#include <float.h>
#pragma warning(push)
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4514) // unreferenced inline function
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function
#include <windows.h>
#undef DrawText
#include <ShellScalingApi.h> // SetProcessDpiAwareness
#pragma warning(pop)

#include "ui_direct_draw.h"
#include "ui_direct_Write.h"
#include "ui_colors.h"

// Silence "Someone Else Problems" when compiled with /Wall Warnings All:
#pragma warning(push)
#pragma warning(disable: 4255) // function prototype given: converting '()' to '(void)'
#include <d3d11_4.h>
#include <dxgi1_6.h>
#pragma warning(pop)

#include "vigil.h"
#include "clock.h"

#define null ((void*)0)
#define countof(a) (sizeof(a) / sizeof((a)[0]))
#define idof(c) __uuidof(c)
#define fif(hr, ...) fatal_if_error(hr, "" __VA_ARGS__)
#define call(ptr, method, ...) fif((ptr)->lpVtbl->method(ptr, ##__VA_ARGS__))
#define void_call(ptr, method, ...) (ptr)->lpVtbl->method(ptr, ##__VA_ARGS__)

static bool translucent = false;

static NONCLIENTMETRICSW ui_app_ncm = { sizeof(NONCLIENTMETRICSW) };

typedef float ui_dip_t; // device independent "pixels" 1.0 / 96.0 inch

typedef struct ui_dpi_t {
    int32_t window;
    int32_t system;
    int32_t monitor_effective;
    int32_t monitor_angular;
    int32_t monitor_raw;
} ui_dpi_t;

static ui_dpi_t dpi;

static HFONT font;

static ID3D11Debug* d3d_debug;
static ID3D11Device* d3d_device;
static ID3D11DeviceContext* d3d_ctx;
static ID2D1Factory* d2d_factory;
static ID2D1DCRenderTarget* render_target;
static IDWriteFactory* dwrite_factory;
static IDWriteTextFormat* text_format;
static IDWriteTextFormat* segoe_format;
static ID2D1SolidColorBrush* brush_white;
static ID2D1SolidColorBrush* brush_black;
static ID2D1SolidColorBrush* brush_orange;
static ID2D1SolidColorBrush* brush_green;
static ID2D1SolidColorBrush* brush_red;

static void release(void* *p) {
    IUnknown* o = (IUnknown*)*p;
    if (o != null) {
        o->lpVtbl->Release(o);
        *p = null;
    }
}

static void ui_app_update_monitor_dpi(HMONITOR monitor) {
    for (int32_t mtd = MDT_EFFECTIVE_DPI; mtd <= MDT_RAW_DPI; mtd++) {
        uint32_t dpi_x = 0;
        uint32_t dpi_y = 0;
        // GetDpiForMonitor() may return ERROR_GEN_FAILURE 0x8007001F when
        // system wakes up from sleep:
        // ""A device attached to the system is not functioning."
        // docs say:
        // "May be used to indicate that the device has stopped responding
        // or a general failure has occurred on the device.
        // The device may need to be manually reset."
        int32_t r = GetDpiForMonitor(monitor, (MONITOR_DPI_TYPE)mtd, &dpi_x, &dpi_y);
        if (r != 0) {
            Sleep(33); // and retry:
            r = GetDpiForMonitor(monitor, (MONITOR_DPI_TYPE)mtd, &dpi_x, &dpi_y);
        }
        if (r == 0) {
            const char* names[] = {"EFFECTIVE_DPI", "ANGULAR_DPI","RAW_DPI"};
            traceln("%s %d %d", names[mtd], dpi_x, dpi_y);
            // EFFECTIVE_DPI 168 168 (with regard of user scaling)
            // ANGULAR_DPI 247 248 (diagonal)
            // RAW_DPI 283 284 (horizontal, vertical)
            switch (mtd) {
                case MDT_EFFECTIVE_DPI:
                    dpi.monitor_effective = (int32_t)max(dpi_x, dpi_y); break;
                case MDT_ANGULAR_DPI:
                    dpi.monitor_angular = (int32_t)max(dpi_x, dpi_y); break;
                case MDT_RAW_DPI:
                    dpi.monitor_raw = (int32_t)max(dpi_x, dpi_y); break;
                default: swear(false);
            }
        }
    }
}

