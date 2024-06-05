#pragma warning(push)
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4514) // unreferenced inline function
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function
#include <windows.h>
#undef DrawText
#include <ShellScalingApi.h> // SetProcessDpiAwareness
#pragma warning(pop)

#include "vigil.h"
#include "clock.h"
#include "ui_direct_draw.h"
#include "ui_direct_Write.h"
#include "colors.h"

// Silence "Someone Else Problems" when compiled with /Wall Warnings All:
#pragma warning(push)
#pragma warning(disable: 4255) // function prototype given: converting '()' to '(void)'
#include <d3d11_4.h>
#include <dxgi1_6.h>
#pragma warning(pop)

#define null ((void*)0)
#define countof(a) (sizeof(a) / sizeof((a)[0]))
#define idof(c) __uuidof(c)
#define fif(hr, ...) fatal_if_error(hr, "" __VA_ARGS__)
#define call(ptr, method, ...) fif((ptr)->lpVtbl->method(ptr, ##__VA_ARGS__))
#define void_call(ptr, method, ...) (ptr)->lpVtbl->method(ptr, ##__VA_ARGS__)

static bool translucent = false;

static NONCLIENTMETRICSW ui_app_ncm = { sizeof(NONCLIENTMETRICSW) };

static double dpi;
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

static float pt2dip(double pt) {
    return (float)(pt * 96.0 / 72.0);
}

static float px2pt(double x) {
    return (float)(x * 72.0 / dpi);
}

static float px2dip(double x) {
    return (float)(x * 96.0 / dpi);
}

static float dip2px(double x) {
    return (float)(x * dpi / 96.0);
}

static void create_brushes(void) {
    const D2D1_BRUSH_PROPERTIES* brush_properties = null;
    D2D1_COLOR_F black  = color_f(Black);
    D2D1_COLOR_F orange = color_f(Orange);
    D2D1_COLOR_F green  = color_f(Green);
    D2D1_COLOR_F red    = color_f(Red);
    D2D1_COLOR_F white  = color_f(White);
#ifndef DEBUG
    double t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) {
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
}

