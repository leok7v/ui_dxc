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

// IDWriteTextFormat capable of rendering text with a specific font, size,
// and style.
// Can only set text and paragraph alignment, trimming, line spacing,
// tab stop, flow direction, and word wrapping.
// CANNOT change size!

// IDWriteTextLayout can layout and render text with a specific font, size,
// and style changing size but the text is fixed in the time of creation.
// IDWriteTextLayout can also render to GDI and other targets

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
        float incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *SetTrimming)(
        IDWriteTextFormat* This,
        const DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject* trimmingSign);
    HRESULT (STDMETHODCALLTYPE *SetLineSpacing)(
        IDWriteTextFormat* This,
        DWRITE_LINE_SPACING_METHOD lineSpacingMethod,
        float lineSpacing,
        float baseline);
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
        float* incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *GetTrimming)(
        IDWriteTextFormat* This,
        DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject** trimmingSign);
    HRESULT (STDMETHODCALLTYPE *GetLineSpacing)(
        IDWriteTextFormat* This,
        DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,
        float* lineSpacing,
        float* baseline);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection)(
        IDWriteTextFormat* This,
        IDWriteFontCollection** fontCollection);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyNameLength)(
        IDWriteTextFormat* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName)(
        IDWriteTextFormat* This,
        wchar_t* fontFamilyName,
        UINT32 nameSize);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight)(
        IDWriteTextFormat* This);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle)(
        IDWriteTextFormat* This);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch)(
        IDWriteTextFormat* This);
    float (STDMETHODCALLTYPE *GetFontSize)(
        IDWriteTextFormat* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleNameLength2)(
        IDWriteTextFormat* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName2)(
        IDWriteTextFormat* This,
        wchar_t* localeName,
        UINT32 nameSize);
} IDWriteTextFormatVtbl;

struct IDWriteTextFormat {
    const IDWriteTextFormatVtbl* lpVtbl;
};

DEFINE_GUID(IID_IDWriteTextFormat, // {9C906818-31D7-4FD3-A151-7C5E225DB55A}
0x9C906818, 0x31D7, 0x4FD3, 0xA1, 0x51, 0x7C, 0x5E, 0x22, 0x5D, 0xB5, 0x5A);

// https://learn.microsoft.com/en-us/windows/win32/directwrite/text-formatting-and-layout

