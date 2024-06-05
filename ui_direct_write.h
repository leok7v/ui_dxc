#pragma once
#ifndef DirectWrite_h
#define DirectWrite_h
#include <windows.h>
#include <unknwn.h>
#include <dcommon.h>
#include <initguid.h>
#include "ui_direct_write_defs.h"

// https://github.com/tpn/winsdk-10/blob/master/Include/10.0.14393.0/um/dwrite.h

#ifdef __cplusplus
extern "C" {
#endif

#define DIRECT_WRITE_CALL_COM_METHOD(ptr, method, ...) \
    (ptr)->lpVtbl->method(ptr, ##__VA_ARGS__)

typedef struct IDWriteFactoryVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFactory* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFactory* This);
    HRESULT (STDMETHODCALLTYPE *GetSystemFontCollection)(
        IDWriteFactory* This,
        IDWriteFontCollection** fontCollection,
        BOOL checkForUpdates);
    HRESULT (STDMETHODCALLTYPE *CreateCustomFontCollection)(
        IDWriteFactory* This,
        IDWriteFontCollectionLoader* collectionLoader,
        const void* collectionKey,
        UINT32 collectionKeySize,
        IDWriteFontCollection** fontCollection);
    HRESULT (STDMETHODCALLTYPE *RegisterFontCollectionLoader)(
        IDWriteFactory* This,
        IDWriteFontCollectionLoader* fontCollectionLoader);
    HRESULT (STDMETHODCALLTYPE *UnregisterFontCollectionLoader)(
        IDWriteFactory* This,
        IDWriteFontCollectionLoader* fontCollectionLoader);
    HRESULT (STDMETHODCALLTYPE *CreateFontFileReference)(
        IDWriteFactory* This,
        const WCHAR* filePath,
        const FILETIME* lastWriteTime,
        IDWriteFontFile** fontFile);
    HRESULT (STDMETHODCALLTYPE *CreateCustomFontFileReference)(
        IDWriteFactory* This,
        const void* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        IDWriteFontFileLoader* fontFileLoader,
        IDWriteFontFile** fontFile);
    HRESULT (STDMETHODCALLTYPE *CreateFontFace)(
        IDWriteFactory* This,
        DWRITE_FONT_FACE_TYPE fontFaceType,
        UINT32 numberOfFiles,
        IDWriteFontFile* const* fontFiles,
        UINT32 faceIndex,
        DWRITE_FONT_SIMULATIONS fontFaceSimulationFlags,
        IDWriteFontFace** fontFace);
    HRESULT (STDMETHODCALLTYPE *CreateRenderingParams)(
        IDWriteFactory* This,
        IDWriteRenderingParams** renderingParams);
    HRESULT (STDMETHODCALLTYPE *CreateMonitorRenderingParams)(
        IDWriteFactory* This,
        HMONITOR monitor,
        IDWriteRenderingParams** renderingParams);
    HRESULT (STDMETHODCALLTYPE *CreateCustomRenderingParams)(
        IDWriteFactory* This,
        FLOAT gamma,
        FLOAT enhancedContrast,
        FLOAT clearTypeLevel,
        DWRITE_PIXEL_GEOMETRY pixelGeometry,
        DWRITE_RENDERING_MODE renderingMode,
        IDWriteRenderingParams** renderingParams);
    HRESULT (STDMETHODCALLTYPE *RegisterFontFileLoader)(
        IDWriteFactory* This,
        IDWriteFontFileLoader* fontFileLoader);
    HRESULT (STDMETHODCALLTYPE *UnregisterFontFileLoader)(
        IDWriteFactory* This,
        IDWriteFontFileLoader* fontFileLoader);
    HRESULT (STDMETHODCALLTYPE *CreateTextFormat)(
        IDWriteFactory* This,
        const WCHAR* fontFamilyName,
        IDWriteFontCollection* fontCollection,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_FONT_STYLE fontStyle,
        DWRITE_FONT_STRETCH fontStretch,
        FLOAT fontSize,
        const WCHAR* localeName,
        IDWriteTextFormat** textFormat);
    HRESULT (STDMETHODCALLTYPE *CreateTypography)(
        IDWriteFactory* This,
        IDWriteTypography** typography);
    HRESULT (STDMETHODCALLTYPE *GetGdiInterop)(
        IDWriteFactory* This,
        IDWriteGdiInterop** gdiInterop);
    HRESULT (STDMETHODCALLTYPE *CreateTextLayout)(
        IDWriteFactory* This,
        const WCHAR* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT maxWidth,
        FLOAT maxHeight,
        IDWriteTextLayout** textLayout);
    HRESULT (STDMETHODCALLTYPE *CreateGdiCompatibleTextLayout)(
        IDWriteFactory* This,
        const WCHAR* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        FLOAT layoutWidth,
        FLOAT layoutHeight,
        FLOAT pixelsPerDip,
        const DWRITE_MATRIX* transform,
        BOOL useGdiNatural,
        IDWriteTextLayout** textLayout);
    HRESULT (STDMETHODCALLTYPE *CreateEllipsisTrimmingSign)(
        IDWriteFactory* This,
        IDWriteTextFormat* textFormat,
        IDWriteInlineObject** trimmingSign);
    HRESULT (STDMETHODCALLTYPE *CreateTextAnalyzer)(
        IDWriteFactory* This,
        IDWriteTextAnalyzer** textAnalyzer);
    HRESULT (STDMETHODCALLTYPE *CreateNumberSubstitution)(
        IDWriteFactory* This,
        DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod,
        const WCHAR* localeName,
        BOOL ignoreUserOverride,
        IDWriteNumberSubstitution** numberSubstitution);
    HRESULT (STDMETHODCALLTYPE *CreateGlyphRunAnalysis)(
        IDWriteFactory* This,
        const DWRITE_GLYPH_RUN* glyphRun,
        FLOAT pixelsPerDip,
        const DWRITE_MATRIX* transform,
        DWRITE_RENDERING_MODE renderingMode,
        DWRITE_MEASURING_MODE measuringMode,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        IDWriteGlyphRunAnalysis** glyphRunAnalysis);
} IDWriteFactoryVtbl;