static void update_dpi(HWND wnd) {
    dpi.window = (int32_t)GetDpiForWindow(wnd);
    dpi.system = (int32_t)GetDpiForSystem();
    RECT wrc;
    swear(GetWindowRect(wnd, &wrc));
    HMONITOR monitor = MonitorFromRect(&wrc, MONITOR_DEFAULTTONEAREST);
    swear(monitor != null);
    ui_app_update_monitor_dpi(monitor);
    traceln("dpi .window: %d .system: %d "
            ".monitor: effective %d angular %d raw %d",
            dpi.window, dpi.system,
            dpi.monitor_effective, dpi.monitor_angular, dpi.monitor_raw);
}

static ui_dip_t pt2dip(double pt) {
    return (ui_dip_t)(pt * 96.0 / 72.0);
}

static ui_dip_t px2pt(double x) {
    return (ui_dip_t)(x * 72.0 / dpi.window);
}

static ui_dip_t px2dip(double x) {
    return (ui_dip_t)(x * 96.0 / dpi.window);
}

static ui_dip_t dip2px(double x) {
    return (ui_dip_t)(x * dpi.window / 96.0);
}

static inline D2D1_COLOR_F d2d1_color_f(uint32_t bgra) {
    static_assert(sizeof(ui_colorf_t) == sizeof(D2D1_COLOR_F), "size mismatch");
    static_assert(offsetof(ui_colorf_t, r) == offsetof(D2D1_COLOR_F, r), "mismatch");
    static_assert(offsetof(ui_colorf_t, g) == offsetof(D2D1_COLOR_F, g), "mismatch");
    static_assert(offsetof(ui_colorf_t, b) == offsetof(D2D1_COLOR_F, b), "mismatch");
    static_assert(offsetof(ui_colorf_t, a) == offsetof(D2D1_COLOR_F, a), "mismatch");
    ui_colorf_t f = ui_colors.fp32(bgra);
    return *(D2D1_COLOR_F*)&f;
}

static inline D2D1_COLOR_F d2d1_color(ui_colorf_t const* color) {
    return *(D2D1_COLOR_F*)color;
}

static D2D1_SIZE_F wh_px2dip(int w, int h) {
    D2D1_SIZE_F size = { .width = px2dip(w), .height = px2dip(h) };
    return size;
}

static void draw_rounded_gradient_filled_rectangle(const D2D1_RECT_F rect,
        const D2D1_COLOR_F color_border,
        ui_dip_t border_width, ui_dip_t corner_radius,
        const D2D1_COLOR_F color_top, const D2D1_COLOR_F color_bottom) {
    D2D1_GRADIENT_STOP gradient_stops[] = {
        { 0.0f, color_top },
        { 1.0f, color_bottom }
    };
    ID2D1GradientStopCollection* gradient_stop_collection = null;
    call(render_target, CreateGradientStopCollection,
         gradient_stops, countof(gradient_stops),
         D2D1_GAMMA_1_0, D2D1_EXTEND_MODE_CLAMP,
         &gradient_stop_collection);
    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES gradient_brush_properties = {
        .startPoint = { rect.left, rect.top },
        .endPoint = { rect.left, rect.bottom }
    };
    ID2D1LinearGradientBrush* gradient_brush = null;
    call(render_target, CreateLinearGradientBrush,
         &gradient_brush_properties, null,
         gradient_stop_collection, &gradient_brush);
    D2D1_ROUNDED_RECT rounded_rect = {
        .rect = rect,
        .radiusX = corner_radius,
        .radiusY = corner_radius
    };
    const D2D1_BRUSH_PROPERTIES* brush_properties = null;
    ID2D1SolidColorBrush* border_brush = null;
    call(render_target, CreateSolidColorBrush, &color_border,
            brush_properties, &border_brush);
    void_call(render_target, FillRoundedRectangle, &rounded_rect,
              (ID2D1Brush*)gradient_brush);
    void_call(render_target, DrawRoundedRectangle, &rounded_rect,
              (ID2D1Brush*)border_brush, border_width, null);
    release(&border_brush);
    release(&gradient_brush);
    release(&gradient_stop_collection);
}