typedef struct IDWriteTextLayoutVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteTextLayout* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteTextLayout* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *SetTextAlignment)(
        IDWriteTextLayout* This,
        DWRITE_TEXT_ALIGNMENT textAlignment);
    HRESULT (STDMETHODCALLTYPE *SetParagraphAlignment)(
        IDWriteTextLayout* This,
        DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);
    HRESULT (STDMETHODCALLTYPE *SetWordWrapping)(
        IDWriteTextLayout* This,
        DWRITE_WORD_WRAPPING wordWrapping);
    HRESULT (STDMETHODCALLTYPE *SetReadingDirection)(
        IDWriteTextLayout* This,
        DWRITE_READING_DIRECTION readingDirection);
    HRESULT (STDMETHODCALLTYPE *SetFlowDirection)(
        IDWriteTextLayout* This,
        DWRITE_FLOW_DIRECTION flowDirection);
    HRESULT (STDMETHODCALLTYPE *SetIncrementalTabStop)(
        IDWriteTextLayout* This,
        float incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *SetTrimming)(
        IDWriteTextLayout* This,
        const DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject* trimmingSign);
    HRESULT (STDMETHODCALLTYPE *SetLineSpacing)(
        IDWriteTextLayout* This,
        DWRITE_LINE_SPACING_METHOD lineSpacingMethod,
        float lineSpacing,
        float baseline);
    HRESULT (STDMETHODCALLTYPE *GetTextAlignment)(
        IDWriteTextLayout* This,
        DWRITE_TEXT_ALIGNMENT* textAlignment);
    HRESULT (STDMETHODCALLTYPE *GetParagraphAlignment)(
        IDWriteTextLayout* This,
        DWRITE_PARAGRAPH_ALIGNMENT* paragraphAlignment);
    HRESULT (STDMETHODCALLTYPE *GetWordWrapping)(
        IDWriteTextLayout* This,
        DWRITE_WORD_WRAPPING* wordWrapping);
    HRESULT (STDMETHODCALLTYPE *GetReadingDirection)(
        IDWriteTextLayout* This,
        DWRITE_READING_DIRECTION* readingDirection);
    HRESULT (STDMETHODCALLTYPE *GetFlowDirection)(
        IDWriteTextLayout* This,
        DWRITE_FLOW_DIRECTION* flowDirection);
    HRESULT (STDMETHODCALLTYPE *GetIncrementalTabStop)(
        IDWriteTextLayout* This,
        float* incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *GetTrimming)(
        IDWriteTextLayout* This,
        DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject** trimmingSign);
    HRESULT (STDMETHODCALLTYPE *GetLineSpacing)(
        IDWriteTextLayout* This,
        DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,
        float* lineSpacing,
        float* baseline);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection)(
        IDWriteTextLayout* This,
        IDWriteFontCollection** fontCollection);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyNameLength)(
        IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName)(
        IDWriteTextLayout* This,
        wchar_t* fontFamilyName,
        UINT32 nameSize);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight)(
        IDWriteTextLayout* This);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle)(
        IDWriteTextLayout* This);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch)(
        IDWriteTextLayout* This);
    float (STDMETHODCALLTYPE *GetFontSize)(
        IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleNameLength)(
        IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName)(
        IDWriteTextLayout* This,
        wchar_t* localeName,
        UINT32 nameSize);
    HRESULT (STDMETHODCALLTYPE *SetMaxWidth)(
        IDWriteTextLayout* This,
        float maxWidth);
    HRESULT (STDMETHODCALLTYPE *SetMaxHeight)(
        IDWriteTextLayout* This,
        float maxHeight);
    HRESULT (STDMETHODCALLTYPE *SetFontCollection)(
        IDWriteTextLayout* This,
        IDWriteFontCollection* fontCollection,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontFamilyName)(
        IDWriteTextLayout* This,
        const wchar_t* fontFamilyName,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontWeight)(
        IDWriteTextLayout* This,
        DWRITE_FONT_WEIGHT fontWeight,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontStyle)(
        IDWriteTextLayout* This,
        DWRITE_FONT_STYLE fontStyle,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontStretch)(
        IDWriteTextLayout* This,
        DWRITE_FONT_STRETCH fontStretch,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontSize)(
        IDWriteTextLayout* This,
        float fontSize,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetUnderline)(
        IDWriteTextLayout* This,
        int hasUnderline,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetStrikethrough)(
        IDWriteTextLayout* This,
        int hasStrikethrough,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetDrawingEffect)(
        IDWriteTextLayout* This,
        IUnknown* drawingEffect,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetInlineObject)(
        IDWriteTextLayout* This,
        IDWriteInlineObject* inlineObject,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetTypography)(
        IDWriteTextLayout* This,
        IDWriteTypography* typography,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetLocaleName)(
        IDWriteTextLayout* This,
        const wchar_t* localeName,
        DWRITE_TEXT_RANGE textRange);
    float (STDMETHODCALLTYPE *GetMaxWidth)(
        IDWriteTextLayout* This);
    float (STDMETHODCALLTYPE *GetMaxHeight)(
        IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        IDWriteFontCollection** fontCollection,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyNameLength1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        unsigned int* nameLength,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        wchar_t* fontFamilyName,
        unsigned int nameSize,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    float (STDMETHODCALLTYPE *GetFontSize1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetUnderline)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        int* hasUnderline,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetStrikethrough)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        int* hasStrikethrough,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetDrawingEffect)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        IUnknown** drawingEffect,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetInlineObject)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        IDWriteInlineObject** inlineObject,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetTypography)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        IDWriteTypography** typography,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetLocaleNameLength1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        unsigned int* nameLength,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName1)(
        IDWriteTextLayout* This,
        unsigned int currentPosition,
        wchar_t* localeName,
        unsigned int nameSize,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *Draw)(
        IDWriteTextLayout* This,
        void* clientDrawingContext,
        IDWriteTextRenderer* renderer,
        float originX,
        float originY);
    HRESULT (STDMETHODCALLTYPE *GetLineMetrics)(
        IDWriteTextLayout* This,
        DWRITE_LINE_METRICS* lineMetrics,
        unsigned int maxLineCount,
        unsigned int* actualLineCount);
    HRESULT (STDMETHODCALLTYPE *GetMetrics)(
        IDWriteTextLayout* This,
        DWRITE_TEXT_METRICS* textMetrics);
    HRESULT (STDMETHODCALLTYPE *GetOverhangMetrics)(
        IDWriteTextLayout* This,
        DWRITE_OVERHANG_METRICS* overhangs);
    HRESULT (STDMETHODCALLTYPE *GetClusterMetrics)(
        IDWriteTextLayout* This,
        DWRITE_CLUSTER_METRICS* clusterMetrics,
        unsigned int maxClusterCount,
        unsigned int* actualClusterCount);
    HRESULT (STDMETHODCALLTYPE *DetermineMinWidth)(
        IDWriteTextLayout* This,
        float* minWidth);
    HRESULT (STDMETHODCALLTYPE *HitTestPoint)(
        IDWriteTextLayout* This,
        float pointX,
        float pointY,
        int* isTrailingHit,
        int* isInside,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics);
    HRESULT (STDMETHODCALLTYPE *HitTestTextPosition)(
        IDWriteTextLayout* This,
        unsigned int textPosition,
        int isTrailingHit,
        float* pointX,
        float* pointY,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics);
    HRESULT (STDMETHODCALLTYPE *HitTestTextRange)(
        IDWriteTextLayout* This,
        unsigned int textPosition,
        unsigned int textLength,
        float originX,
        float originY,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics,
        unsigned int maxHitTestMetricsCount,
        unsigned int* actualHitTestMetricsCount);
} IDWriteTextLayoutVtbl;

