#pragma once
#ifndef DirectDraw_h
#define DirectDraw_h
#include <windows.h>
#include <unknwn.h>
#include <dcommon.h>
#include <initguid.h>
#include "ui_direct_draw_defs.h"
#include "ui_direct_write_defs.h"

// Last C supported d2d1.h
// https://github.com/tpn/winsdk-10/blob/master/Include/10.0.10240.0/um/d2d1.h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DIRECT_DRAW_IMPORT
#define DIRECT_DRAW_IMPORT __declspec(dllimport) WINAPI
#endif

typedef struct ID2D1MeshVtbl {
    // IUnknown methods
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1Mesh* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1Mesh* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1Mesh* This);

    // ID2D1Resource methods
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1Mesh* This,
        ID2D1Factory** factory);

    // ID2D1Mesh methods
    HRESULT (STDMETHODCALLTYPE *Open)(
        ID2D1Mesh* This,
        ID2D1TessellationSink** tessellationSink);
} ID2D1MeshVtbl;

struct ID2D1Mesh {
    const ID2D1MeshVtbl* lpVtbl;
};

DEFINE_GUID(IID_ID2D1Mesh, // {2CD906C2-12E2-11DC-9FED-001143A055F9}
0x2CD906C2, 0x12E2, 0x11DC, 0x9F, 0xED, 0x00, 0x11, 0x43, 0xA0, 0x55, 0xF9);