static void draw_rectangle(const D2D1_RECT_F rect,
        const D2D1_COLOR_F border_color,
        ui_dip_t border_width, const D2D1_COLOR_F fill_color) {
    ID2D1SolidColorBrush* fill_brush = null;
    call(render_target, CreateSolidColorBrush, &fill_color, null, &fill_brush);
    ID2D1SolidColorBrush* border_brush = null;
    call(render_target, CreateSolidColorBrush, &border_color, null, &border_brush);
    void_call(render_target, FillRectangle, &rect, (ID2D1Brush*)fill_brush);
    void_call(render_target, DrawRectangle, &rect, (ID2D1Brush*)border_brush, border_width, null);
    release(&fill_brush);
    release(&border_brush);
}

static void draw_filled_rect(const D2D1_RECT_F rect,
        const D2D1_COLOR_F fill_color) {
    ID2D1SolidColorBrush* fill_brush = null;
    call(render_target, CreateSolidColorBrush, &fill_color, null, &fill_brush);
    void_call(render_target, FillRectangle, &rect, (ID2D1Brush*)fill_brush);
    release(&fill_brush);
}

static void draw_frame(const D2D1_RECT_F rect,
        const D2D1_COLOR_F border_color,
        ui_dip_t border_width) {
    ID2D1SolidColorBrush* border_brush = null;
    call(render_target, CreateSolidColorBrush, &border_color, null, &border_brush);
    void_call(render_target, DrawRectangle, &rect, (ID2D1Brush*)border_brush, border_width, null);
    release(&border_brush);
}

static void draw_line(const D2D1_POINT_2F from, const D2D1_POINT_2F to,
        ui_dip_t line_width, const D2D1_COLOR_F line_color) {
    ID2D1SolidColorBrush* brush = null;
    const D2D1_BRUSH_PROPERTIES* brush_properties = null;
    call(render_target, CreateSolidColorBrush, &line_color, brush_properties, &brush);
    ID2D1StrokeStyle* stroke_style = null;
    void_call(render_target, DrawLine, from, to, (ID2D1Brush*)brush, line_width, stroke_style);
    release(&brush);
}

static void draw_polyline(int32_t count, const D2D1_POINT_2F points[],
        ui_dip_t line_width, D2D1_COLOR_F line_color) {
    for (int32_t i = 0; i < count - 1; i++) {
        draw_line(points[i], points[i + 1], line_width, line_color);
    }
}

static DWRITE_TEXT_METRICS measure_text(const uint16_t* utf16, int32_t count,
        IDWriteTextFormat* tf, ui_dip_t max_w, ui_dip_t max_h) {
    DWRITE_TEXT_METRICS tm = {0};
    IDWriteTextLayout* tl = null;
    call(dwrite_factory, CreateTextLayout, utf16, (uint32_t)count, tf,
                                           max_w, max_h, &tl);
    call(tl, GetMetrics, &tm);
    release(&tl);
    return tm;
}

static void create_brushes(void) {
    const D2D1_BRUSH_PROPERTIES* brush_properties = null;
    D2D1_COLOR_F black  = d2d1_color(&ui_colors.f.black);
    D2D1_COLOR_F orange = d2d1_color(&ui_colors.f.orange);
    D2D1_COLOR_F green  = d2d1_color(&ui_colors.f.green);
    D2D1_COLOR_F red    = d2d1_color(&ui_colors.f.red);
    D2D1_COLOR_F white  = d2d1_color(&ui_colors.f.white);
#ifndef DEBUG
    // Measured timing: MacBook Air M3 2024 (ARM64) / MacBook Pro 9,1 June 11, 2012 i7-3615QM
    double t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) { // min 122ns / 242ns ~ malloc() time
        call(render_target, CreateSolidColorBrush, &black,  brush_properties, &brush_black);
        release(&brush_black);
    }
    traceln("CreateSolidColorBrush: %.0fns (nanoseconds)",
            (clock_seconds() - t) * 1000.0);