struct IDWriteTextLayout {
    const IDWriteTextLayoutVtbl* lpVtbl;
};

DEFINE_GUID(IID_IDWriteTextLayout, // {53737037-6D14-410B-9BFE-0B182BB70961}
0x53737037, 0x6D14, 0x410B, 0x9B, 0xFE, 0x0B, 0x18, 0x2B, 0xB7, 0x09, 0x61);


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
        float gamma,
        float enhancedContrast,
        float clearTypeLevel,
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
        float fontSize,
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
        float maxWidth,
        float maxHeight,
        IDWriteTextLayout** textLayout);
    HRESULT (STDMETHODCALLTYPE *CreateGdiCompatibleTextLayout)(
        IDWriteFactory* This,
        const WCHAR* string,
        UINT32 stringLength,
        IDWriteTextFormat* textFormat,
        float layoutWidth,
        float layoutHeight,
        float pixelsPerDip,
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
        float pixelsPerDip,
        const DWRITE_MATRIX* transform,
        DWRITE_RENDERING_MODE renderingMode,
        DWRITE_MEASURING_MODE measuringMode,
        float baselineOriginX,
        float baselineOriginY,
        IDWriteGlyphRunAnalysis** glyphRunAnalysis);
} IDWriteFactoryVtbl;

struct IDWriteFactory { const IDWriteFactoryVtbl* lpVtbl; };

DEFINE_GUID(IID_IDWriteFactory, // {B859EE5A-D838-4B5B-A2E8-1ADC7D93DB48}
0xB859EE5A, 0xD838, 0x4B5B, 0xA2, 0xE8, 0x1A, 0xDC, 0x7D, 0x93, 0xDB, 0x48);

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