typedef struct ID2D1DCRenderTargetVtbl {
    // Base interface methods (ID2D1RenderTarget)
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1DCRenderTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1DCRenderTarget* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1DCRenderTarget* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1DCRenderTarget* This,
        ID2D1Factory** factory);
    HRESULT (STDMETHODCALLTYPE *CreateBitmap)(
        ID2D1DCRenderTarget* This,
        D2D1_SIZE_U size,
        const void* srcData,
        UINT32 pitch,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapFromWicBitmap)(
        ID2D1DCRenderTarget* This,
        IWICBitmapSource* wicBitmapSource,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateSharedBitmap)(
        ID2D1DCRenderTarget* This,
        REFIID riid,
        void* data,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapBrush)(
        ID2D1DCRenderTarget* This,
        ID2D1Bitmap* bitmap,
        const D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1BitmapBrush** bitmapBrush);
    HRESULT (STDMETHODCALLTYPE *CreateSolidColorBrush)(
        ID2D1DCRenderTarget* This,
        const D2D1_COLOR_F* color,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1SolidColorBrush** solidColorBrush);
    HRESULT (STDMETHODCALLTYPE *CreateGradientStopCollection)(
        ID2D1DCRenderTarget* This,
        const D2D1_GRADIENT_STOP* gradientStops,
        UINT32 gradientStopsCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        ID2D1GradientStopCollection** gradientStopCollection);
    HRESULT (STDMETHODCALLTYPE *CreateLinearGradientBrush)(
        ID2D1DCRenderTarget* This,
        const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1LinearGradientBrush** linearGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateRadialGradientBrush)(
        ID2D1DCRenderTarget* This,
        const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1RadialGradientBrush** radialGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateCompatibleRenderTarget)(
        ID2D1DCRenderTarget* This,
        const D2D1_SIZE_F* desiredSize,
        const D2D1_SIZE_U* desiredPixelSize,
        const D2D1_PIXEL_FORMAT* desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        ID2D1BitmapRenderTarget** bitmapRenderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateLayer)(
        ID2D1DCRenderTarget* This,
        const D2D1_SIZE_F* size,
        ID2D1Layer** layer);
    HRESULT (STDMETHODCALLTYPE *CreateMesh)(
        ID2D1DCRenderTarget* This,
        ID2D1Mesh** mesh);
    void (STDMETHODCALLTYPE *DrawLine)(
        ID2D1DCRenderTarget* This,
        D2D1_POINT_2F point0,
        D2D1_POINT_2F point1,
        ID2D1Brush* brush,
        FLOAT strokeWidth,
        ID2D1StrokeStyle* strokeStyle);
    void (STDMETHODCALLTYPE *DrawRectangle)(
        ID2D1DCRenderTarget* This,
        const D2D1_RECT_F* rect,
        ID2D1Brush* brush,
        FLOAT strokeWidth,
        ID2D1StrokeStyle* strokeStyle);
    void (STDMETHODCALLTYPE *FillRectangle)(
        ID2D1DCRenderTarget* This,
        const D2D1_RECT_F* rect,
        ID2D1Brush* brush);
    void (STDMETHODCALLTYPE *DrawRoundedRectangle)(
        ID2D1DCRenderTarget* This,
        const D2D1_ROUNDED_RECT* roundedRect,
        ID2D1Brush* brush,
        FLOAT strokeWidth,
        ID2D1StrokeStyle* strokeStyle);
    void (STDMETHODCALLTYPE *FillRoundedRectangle)(
        ID2D1DCRenderTarget* This,
        const D2D1_ROUNDED_RECT* roundedRect,
        ID2D1Brush* brush);
    void (STDMETHODCALLTYPE *DrawEllipse)(
        ID2D1DCRenderTarget* This,
        const D2D1_ELLIPSE* ellipse,
        ID2D1Brush* brush,
        FLOAT strokeWidth,
        ID2D1StrokeStyle* strokeStyle);
    void (STDMETHODCALLTYPE *FillEllipse)(
        ID2D1DCRenderTarget* This,
        const D2D1_ELLIPSE* ellipse,
        ID2D1Brush* brush);
    void (STDMETHODCALLTYPE *DrawGeometry)(
        ID2D1DCRenderTarget* This,
        ID2D1Geometry* geometry,
        ID2D1Brush* brush,
        FLOAT strokeWidth,
        ID2D1StrokeStyle* strokeStyle);
    void (STDMETHODCALLTYPE *FillGeometry)(
        ID2D1DCRenderTarget* This,
        ID2D1Geometry* geometry,
        ID2D1Brush* brush,
        ID2D1Brush* opacityBrush);
    void (STDMETHODCALLTYPE *FillMesh)(
        ID2D1DCRenderTarget* This,
        ID2D1Mesh* mesh,
        ID2D1Brush* brush);
    void (STDMETHODCALLTYPE *FillOpacityMask)(
        ID2D1DCRenderTarget* This,
        ID2D1Bitmap* opacityMask,
        ID2D1Brush* brush,
        D2D1_OPACITY_MASK_CONTENT content,
        const D2D1_RECT_F* destinationRectangle,
        const D2D1_RECT_F* sourceRectangle);
    void (STDMETHODCALLTYPE *DrawBitmap)(
        ID2D1DCRenderTarget* This,
        ID2D1Bitmap* bitmap,
        const D2D1_RECT_F* destinationRectangle,
        FLOAT opacity,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode,
        const D2D1_RECT_F* sourceRectangle);
    void (STDMETHODCALLTYPE *DrawText)(
        ID2D1DCRenderTarget* This,
        const WCHAR* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        const D2D1_RECT_F* layoutRect,
        ID2D1Brush* defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options,
        DWRITE_MEASURING_MODE measuringMode);
    void (STDMETHODCALLTYPE *DrawTextLayout)(
        ID2D1DCRenderTarget* This,
        D2D1_POINT_2F origin,
        IDWriteTextLayout* textLayout,
        ID2D1Brush* defaultForegroundBrush,
        D2D1_DRAW_TEXT_OPTIONS options);
    void (STDMETHODCALLTYPE *DrawGlyphRun)(
        ID2D1DCRenderTarget* This,
        D2D1_POINT_2F baselineOrigin,
        const DWRITE_GLYPH_RUN* glyphRun,
        const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
        ID2D1Brush* foregroundBrush,
        DWRITE_MEASURING_MODE measuringMode);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1DCRenderTarget* This,
        const D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1DCRenderTarget* This,
        D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *SetAntialiasMode)(
        ID2D1DCRenderTarget* This,
        D2D1_ANTIALIAS_MODE antialiasMode);
    D2D1_ANTIALIAS_MODE (STDMETHODCALLTYPE *GetAntialiasMode)(
        ID2D1DCRenderTarget* This);
    void (STDMETHODCALLTYPE *SetTextAntialiasMode)(
        ID2D1DCRenderTarget* This,
        D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode);
    D2D1_TEXT_ANTIALIAS_MODE (STDMETHODCALLTYPE *GetTextAntialiasMode)(
        ID2D1DCRenderTarget* This);
    void (STDMETHODCALLTYPE *SetTextRenderingParams)(
        ID2D1DCRenderTarget* This,
        IDWriteRenderingParams* textRenderingParams);
    void (STDMETHODCALLTYPE *GetTextRenderingParams)(
        ID2D1DCRenderTarget* This,
        IDWriteRenderingParams** textRenderingParams);
    void (STDMETHODCALLTYPE *SetTags)(
        ID2D1DCRenderTarget* This,
        D2D1_TAG tag1,
        D2D1_TAG tag2);
    void (STDMETHODCALLTYPE *GetTags)(
        ID2D1DCRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    void (STDMETHODCALLTYPE *PushLayer)(
        ID2D1DCRenderTarget* This,
        const D2D1_LAYER_PARAMETERS* layerParameters,
        ID2D1Layer* layer);
    void (STDMETHODCALLTYPE *PopLayer)(ID2D1DCRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *Flush)(
        ID2D1DCRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    void (STDMETHODCALLTYPE *SaveDrawingState)(
        ID2D1DCRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    void (STDMETHODCALLTYPE *RestoreDrawingState)(
        ID2D1DCRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    void (STDMETHODCALLTYPE *PushAxisAlignedClip)(
        ID2D1DCRenderTarget* This,
        const D2D1_RECT_F* clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode);
    void (STDMETHODCALLTYPE *PopAxisAlignedClip)(ID2D1DCRenderTarget* This);
    void (STDMETHODCALLTYPE *Clear)(
        ID2D1DCRenderTarget* This,
        const D2D1_COLOR_F* clearColor);
    void (STDMETHODCALLTYPE *BeginDraw)(ID2D1DCRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *EndDraw)(
        ID2D1DCRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    D2D1_PIXEL_FORMAT (STDMETHODCALLTYPE *GetPixelFormat)(ID2D1DCRenderTarget* This);
    void (STDMETHODCALLTYPE *SetDpi)(
        ID2D1DCRenderTarget* This,
        FLOAT dpiX,
        FLOAT dpiY);
    void (STDMETHODCALLTYPE *GetDpi)(
        ID2D1DCRenderTarget* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    D2D1_SIZE_F (STDMETHODCALLTYPE *GetSize)(ID2D1DCRenderTarget* This);
    D2D1_SIZE_U (STDMETHODCALLTYPE *GetPixelSize)(ID2D1DCRenderTarget* This);
    UINT32 (STDMETHODCALLTYPE *GetMaximumBitmapSize)(ID2D1DCRenderTarget* This);
    BOOL (STDMETHODCALLTYPE *IsSupported)(
        ID2D1DCRenderTarget* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties);

    // Derived interface methods
    HRESULT (STDMETHODCALLTYPE *BindDC)(
        ID2D1DCRenderTarget* This,
        const HDC hdc,
        const RECT* pSubRect);
} ID2D1DCRenderTargetVtbl;

struct ID2D1DCRenderTarget {
    const ID2D1DCRenderTargetVtbl* lpVtbl;
};

DEFINE_GUID(IID_ID2D1DCRenderTarget,
0x1c51bc64, 0xde61, 0x46fd, 0x98, 0x99, 0x63, 0xa5, 0xd8, 0xf0, 0x39, 0x50);

typedef struct ID2D1BitmapBrushVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1BitmapBrush* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1BitmapBrush* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1BitmapBrush* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1BitmapBrush* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *SetOpacity)(
        ID2D1BitmapBrush* This,
        FLOAT opacity);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1BitmapBrush* This,
        const D2D1_MATRIX_3X2_F* transform);
    FLOAT (STDMETHODCALLTYPE *GetOpacity)(
        ID2D1BitmapBrush* This);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1BitmapBrush* This,
        D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *SetExtendModeX)(
        ID2D1BitmapBrush* This,
        D2D1_EXTEND_MODE extendModeX);
    void (STDMETHODCALLTYPE *SetExtendModeY)(
        ID2D1BitmapBrush* This,
        D2D1_EXTEND_MODE extendModeY);
    void (STDMETHODCALLTYPE *SetInterpolationMode)(
        ID2D1BitmapBrush* This,
        D2D1_BITMAP_INTERPOLATION_MODE interpolationMode);
    D2D1_EXTEND_MODE (STDMETHODCALLTYPE *GetExtendModeX)(
        ID2D1BitmapBrush* This);
    D2D1_EXTEND_MODE (STDMETHODCALLTYPE *GetExtendModeY)(
        ID2D1BitmapBrush* This);
    D2D1_BITMAP_INTERPOLATION_MODE (STDMETHODCALLTYPE *GetInterpolationMode)(
        ID2D1BitmapBrush* This);
} ID2D1BitmapBrushVtbl;

struct ID2D1BitmapBrush {
    const ID2D1BitmapBrushVtbl* lpVtbl;
};

typedef struct ID2D1LinearGradientBrushVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1LinearGradientBrush* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1LinearGradientBrush* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1LinearGradientBrush* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1LinearGradientBrush* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *SetOpacity)(
        ID2D1LinearGradientBrush* This,
        FLOAT opacity);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1LinearGradientBrush* This,
        const D2D1_MATRIX_3X2_F* transform);
    FLOAT (STDMETHODCALLTYPE *GetOpacity)(
        ID2D1LinearGradientBrush* This);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1LinearGradientBrush* This,
        D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *SetStartPoint)(
        ID2D1LinearGradientBrush* This,
        D2D1_POINT_2F startPoint);
    void (STDMETHODCALLTYPE *SetEndPoint)(
        ID2D1LinearGradientBrush* This,
        D2D1_POINT_2F endPoint);
    D2D1_POINT_2F (STDMETHODCALLTYPE *GetStartPoint)(
        ID2D1LinearGradientBrush* This);
    D2D1_POINT_2F (STDMETHODCALLTYPE *GetEndPoint)(
        ID2D1LinearGradientBrush* This);
    void (STDMETHODCALLTYPE *GetGradientStopCollection)(
        ID2D1LinearGradientBrush* This,
        ID2D1GradientStopCollection** gradientStopCollection);
} ID2D1LinearGradientBrushVtbl;