#else
    (void)clock_seconds(); // unused in debug
#endif
    call(render_target, CreateSolidColorBrush, &white,  brush_properties, &brush_white);
    call(render_target, CreateSolidColorBrush, &black,  brush_properties, &brush_black);
    call(render_target, CreateSolidColorBrush, &orange, brush_properties, &brush_orange);
    call(render_target, CreateSolidColorBrush, &green,  brush_properties, &brush_green);
    call(render_target, CreateSolidColorBrush, &red,    brush_properties, &brush_red);
#ifndef DEBUG
    // Measured timing: MacBook Air M3 2024 (ARM64) / MacBook Pro 9,1 June 11, 2012 i7-3615QM
    t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) { // 38ns / 16ns
        void_call(brush_black, SetColor, &black);
    }
    traceln("CreateSolidColorBrush.SetColor): %.0fns (nanoseconds)",
            (clock_seconds() - t) * 1000.0);
#endif
}

static void create_text_format(void) {
    float h = (float)abs(ui_app_ncm.lfMessageFont.lfHeight);
    float pt = (float)px2pt(h);
    traceln("MessageFont: %.1fpx %.1fpt %.1fdip %.1fpx",
            h, pt, pt2dip(pt), dip2px(pt2dip(pt)));
#ifndef DEBUG
    // Measured timing: MacBook Air M3 2024 (ARM64) / MacBook Pro 9,1 June 11, 2012 i7-3615QM
    double t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) { // min 495ns / 1363ns ~ 3 x malloc()
        call(dwrite_factory, CreateTextFormat, L"Segoe UI", null,
            DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL, (float)pt2dip(pt),
            L"en-us", &segoe_format);
        release(&segoe_format);
    }
    traceln("CreateTextFormat: %.0fns (nanoseconds)",
            (clock_seconds() - t) * 1000.0);
#endif
    call(dwrite_factory, CreateTextFormat, L"Gabriola", null,
        DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, pt2dip(48.0f),
        L"en-us", &text_format);
    call(dwrite_factory, CreateTextFormat,
        ui_app_ncm.lfMessageFont.lfFaceName, null,
        DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, pt2dip(pt),
        L"en-us", &segoe_format);
    call(text_format, SetTrimming, &(DWRITE_TRIMMING){
        .granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER,
        .delimiter = 0,
        .delimiterCount = 0
    }, null);
    DWRITE_TEXT_METRICS tm = measure_text(L"Hello World!", 12, text_format, FLT_MAX, FLT_MAX);
#ifndef DEBUG
    // Measured timing: MacBook Air M3 2024 (ARM64) / MacBook Pro 9,1 June 11, 2012 i7-3615QM
    t = clock_seconds();
    for (int i = 0; i < 1000; i++) { // min ???us / 68us
        tm = measure_text(L"Hello World!", 12, text_format, FLT_MAX, FLT_MAX);
    }
    traceln("CreateTextFormat.CreateTextLayout.GetMetrics(): %.0fus (microseconds)",
            (clock_seconds() - t) * 1000.0);
    // single call modifying text_format:
    t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) { // min 29ns / 3ns
        call(text_format, SetWordWrapping, DWRITE_WORD_WRAPPING_NO_WRAP);
    }
    traceln("CreateTextFormat.SetWordWrapping(): %.0fns (nanoseconds)",
            (clock_seconds() - t) * 1000.0);
#endif
    (void)tm;
}

static void cleanup_render_target(void) {
    if (brush_white)   { release(&brush_white); }
    if (brush_black)   { release(&brush_black); }
    if (brush_orange)  { release(&brush_orange); }
    if (brush_green)   { release(&brush_green); }
    if (brush_red)     { release(&brush_red); }
    if (text_format)   { release(&text_format); }
    if (segoe_format)  { release(&segoe_format); }
    if (d3d_ctx)       { void_call(d3d_ctx, ClearState); }
    if (render_target) { release(&render_target); }
}