static void create_text_format(void) {
    float h = (float)abs(ui_app_ncm.lfMessageFont.lfHeight);
    float pt = (float)px2pt(h);
    traceln("MessageFont: %.1fpx %.1fpt %.1fdip %.1fpx",
            h, pt, pt2dip(pt), dip2px(pt2dip(pt)));
#ifndef DEBUG
    double t = clock_seconds();
    for (int i = 0; i < 1000 * 1000; i++) {
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
        DWRITE_FONT_STRETCH_NORMAL, (float)pt2dip(72.0f),
        L"en-us", &text_format);
    call(dwrite_factory, CreateTextFormat, L"Segoe UI", null,
        DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, (float)pt2dip(pt),
        L"en-us", &segoe_format);
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
        dpi = (double)GetDpiForWindow(wnd);
        D2D1_RENDER_TARGET_PROPERTIES ps = {
            .type = D2D1_RENDER_TARGET_TYPE_DEFAULT,
            .pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM,
                             D2D1_ALPHA_MODE_PREMULTIPLIED },
            .dpiX = (float)dpi,
            .dpiY = (float)dpi,
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

static D2D1_SIZE_F wh_px2dip(int w, int h) {
    D2D1_SIZE_F size = { .width = px2dip(w), .height = px2dip(h) };
    return size;
}

static bool render_dx(D2D1_SIZE_F size) {
    void_call(render_target, BeginDraw);
    void_call(render_target, SetTransform, &D2D1_MATRIX_3X2_F_IDENTITY);
    D2D1_COLOR_F background = color_f(Black);
    void_call(render_target, Clear, &background);

    // Create gradient stops
    D2D1_GRADIENT_STOP gradient_stops[] = {
        { 0.0f, { 0.5f, 0.5f, 0.5f, 1.0f } },
        { 1.0f, { 0.25f, 0.25f, 0.25f, 1.0f } }
    };

    // Create gradient stop collection
    ID2D1GradientStopCollection* gradient_stop_collection = null;
    call(render_target, CreateGradientStopCollection,
         gradient_stops, countof(gradient_stops),
         D2D1_GAMMA_1_0, D2D1_EXTEND_MODE_CLAMP,
         &gradient_stop_collection);
    ID2D1LinearGradientBrush* gradient_brush = null;
    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES gradient_brush_properties = {
        .startPoint = { 150.0f, 200.0f },
        .endPoint = { 650.0f, 300.0f }
    };
    call(render_target, CreateLinearGradientBrush,
         &gradient_brush_properties, null,
         gradient_stop_collection, &gradient_brush);
    D2D1_ROUNDED_RECT rounded_rect = {
        .rect = { 150.0f, 200.0f, 650.0f, 300.0f },
        .radiusX = 20.0f,
        .radiusY = 20.0f
    };
    void_call(render_target, FillRoundedRectangle, &rounded_rect,
              (ID2D1Brush*)gradient_brush);
    void_call(render_target, DrawRoundedRectangle, &rounded_rect,
              (ID2D1Brush*)brush_black, 0.75f, null);
    release(&gradient_brush);
    release(&gradient_stop_collection);
#if 0
    D2D1_RECT_F rect = (D2D1_RECT_F){150, 200, 650, 300};
    void_call(render_target, FillRectangle, &rect, (ID2D1Brush*)brush_orange);
    ID2D1StrokeStyle* stroke_style = null;
    void_call(render_target, DrawRectangle, &rect, (ID2D1Brush*)brush_green,
                                            2.0f, stroke_style);
#endif

    D2D1_RECT_F layout = (D2D1_RECT_F){px2dip(10.0), px2dip(10.0), size.width, size.height};
    void_call(render_target, DrawText,
              L"Hello, World!", 13,
              text_format, &layout, (ID2D1Brush*)brush_white,
              D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,
              DWRITE_MEASURING_MODE_NATURAL);
    void_call(render_target, DrawText,
              L"Hello, World!\xD83E\xDDF8 (DirectWrite)", 29,
              segoe_format, &layout, (ID2D1Brush*)brush_white,
              D2D1_DRAW_TEXT_OPTIONS_ENABLE_COLOR_FONT,
              DWRITE_MEASURING_MODE_NATURAL);
#if 0
    D2D1_POINT_2F points[6] = {
        {150.0f, 200.0f},
        {200.0f, 250.0f},
        {250.0f, 200.0f},
        {300.0f, 250.0f},
        {350.0f, 200.0f},
        {650.0f, 300.0f}
    };
    void_call(render_target, DrawLine, points[0], points[1], (ID2D1Brush*)brush_red, 2.0f, stroke_style);
    void_call(render_target, DrawLine, points[1], points[2], (ID2D1Brush*)brush_red, 2.0f, stroke_style);
    void_call(render_target, DrawLine, points[2], points[3], (ID2D1Brush*)brush_red, 2.0f, stroke_style);
    void_call(render_target, DrawLine, points[3], points[4], (ID2D1Brush*)brush_red, 2.0f, stroke_style);
    void_call(render_target, DrawLine, points[4], points[5], (ID2D1Brush*)brush_red, 2.0f, stroke_style);
#endif
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
    dpi = (double)GetDpiForWindow(wnd);
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
        dpi = (double)GetDpiForWindow(wnd);
        if (wParam != SIZE_MINIMIZED && render_target != null) {
            int w = LOWORD(lParam);
            int h = HIWORD(lParam);
            printf("%dx%d", w, h);
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
        sizeof(ui_app_ncm), &ui_app_ncm, 0, (DWORD)dpi));
    LOGFONTW lf = ui_app_ncm.lfMessageFont;
    traceln("lfMessageFont: %S", lf.lfFaceName);
    traceln("Height : %d", lf.lfHeight);
    traceln("Weight : %d", lf.lfWeight);
    traceln("Quality: %d", lf.lfQuality);
    traceln("dpi:     %d", (uint32_t)dpi);
}

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
                   _In_ char* cmd, _In_ int show_command) {
    (void)prev; (void)cmd;
    set_dpi_awareness();
    WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW,
        window_proc, 0, 0, instance, null, LoadCursor(null, IDC_ARROW),
        null, null, "WindowClass", null };
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
    dpi = (double)GetDpiForWindow(wnd);
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
    return 0;
}

#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "shcore") // SetProcessDpiAwareness