struct ID2D1LinearGradientBrush {
    const ID2D1LinearGradientBrushVtbl* lpVtbl;
};

typedef struct ID2D1GradientStopCollectionVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1GradientStopCollection* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1GradientStopCollection* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1GradientStopCollection* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1GradientStopCollection* This,
        ID2D1Factory** factory);
    UINT32 (STDMETHODCALLTYPE *GetGradientStopCount)(
        ID2D1GradientStopCollection* This);
    void (STDMETHODCALLTYPE *GetGradientStops)(
        ID2D1GradientStopCollection* This,
        D2D1_GRADIENT_STOP* gradientStops,
        UINT32 gradientStopsCount);
    D2D1_GAMMA (STDMETHODCALLTYPE *GetColorInterpolationGamma)(
        ID2D1GradientStopCollection* This);
    D2D1_EXTEND_MODE (STDMETHODCALLTYPE *GetExtendMode)(
        ID2D1GradientStopCollection* This);
} ID2D1GradientStopCollectionVtbl;

struct ID2D1GradientStopCollection {
    const ID2D1GradientStopCollectionVtbl* lpVtbl;
};

typedef struct ID2D1RadialGradientBrushVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1RadialGradientBrush* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1RadialGradientBrush* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1RadialGradientBrush* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1RadialGradientBrush* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *SetOpacity)(
        ID2D1RadialGradientBrush* This,
        FLOAT opacity);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1RadialGradientBrush* This,
        const D2D1_MATRIX_3X2_F* transform);
    FLOAT (STDMETHODCALLTYPE *GetOpacity)(
        ID2D1RadialGradientBrush* This);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1RadialGradientBrush* This,
        D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *SetCenter)(
        ID2D1RadialGradientBrush* This,
        D2D1_POINT_2F center);
    void (STDMETHODCALLTYPE *SetGradientOriginOffset)(
        ID2D1RadialGradientBrush* This,
        D2D1_POINT_2F gradientOriginOffset);
    void (STDMETHODCALLTYPE *SetRadiusX)(
        ID2D1RadialGradientBrush* This,
        FLOAT radiusX);
    void (STDMETHODCALLTYPE *SetRadiusY)(
        ID2D1RadialGradientBrush* This,
        FLOAT radiusY);
    D2D1_POINT_2F (STDMETHODCALLTYPE *GetCenter)(
        ID2D1RadialGradientBrush* This);
    D2D1_POINT_2F (STDMETHODCALLTYPE *GetGradientOriginOffset)(
        ID2D1RadialGradientBrush* This);
    FLOAT (STDMETHODCALLTYPE *GetRadiusX)(
        ID2D1RadialGradientBrush* This);
    FLOAT (STDMETHODCALLTYPE *GetRadiusY)(
        ID2D1RadialGradientBrush* This);
    void (STDMETHODCALLTYPE *GetGradientStopCollection)(
        ID2D1RadialGradientBrush* This,
        ID2D1GradientStopCollection** gradientStopCollection);
} ID2D1RadialGradientBrushVtbl;