static void create_render_target(HWND wnd) {
    RECT rc;
    GetClientRect(wnd, &rc);
    if (d2d_factory != null) {
        update_dpi(wnd);
        D2D1_RENDER_TARGET_PROPERTIES ps = {
            .type = D2D1_RENDER_TARGET_TYPE_DEFAULT,
            .pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM,
                             D2D1_ALPHA_MODE_PREMULTIPLIED },
            .dpiX = (float)dpi.window,
            .dpiY = (float)dpi.window,
            .usage = D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE,
            .minLevel = D2D1_FEATURE_LEVEL_10
        };
        call(d2d_factory, CreateDCRenderTarget, &ps, &render_target);
        create_brushes();
        create_text_format();
    }
}

static void init_d3d(HWND wnd) {
    IDXGIFactory2* dxgi_factory = null;
    fif(CreateDXGIFactory1(&IID_IDXGIFactory2, (void**)&dxgi_factory));
    swear(dxgi_factory != null);
    call(dxgi_factory, MakeWindowAssociation, wnd, 0);
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };
    if (FAILED(D3D11CreateDevice(null, D3D_DRIVER_TYPE_HARDWARE, null,
               creationFlags, featureLevels, countof(featureLevels),
               D3D11_SDK_VERSION, &d3d_device, null, &d3d_ctx))) {
        fif(D3D11CreateDevice(null, D3D_DRIVER_TYPE_WARP, null,
                              creationFlags, featureLevels, countof(featureLevels),
                              D3D11_SDK_VERSION, &d3d_device, null, &d3d_ctx));
    }
#if defined(_DEBUG)
    if (d3d_device != null) {
        call(d3d_device, QueryInterface, &IID_ID3D11Debug, (void**)&d3d_debug);
    }
#endif
    release(&dxgi_factory);
}

static void init_d2d(void) {
    D2D1_FACTORY_OPTIONS options = { .debugLevel = D2D1_DEBUG_LEVEL_NONE };
#if defined(DEBUG) || defined(_DEBUG)
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
    fif(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                          &IID_ID2D1Factory,
                          &options, (void**)&d2d_factory));
    fif(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                            &IID_IDWriteFactory,
                            (void**)&dwrite_factory));
}