struct IDWriteFactory { const IDWriteFactoryVtbl* lpVtbl; };

DEFINE_GUID(IID_IDWriteFactory, // {B859EE5A-D838-4B5B-A2E8-1ADC7D93DB48}
0xB859EE5A, 0xD838, 0x4B5B, 0xA2, 0xE8, 0x1A, 0xDC, 0x7D, 0x93, 0xDB, 0x48);

typedef struct IDWriteTextFormatVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteTextFormat* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteTextFormat* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteTextFormat* This);
    HRESULT (STDMETHODCALLTYPE *SetTextAlignment)(
        IDWriteTextFormat* This,
        DWRITE_TEXT_ALIGNMENT textAlignment);
    HRESULT (STDMETHODCALLTYPE *SetParagraphAlignment)(
        IDWriteTextFormat* This,
        DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
    HRESULT (STDMETHODCALLTYPE *SetWordWrapping)(
        IDWriteTextFormat* This,
        DWRITE_WORD_WRAPPING wordWrapping);
    HRESULT (STDMETHODCALLTYPE *SetReadingDirection)(
        IDWriteTextFormat* This,
        DWRITE_READING_DIRECTION readingDirection);
    HRESULT (STDMETHODCALLTYPE *SetFlowDirection)(
        IDWriteTextFormat* This,
        DWRITE_FLOW_DIRECTION flowDirection);
    HRESULT (STDMETHODCALLTYPE *SetIncrementalTabStop)(
        IDWriteTextFormat* This,
        FLOAT incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *SetTrimming)(
        IDWriteTextFormat* This,
        const DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject* trimmingSign);
    HRESULT (STDMETHODCALLTYPE *SetLineSpacing)(
        IDWriteTextFormat* This,
        DWRITE_LINE_SPACING_METHOD lineSpacingMethod,
        FLOAT lineSpacing,
        FLOAT baseline);
    HRESULT (STDMETHODCALLTYPE *GetTextAlignment)(
        IDWriteTextFormat* This,
        DWRITE_TEXT_ALIGNMENT* textAlignment);
    HRESULT (STDMETHODCALLTYPE *GetParagraphAlignment)(
        IDWriteTextFormat* This,
        DWRITE_PARAGRAPH_ALIGNMENT* paragraphAlignment);
    HRESULT (STDMETHODCALLTYPE *GetWordWrapping)(
        IDWriteTextFormat* This,
        DWRITE_WORD_WRAPPING* wordWrapping);
    HRESULT (STDMETHODCALLTYPE *GetReadingDirection)(
        IDWriteTextFormat* This,
        DWRITE_READING_DIRECTION* readingDirection);
    HRESULT (STDMETHODCALLTYPE *GetFlowDirection)(
        IDWriteTextFormat* This,
        DWRITE_FLOW_DIRECTION* flowDirection);
    HRESULT (STDMETHODCALLTYPE *GetIncrementalTabStop)(
        IDWriteTextFormat* This,
        FLOAT* incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *GetTrimming)(
        IDWriteTextFormat* This,
        DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject** trimmingSign);
    HRESULT (STDMETHODCALLTYPE *GetLineSpacing)(
        IDWriteTextFormat* This,
        DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,
        FLOAT* lineSpacing,
        FLOAT* baseline);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection)(
        IDWriteTextFormat* This,
        IDWriteFontCollection** fontCollection);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName)(
        IDWriteTextFormat* This,
        WCHAR* fontFamilyName,
        UINT32 nameSize);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight)(IDWriteTextFormat* This);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle)(IDWriteTextFormat* This);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch)(IDWriteTextFormat* This);
    FLOAT (STDMETHODCALLTYPE *GetFontSize)(IDWriteTextFormat* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName)(
        IDWriteTextFormat* This,
        WCHAR* localeName,
        UINT32 nameSize);
    // Other methods omitted for brevity
} IDWriteTextFormatVtbl;

struct IDWriteTextFormat {
    const IDWriteTextFormatVtbl* lpVtbl;
};

#ifndef DIRECT_WRITE_IMPORT
#define DIRECT_WRITE_IMPORT __declspec(dllimport) WINAPI
#endif

EXTERN_C HRESULT DIRECT_WRITE_IMPORT DWriteCreateFactory(
    _In_ DWRITE_FACTORY_TYPE factoryType,
    _In_ REFIID iid,
    _COM_Outptr_ void** factory
    ) WIN_NOEXCEPT;

#ifdef __cplusplus
} // extern "C"
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#endif // DirectWrite_h