struct ID2D1RadialGradientBrush {
    const ID2D1RadialGradientBrushVtbl* lpVtbl;
};

typedef struct ID2D1BitmapRenderTargetVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1BitmapRenderTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1BitmapRenderTarget* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1BitmapRenderTarget* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1BitmapRenderTarget* This,
        ID2D1Factory** factory);
    HRESULT (STDMETHODCALLTYPE *CreateBitmap)(
        ID2D1BitmapRenderTarget* This,
        D2D1_SIZE_U size,
        const void* srcData,
        UINT32 pitch,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapFromWicBitmap)(
        ID2D1BitmapRenderTarget* This,
        IWICBitmapSource* wicBitmapSource,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateSharedBitmap)(
        ID2D1BitmapRenderTarget* This,
        REFIID riid,
        void* data,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapBrush)(
        ID2D1BitmapRenderTarget* This,
        ID2D1Bitmap* bitmap,
        const D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1BitmapBrush** bitmapBrush);
    HRESULT (STDMETHODCALLTYPE *CreateSolidColorBrush)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_COLOR_F* color,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1SolidColorBrush** solidColorBrush);
    HRESULT (STDMETHODCALLTYPE *CreateGradientStopCollection)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_GRADIENT_STOP* gradientStops,
        UINT32 gradientStopCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        ID2D1GradientStopCollection** gradientStopCollection);
    HRESULT (STDMETHODCALLTYPE *CreateLinearGradientBrush)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1LinearGradientBrush** linearGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateRadialGradientBrush)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1RadialGradientBrush** radialGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateCompatibleRenderTarget)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_SIZE_F* desiredSize,
        const D2D1_SIZE_U* desiredPixelSize,
        const D2D1_PIXEL_FORMAT* desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        ID2D1BitmapRenderTarget** bitmapRenderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateLayer)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_SIZE_F* size,
        ID2D1Layer** layer);
    HRESULT (STDMETHODCALLTYPE *CreateDrawingStateBlock)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription,
        IDWriteRenderingParams* textRenderingParams,
        ID2D1DrawingStateBlock** drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushLayer)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_LAYER_PARAMETERS* layerParameters,
        ID2D1Layer* layer);
    HRESULT (STDMETHODCALLTYPE *PopLayer)(
        ID2D1BitmapRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *Flush)(
        ID2D1BitmapRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    HRESULT (STDMETHODCALLTYPE *SaveDrawingState)(
        ID2D1BitmapRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *RestoreDrawingState)(
        ID2D1BitmapRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushAxisAlignedClip)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_RECT_F* clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode);
    HRESULT (STDMETHODCALLTYPE *PopAxisAlignedClip)(
        ID2D1BitmapRenderTarget* This);
    void (STDMETHODCALLTYPE *Clear)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_COLOR_F* clearColor);
    void (STDMETHODCALLTYPE *BeginDraw)(
        ID2D1BitmapRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *EndDraw)(
        ID2D1BitmapRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    D2D1_PIXEL_FORMAT (STDMETHODCALLTYPE *GetPixelFormat)(
        ID2D1BitmapRenderTarget* This);
    void (STDMETHODCALLTYPE *SetDpi)(
        ID2D1BitmapRenderTarget* This,
        FLOAT dpiX,
        FLOAT dpiY);
    void (STDMETHODCALLTYPE *GetDpi)(
        ID2D1BitmapRenderTarget* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    D2D1_SIZE_F (STDMETHODCALLTYPE *GetSize)(
        ID2D1BitmapRenderTarget* This);
    D2D1_SIZE_U (STDMETHODCALLTYPE *GetPixelSize)(
        ID2D1BitmapRenderTarget* This);
    UINT32 (STDMETHODCALLTYPE *GetMaximumBitmapSize)(
        ID2D1BitmapRenderTarget* This);
    BOOL (STDMETHODCALLTYPE *IsSupported)(
        ID2D1BitmapRenderTarget* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties);
} ID2D1BitmapRenderTargetVtbl;

struct ID2D1BitmapRenderTarget {
    const ID2D1BitmapRenderTargetVtbl* lpVtbl;
};

typedef struct ID2D1ResourceVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1Resource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1Resource* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1Resource* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1Resource* This,
        ID2D1Factory** factory);
} ID2D1ResourceVtbl;