static bool render_dx(D2D1_SIZE_F size) {
    void_call(render_target, BeginDraw);
    void_call(render_target, SetTransform, &D2D1_MATRIX_3X2_F_IDENTITY);
    D2D1_COLOR_F background = d2d1_color_f(ui_colors.bgra.black);
    void_call(render_target, Clear, &background);
    ui_dip_t w4 = size.width / 4;
    ui_dip_t h4 = size.height / 4;
    const D2D1_RECT_F rect = { .left = w4, .top = h4,
        .right = size.width - w4, .bottom = size.height - h4 };
    D2D1_COLOR_F border_color = {0.75f, 0.75f, 0.75f, 1.0f};
    const ui_dip_t border_width = 3.0f;
    D2D1_COLOR_F top_color = {0.5f, 0.5f, 0.5f, 1.0f};
    D2D1_COLOR_F bottom_color = {0.25f, 0.25f, 0.25f, 1.0f};
    const ui_dip_t corner_radius = 20.0f;
    draw_rounded_gradient_filled_rectangle(rect, border_color,
        border_width, corner_radius, top_color, bottom_color);
    D2D1_RECT_F inner = rect;
    inner.left   += w4 / 4;
    inner.right  -= w4 / 4;
    inner.top    += h4 / 4;
    inner.bottom -= h4 / 4;
    draw_rectangle(inner, d2d1_color_f(ui_colors.bgra.green),
                   border_width, d2d1_color_f(ui_colors.bgra.orange));
    D2D1_RECT_F layout = inner;
    layout.left  += w4 / 32;
    layout.right -= w4 / 32;
    void_call(render_target, DrawText,
              L"Hello, World!", 13,
              text_format, &layout, (ID2D1Brush*)brush_black,
              D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,
              DWRITE_MEASURING_MODE_NATURAL);
    layout = (D2D1_RECT_F){px2dip(10.0), px2dip(10.0),
        size.width - px2dip(10.0), size.height - px2dip(10.0)};
    void_call(render_target, DrawText,
              L"Hello, World!\xD83E\xDDF8 (DirectWrite)", 29,
              segoe_format, &layout, (ID2D1Brush*)brush_white,
              D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,
              DWRITE_MEASURING_MODE_NATURAL);
#ifndef DEBUG
    // Measured timing: MacBook Air M3 2024 (ARM64) / MacBook Pro 9,1 June 11, 2012 i7-3615QM
    double t = clock_seconds();
    for (int i = 0; i < 1000; i++) { // min ???us / 96us
        void_call(render_target, DrawText,
                  L"Hello, World!\xD83E\xDDF8 (DirectWrite)", 29,
                  segoe_format, &layout, (ID2D1Brush*)brush_white,
                  D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,
                  DWRITE_MEASURING_MODE_NATURAL);
    }
    traceln("CreateTextFormat.DrawText(): %.0fus (microseconds)",
            (clock_seconds() - t) * 1000.0);
#endif
    const D2D1_POINT_2F points[6] = {
        {150.0f, 200.0f},
        {200.0f, 250.0f},
        {250.0f, 200.0f},
        {300.0f, 250.0f},
        {350.0f, 200.0f},
        {650.0f, 300.0f}
    };
    draw_polyline(countof(points), points, border_width,
                  d2d1_color_f(ui_colors.bgra.red));
    HRESULT hr = render_target->lpVtbl->EndDraw(render_target, null, null);
    if (hr != D2DERR_RECREATE_TARGET) { fif(hr); }
    return hr != D2DERR_RECREATE_TARGET;
}

static void render_gdi(HDC hdc, RECT rc) {
    COLORREF text_color = SetTextColor(hdc, 0xFFFFFF);
    int background_mode = SetBkMode(hdc, TRANSPARENT);
    HBRUSH brush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    // SYSTEM_FONT is even smaller than DEFAULT_GUI_FONT
    rc.left = 10;
    rc.top  = 60;
    HFONT f = (HFONT)SelectObject(hdc, font);
    DrawTextW(hdc, L"Hello, World!\xD83E\xDDF8 (GDI)", 21, &rc,
                DT_LEFT | DT_SINGLELINE);
    rc.top += 60;
    SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
    DrawTextA(hdc, "Hello, World! (DEFAULT_GUI_FONT)", 32, &rc,
                DT_LEFT | DT_SINGLELINE);
    SelectObject(hdc, f);
    SelectObject(hdc, brush);
    SetBkMode(hdc, background_mode);
    SetTextColor(hdc, text_color);
}

static void paint(HWND wnd, HDC hdc) {
    SetLayout(hdc, LAYOUT_BITMAPORIENTATIONPRESERVED);
    update_dpi(wnd);
    RECT rc;
    GetClientRect(wnd, &rc);
    if (render_target == null) { create_render_target(wnd); }
    if (render_target != null) {
        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;
        D2D1_SIZE_F size = wh_px2dip(w, h);
        void_call(render_target, BindDC, hdc, &rc);
        if (!render_dx(size)) {
            cleanup_render_target();
            InvalidateRect(wnd, null, false);
        }
    }
    swear(font != null);
    if (font != null) {
        render_gdi(hdc, rc);
    }
}