struct ID2D1Resource {
    const ID2D1ResourceVtbl* lpVtbl;
};

typedef struct ID2D1BitmapVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1Bitmap* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1Bitmap* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1Bitmap* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1Bitmap* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *GetSize)(
        ID2D1Bitmap* This,
        D2D1_SIZE_F* size);
    void (STDMETHODCALLTYPE *GetPixelSize)(
        ID2D1Bitmap* This,
        D2D1_SIZE_U* pixelSize);
    void (STDMETHODCALLTYPE *GetPixelFormat)(
        ID2D1Bitmap* This,
        D2D1_PIXEL_FORMAT* pixelFormat);
    void (STDMETHODCALLTYPE *GetDpi)(
        ID2D1Bitmap* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    HRESULT (STDMETHODCALLTYPE *CopyFromBitmap)(
        ID2D1Bitmap* This,
        const D2D1_POINT_2F* destPoint,
        ID2D1Bitmap* bitmap,
        const D2D1_RECT_F* srcRect);
    HRESULT (STDMETHODCALLTYPE *CopyFromRenderTarget)(
        ID2D1Bitmap* This,
        const D2D1_POINT_2F* destPoint,
        ID2D1RenderTarget* renderTarget,
        const D2D1_RECT_F* srcRect);
    HRESULT (STDMETHODCALLTYPE *CopyFromMemory)(
        ID2D1Bitmap* This,
        const D2D1_RECT_F* dstRect,
        const void* srcData,
        UINT32 pitch);
} ID2D1BitmapVtbl;

struct ID2D1Bitmap {
    const ID2D1BitmapVtbl* lpVtbl;
};

typedef struct ID2D1BrushVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1Brush* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1Brush* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1Brush* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1Brush* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *SetOpacity)(
        ID2D1Brush* This,
        FLOAT opacity);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1Brush* This,
        const D2D1_MATRIX_3X2_F* transform);
    FLOAT (STDMETHODCALLTYPE *GetOpacity)(
        ID2D1Brush* This);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1Brush* This,
        D2D1_MATRIX_3X2_F* transform);
} ID2D1BrushVtbl;

struct ID2D1Brush {
    const ID2D1BrushVtbl* lpVtbl;
};

typedef struct ID2D1SolidColorBrushVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1SolidColorBrush* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1SolidColorBrush* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1SolidColorBrush* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1SolidColorBrush* This,
        ID2D1Factory** factory);
    void (STDMETHODCALLTYPE *SetOpacity)(
        ID2D1SolidColorBrush* This,
        FLOAT opacity);
    void (STDMETHODCALLTYPE *SetTransform)(
        ID2D1SolidColorBrush* This,
        const D2D1_MATRIX_3X2_F* transform);
    FLOAT (STDMETHODCALLTYPE *GetOpacity)(
        ID2D1SolidColorBrush* This);
    void (STDMETHODCALLTYPE *GetTransform)(
        ID2D1SolidColorBrush* This,
        D2D1_MATRIX_3X2_F* transform);
    void (STDMETHODCALLTYPE *SetColor)(
        ID2D1SolidColorBrush* This,
        const D2D1_COLOR_F* color);
    void (STDMETHODCALLTYPE *GetColor)(
        ID2D1SolidColorBrush* This,
        D2D1_COLOR_F* color);
} ID2D1SolidColorBrushVtbl;

struct ID2D1SolidColorBrush {
    const ID2D1SolidColorBrushVtbl* lpVtbl;
};

typedef struct ID2D1RenderTargetVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1RenderTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1RenderTarget* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1RenderTarget* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1RenderTarget* This,
        ID2D1Factory** factory);
    HRESULT (STDMETHODCALLTYPE *CreateBitmap)(
        ID2D1RenderTarget* This,
        D2D1_SIZE_U size,
        const void* srcData,
        UINT32 pitch,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapFromWicBitmap)(
        ID2D1RenderTarget* This,
        IWICBitmapSource* wicBitmapSource,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateSharedBitmap)(
        ID2D1RenderTarget* This,
        REFIID riid,
        void* data,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapBrush)(
        ID2D1RenderTarget* This,
        ID2D1Bitmap* bitmap,
        const D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1BitmapBrush** bitmapBrush);
    HRESULT (STDMETHODCALLTYPE *CreateSolidColorBrush)(
        ID2D1RenderTarget* This,
        const D2D1_COLOR_F* color,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1SolidColorBrush** solidColorBrush);
    HRESULT (STDMETHODCALLTYPE *CreateGradientStopCollection)(
        ID2D1RenderTarget* This,
        const D2D1_GRADIENT_STOP* gradientStops,
        UINT32 gradientStopCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        ID2D1GradientStopCollection** gradientStopCollection);
    HRESULT (STDMETHODCALLTYPE *CreateLinearGradientBrush)(
        ID2D1RenderTarget* This,
        const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1LinearGradientBrush** linearGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateRadialGradientBrush)(
        ID2D1RenderTarget* This,
        const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1RadialGradientBrush** radialGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateCompatibleRenderTarget)(
        ID2D1RenderTarget* This,
        const D2D1_SIZE_F* desiredSize,
        const D2D1_SIZE_U* desiredPixelSize,
        const D2D1_PIXEL_FORMAT* desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        ID2D1BitmapRenderTarget** bitmapRenderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateLayer)(
        ID2D1RenderTarget* This,
        const D2D1_SIZE_F* size,
        ID2D1Layer** layer);
    HRESULT (STDMETHODCALLTYPE *CreateDrawingStateBlock)(
        ID2D1RenderTarget* This,
        const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription,
        IDWriteRenderingParams* textRenderingParams,
        ID2D1DrawingStateBlock** drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushLayer)(
        ID2D1RenderTarget* This,
        const D2D1_LAYER_PARAMETERS* layerParameters,
        ID2D1Layer* layer);
    HRESULT (STDMETHODCALLTYPE *PopLayer)(
        ID2D1RenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *Flush)(
        ID2D1RenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    HRESULT (STDMETHODCALLTYPE *SaveDrawingState)(
        ID2D1RenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *RestoreDrawingState)(
        ID2D1RenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushAxisAlignedClip)(
        ID2D1RenderTarget* This,
        const D2D1_RECT_F* clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode);
    HRESULT (STDMETHODCALLTYPE *PopAxisAlignedClip)(
        ID2D1RenderTarget* This);
    void (STDMETHODCALLTYPE *Clear)(
        ID2D1RenderTarget* This,
        const D2D1_COLOR_F* clearColor);
    void (STDMETHODCALLTYPE *BeginDraw)(
        ID2D1RenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *EndDraw)(
        ID2D1RenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    D2D1_PIXEL_FORMAT (STDMETHODCALLTYPE *GetPixelFormat)(
        ID2D1RenderTarget* This);
    void (STDMETHODCALLTYPE *SetDpi)(
        ID2D1RenderTarget* This,
        FLOAT dpiX,
        FLOAT dpiY);
    void (STDMETHODCALLTYPE *GetDpi)(
        ID2D1RenderTarget* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    D2D1_SIZE_F (STDMETHODCALLTYPE *GetSize)(
        ID2D1RenderTarget* This);
    D2D1_SIZE_U (STDMETHODCALLTYPE *GetPixelSize)(
        ID2D1RenderTarget* This);
    UINT32 (STDMETHODCALLTYPE *GetMaximumBitmapSize)(
        ID2D1RenderTarget* This);
    BOOL (STDMETHODCALLTYPE *IsSupported)(
        ID2D1RenderTarget* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties);
} ID2D1RenderTargetVtbl;

struct ID2D1RenderTarget {
    const ID2D1RenderTargetVtbl* lpVtbl;
};

typedef struct ID2D1FactoryVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1Factory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1Factory* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1Factory* This);
    HRESULT (STDMETHODCALLTYPE *ReloadSystemMetrics)(
        ID2D1Factory* This);
    void (STDMETHODCALLTYPE *GetDesktopDpi)(
        ID2D1Factory* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    HRESULT (STDMETHODCALLTYPE *CreateRectangleGeometry)(
        ID2D1Factory* This,
        const D2D1_RECT_F* rectangle,
        ID2D1RectangleGeometry** rectangleGeometry);
    HRESULT (STDMETHODCALLTYPE *CreateRoundedRectangleGeometry)(
        ID2D1Factory* This,
        const D2D1_ROUNDED_RECT* roundedRectangle,
        ID2D1RoundedRectangleGeometry** roundedRectangleGeometry);
    HRESULT (STDMETHODCALLTYPE *CreateEllipseGeometry)(
        ID2D1Factory* This,
        const D2D1_ELLIPSE* ellipse,
        ID2D1EllipseGeometry** ellipseGeometry);
    HRESULT (STDMETHODCALLTYPE *CreateGeometryGroup)(
        ID2D1Factory* This,
        D2D1_FILL_MODE fillMode,
        ID2D1Geometry** geometries,
        UINT32 geometriesCount,
        ID2D1GeometryGroup** geometryGroup);
    HRESULT (STDMETHODCALLTYPE *CreateTransformedGeometry)(
        ID2D1Factory* This,
        ID2D1Geometry* sourceGeometry,
        const D2D1_MATRIX_3X2_F* transform,
        ID2D1TransformedGeometry** transformedGeometry);
    HRESULT (STDMETHODCALLTYPE *CreatePathGeometry)(
        ID2D1Factory* This,
        ID2D1PathGeometry** pathGeometry);
    HRESULT (STDMETHODCALLTYPE *CreateStrokeStyle)(
        ID2D1Factory* This,
        const D2D1_STROKE_STYLE_PROPERTIES* strokeStyleProperties,
        const FLOAT* dashes,
        UINT32 dashesCount,
        ID2D1StrokeStyle** strokeStyle);
    HRESULT (STDMETHODCALLTYPE *CreateDrawingStateBlock)(
        ID2D1Factory* This,
        const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription,
        IDWriteRenderingParams* textRenderingParams,
        ID2D1DrawingStateBlock** drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *CreateWicBitmapRenderTarget)(
        ID2D1Factory* This,
        IWICBitmap* target,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
        ID2D1RenderTarget** renderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateHwndRenderTarget)(
        ID2D1Factory* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
        const D2D1_HWND_RENDER_TARGET_PROPERTIES* hwndRenderTargetProperties,
        ID2D1HwndRenderTarget** hwndRenderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateDxgiSurfaceRenderTarget)(
        ID2D1Factory* This,
        IDXGISurface* dxgiSurface,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
        ID2D1RenderTarget** renderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateDCRenderTarget)(
        ID2D1Factory* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,
        ID2D1DCRenderTarget** dcRenderTarget);
} ID2D1FactoryVtbl;

struct ID2D1Factory {
    const ID2D1FactoryVtbl* lpVtbl;
};

typedef struct ID2D1HwndRenderTargetVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID2D1HwndRenderTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ID2D1HwndRenderTarget* This);
    ULONG (STDMETHODCALLTYPE *Release)(ID2D1HwndRenderTarget* This);
    void (STDMETHODCALLTYPE *GetFactory)(
        ID2D1HwndRenderTarget* This,
        ID2D1Factory** factory);
    HRESULT (STDMETHODCALLTYPE *CreateBitmap)(
        ID2D1HwndRenderTarget* This,
        D2D1_SIZE_U size,
        const void* srcData,
        UINT32 pitch,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapFromWicBitmap)(
        ID2D1HwndRenderTarget* This,
        IWICBitmapSource* wicBitmapSource,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateSharedBitmap)(
        ID2D1HwndRenderTarget* This,
        REFIID riid,
        void* data,
        const D2D1_BITMAP_PROPERTIES* bitmapProperties,
        ID2D1Bitmap** bitmap);
    HRESULT (STDMETHODCALLTYPE *CreateBitmapBrush)(
        ID2D1HwndRenderTarget* This,
        ID2D1Bitmap* bitmap,
        const D2D1_BITMAP_BRUSH_PROPERTIES* bitmapBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1BitmapBrush** bitmapBrush);
    HRESULT (STDMETHODCALLTYPE *CreateSolidColorBrush)(
        ID2D1HwndRenderTarget* This,
        const D2D1_COLOR_F* color,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1SolidColorBrush** solidColorBrush);
    HRESULT (STDMETHODCALLTYPE *CreateGradientStopCollection)(
        ID2D1HwndRenderTarget* This,
        const D2D1_GRADIENT_STOP* gradientStops,
        UINT32 gradientStopCount,
        D2D1_GAMMA colorInterpolationGamma,
        D2D1_EXTEND_MODE extendMode,
        ID2D1GradientStopCollection** gradientStopCollection);
    HRESULT (STDMETHODCALLTYPE *CreateLinearGradientBrush)(
        ID2D1HwndRenderTarget* This,
        const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linearGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1LinearGradientBrush** linearGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateRadialGradientBrush)(
        ID2D1HwndRenderTarget* This,
        const D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES* radialGradientBrushProperties,
        const D2D1_BRUSH_PROPERTIES* brushProperties,
        ID2D1GradientStopCollection* gradientStopCollection,
        ID2D1RadialGradientBrush** radialGradientBrush);
    HRESULT (STDMETHODCALLTYPE *CreateCompatibleRenderTarget)(
        ID2D1HwndRenderTarget* This,
        const D2D1_SIZE_F* desiredSize,
        const D2D1_SIZE_U* desiredPixelSize,
        const D2D1_PIXEL_FORMAT* desiredFormat,
        D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS options,
        ID2D1BitmapRenderTarget** bitmapRenderTarget);
    HRESULT (STDMETHODCALLTYPE *CreateLayer)(
        ID2D1HwndRenderTarget* This,
        const D2D1_SIZE_F* size,
        ID2D1Layer** layer);
    HRESULT (STDMETHODCALLTYPE *CreateDrawingStateBlock)(
        ID2D1HwndRenderTarget* This,
        const D2D1_DRAWING_STATE_DESCRIPTION* drawingStateDescription,
        IDWriteRenderingParams* textRenderingParams,
        ID2D1DrawingStateBlock** drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushLayer)(
        ID2D1HwndRenderTarget* This,
        const D2D1_LAYER_PARAMETERS* layerParameters,
        ID2D1Layer* layer);
    HRESULT (STDMETHODCALLTYPE *PopLayer)(
        ID2D1HwndRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *Flush)(
        ID2D1HwndRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    HRESULT (STDMETHODCALLTYPE *SaveDrawingState)(
        ID2D1HwndRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *RestoreDrawingState)(
        ID2D1HwndRenderTarget* This,
        ID2D1DrawingStateBlock* drawingStateBlock);
    HRESULT (STDMETHODCALLTYPE *PushAxisAlignedClip)(
        ID2D1HwndRenderTarget* This,
        const D2D1_RECT_F* clipRect,
        D2D1_ANTIALIAS_MODE antialiasMode);
    HRESULT (STDMETHODCALLTYPE *PopAxisAlignedClip)(
        ID2D1HwndRenderTarget* This);
    void (STDMETHODCALLTYPE *Clear)(
        ID2D1HwndRenderTarget* This,
        const D2D1_COLOR_F* clearColor);
    void (STDMETHODCALLTYPE *BeginDraw)(
        ID2D1HwndRenderTarget* This);
    HRESULT (STDMETHODCALLTYPE *EndDraw)(
        ID2D1HwndRenderTarget* This,
        D2D1_TAG* tag1,
        D2D1_TAG* tag2);
    D2D1_PIXEL_FORMAT (STDMETHODCALLTYPE *GetPixelFormat)(
        ID2D1HwndRenderTarget* This);
    void (STDMETHODCALLTYPE *SetDpi)(
        ID2D1HwndRenderTarget* This,
        FLOAT dpiX,
        FLOAT dpiY);
    void (STDMETHODCALLTYPE *GetDpi)(
        ID2D1HwndRenderTarget* This,
        FLOAT* dpiX,
        FLOAT* dpiY);
    D2D1_SIZE_F (STDMETHODCALLTYPE *GetSize)(
        ID2D1HwndRenderTarget* This);
    D2D1_SIZE_U (STDMETHODCALLTYPE *GetPixelSize)(
        ID2D1HwndRenderTarget* This);
    UINT32 (STDMETHODCALLTYPE *GetMaximumBitmapSize)(
        ID2D1HwndRenderTarget* This);
    BOOL (STDMETHODCALLTYPE *IsSupported)(
        ID2D1HwndRenderTarget* This,
        const D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties);
} ID2D1HwndRenderTargetVtbl;

struct ID2D1HwndRenderTarget {
    const ID2D1HwndRenderTargetVtbl* lpVtbl;
};

static const D2D1_MATRIX_3X2_F D2D1_MATRIX_3X2_F_IDENTITY = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

#ifdef __cplusplus
} // extern "C"
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#endif // DirectDraw_h