LRESULT CALLBACK window_proc(HWND wnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SIZE:
        update_dpi(wnd);
        if (wParam != SIZE_MINIMIZED && render_target != null) {
            int w = LOWORD(lParam);
            int h = HIWORD(lParam);
            traceln("%dx%d", w, h);
            cleanup_render_target();
        }
        return 0;
    case WM_ERASEBKGND: return 1;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(wnd, &ps);
        paint(wnd, ps.hdc);
        EndPaint(wnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        cleanup_render_target();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(wnd, uMsg, wParam, lParam);
}

static void set_dpi_awareness(void) {
    DPI_AWARENESS_CONTEXT dpi_awareness_context_1 =
        GetThreadDpiAwarenessContext();
    // https://blogs.windows.com/windowsdeveloper/2017/05/19/improving-high-dpi-experience-gdi-based-desktop-apps/
    DWORD error = SetProcessDpiAwarenessContext(
                    DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2) ?
        0 : GetLastError();
    if (error == ERROR_ACCESS_DENIED) {
        traceln("Warning: SetProcessDpiAwarenessContext(): ERROR_ACCESS_DENIED");
        // dpi awareness already set, manifest, registry, windows policy
        // Try via Shell:
        HRESULT hr = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
        if (hr == E_ACCESSDENIED) {
            traceln("Warning: SetProcessDpiAwareness(): E_ACCESSDENIED");
        }
    }
    DPI_AWARENESS_CONTEXT dpi_awareness_context_2 =
        GetThreadDpiAwarenessContext();
    swear(dpi_awareness_context_1 != dpi_awareness_context_2);
}

static void ui_app_update_ncm(void) {
    // Only UTF-16 version supported SystemParametersInfoForDpi
    swear(SystemParametersInfoForDpi(SPI_GETNONCLIENTMETRICS,
        sizeof(ui_app_ncm), &ui_app_ncm, 0, (DWORD)dpi.window));
    LOGFONTW lf = ui_app_ncm.lfMessageFont;
    traceln("lfMessageFont: %S", lf.lfFaceName);
    traceln("Height : %dpx %.1fpt", lf.lfHeight, px2pt(lf.lfHeight));
    traceln("Weight : %d", lf.lfWeight);
    traceln("Quality: %d", lf.lfQuality);
}

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
                   _In_ char* cmd, _In_ int show_command) {
    (void)prev; (void)cmd;
    fif(CoInitialize(null));
    set_dpi_awareness();
    WNDCLASSEXA wc = { .cbSize = sizeof(WNDCLASSEX),
        .style = CS_HREDRAW | CS_VREDRAW, .lpfnWndProc = window_proc,
        .cbClsExtra= 0, .cbWndExtra = 0,
        .hInstance = instance, .hIcon = null, .hCursor = LoadCursor(null, IDC_ARROW),
        .hbrBackground = GetStockObject(BLACK_BRUSH),
        .lpszMenuName = null, .lpszClassName = "WindowClass", .hIconSm = null
    };
    RegisterClassExA(&wc);
    RECT wr = { 0, 0, 1500, 900 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    int w = wr.right - wr.left;
    int h = wr.bottom - wr.top;
    DWORD ex = translucent ? WS_EX_COMPOSITED | WS_EX_LAYERED : 0;
    HWND wnd = CreateWindowExA(ex,
        "WindowClass", "Hello", WS_OVERLAPPEDWINDOW,
        -1, -1, w, h, null, null, instance, null);
    if (translucent) {
        SetLayeredWindowAttributes(wnd, 0x1E1E1E, 0xBF, LWA_COLORKEY|LWA_ALPHA);
    }
    update_dpi(wnd);
    ui_app_update_ncm();
    LOGFONTW lf = ui_app_ncm.lfMessageFont;
    lf.lfQuality = PROOF_QUALITY;
    font = CreateFontIndirectW(&lf);
    init_d3d(wnd); // only needed for debugging
    init_d2d();
    ShowWindow(wnd, show_command);
    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (GetMessage(&msg, null, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    if (d2d_factory)    { release(&d2d_factory); }
    if (dwrite_factory) { release(&dwrite_factory); }
    if (d3d_device)     { release(&d3d_device); }
    if (d3d_ctx)        { release(&d3d_ctx); }
    if (d3d_debug) {
        void_call(d3d_debug, ReportLiveDeviceObjects, D3D11_RLDO_DETAIL);
        release(&d3d_debug);
    }
    CoUninitialize();
    return 0;
}

#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "shcore") // SetProcessDpiAwareness
