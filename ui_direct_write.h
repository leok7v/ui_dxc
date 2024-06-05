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

#ifndef DIRECT_WRITE_IMPORT
#define DIRECT_WRITE_IMPORT __declspec(dllimport) WINAPI
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

struct IDWriteFactory {
    const IDWriteFactoryVtbl* lpVtbl;
};

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

EXTERN_C HRESULT DIRECT_WRITE_IMPORT DWriteCreateFactory(
    _In_ DWRITE_FACTORY_TYPE factoryType,
    _In_ REFIID iid,
    _COM_Outptr_ void** factory
    ) WIN_NOEXCEPT;

static inline HRESULT CreateDWriteFactory(IDWriteFactory** f) {
    return DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
        &IID_IDWriteFactory, (void**)f);
}

static inline HRESULT CreateTextFormat(
    IDWriteFactory* factory,
    const WCHAR* fontFamilyName,
    DWRITE_FONT_WEIGHT fontWeight,
    DWRITE_FONT_STYLE fontStyle,
    DWRITE_FONT_STRETCH fontStretch,
    FLOAT fontSize,
    const WCHAR* localeName,
    IDWriteTextFormat** textFormat) {
    return DIRECT_WRITE_CALL_COM_METHOD(factory, CreateTextFormat,
        fontFamilyName, NULL,  fontWeight, fontStyle, fontStretch,
        fontSize, localeName, textFormat);
}

#ifdef DIRECT_WRITE_DEFINE_UNUSED

typedef struct IDWriteTypographyVtbl {
    // IUnknown methods
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteTypography* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteTypography* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteTypography* This);

    // IDWriteTypography methods
    HRESULT (STDMETHODCALLTYPE *AddFontFeature)(
        IDWriteTypography* This,
        DWRITE_FONT_FEATURE fontFeature);
    UINT32 (STDMETHODCALLTYPE *GetFontFeatureCount)(
        IDWriteTypography* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFeature)(
        IDWriteTypography* This,
        UINT32 fontFeatureIndex,
        DWRITE_FONT_FEATURE* fontFeature);
} IDWriteTypographyVtbl;

struct IDWriteTypography {
    const IDWriteTypographyVtbl* lpVtbl;
};

DEFINE_GUID(IID_IDWriteTypography, // {55f1112b-1dc2-4b3c-9541-f46894ed85b6}
0x55f1112b, 0x1dc2, 0x4b3c, 0x95, 0x41, 0xf4, 0x68, 0x94, 0xed, 0x85, 0xb6);

typedef struct IDWriteTextLayoutVtbl {
    // IUnknown methods
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteTextLayout* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteTextLayout* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteTextLayout* This);
    // IDWriteTextFormat methods
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
        FLOAT incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *SetTrimming)(
        IDWriteTextLayout* This,
        const DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject* trimmingSign);
    HRESULT (STDMETHODCALLTYPE *SetLineSpacing)(
        IDWriteTextLayout* This,
        DWRITE_LINE_SPACING_METHOD lineSpacingMethod,
        FLOAT lineSpacing,
        FLOAT baseline);
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
        FLOAT* incrementalTabStop);
    HRESULT (STDMETHODCALLTYPE *GetTrimming)(
        IDWriteTextLayout* This,
        DWRITE_TRIMMING* trimmingOptions,
        IDWriteInlineObject** trimmingSign);
    HRESULT (STDMETHODCALLTYPE *GetLineSpacing)(
        IDWriteTextLayout* This,
        DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,
        FLOAT* lineSpacing,
        FLOAT* baseline);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection)(
        IDWriteTextLayout* This,
        IDWriteFontCollection** fontCollection);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName)(
        IDWriteTextLayout* This,
        WCHAR* fontFamilyName,
        UINT32 nameSize);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight)(IDWriteTextLayout* This);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle)(IDWriteTextLayout* This);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch)(IDWriteTextLayout* This);
    FLOAT (STDMETHODCALLTYPE *GetFontSize)(IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName)(
        IDWriteTextLayout* This,
        WCHAR* localeName,
        UINT32 nameSize);
    // IDWriteTextLayout methods
    HRESULT (STDMETHODCALLTYPE *SetMaxWidth)(
        IDWriteTextLayout* This,
        FLOAT maxWidth);
    HRESULT (STDMETHODCALLTYPE *SetMaxHeight)(
        IDWriteTextLayout* This,
        FLOAT maxHeight);
    HRESULT (STDMETHODCALLTYPE *SetFontCollection)(
        IDWriteTextLayout* This,
        IDWriteFontCollection* fontCollection,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetFontFamilyName)(
        IDWriteTextLayout* This,
        const WCHAR* fontFamilyName,
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
        FLOAT fontSize,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetUnderline)(
        IDWriteTextLayout* This,
        BOOL hasUnderline,
        DWRITE_TEXT_RANGE textRange);
    HRESULT (STDMETHODCALLTYPE *SetStrikethrough)(
        IDWriteTextLayout* This,
        BOOL hasStrikethrough,
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
        const WCHAR* localeName,
        DWRITE_TEXT_RANGE textRange);
    FLOAT (STDMETHODCALLTYPE *GetMaxWidth)(IDWriteTextLayout* This);
    FLOAT (STDMETHODCALLTYPE *GetMaxHeight)(IDWriteTextLayout* This);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection1)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        IDWriteFontCollection** fontCollection,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyNameLength)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        UINT32* nameLength,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetFontFamilyName2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        WCHAR* fontFamilyName,
        UINT32 nameSize,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetFontWeight2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetFontStyle2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetFontStretch2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    FLOAT (STDMETHODCALLTYPE *GetFontSize2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetUnderline)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        BOOL* hasUnderline,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetStrikethrough)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        BOOL* hasStrikethrough,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetDrawingEffect)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        IUnknown** drawingEffect,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetInlineObject)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        IDWriteInlineObject** inlineObject,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetTypography)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        IDWriteTypography** typography,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetLocaleNameLength)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        UINT32* nameLength,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName2)(
        IDWriteTextLayout* This,
        UINT32 currentPosition,
        WCHAR* localeName,
        UINT32 nameSize,
        DWRITE_TEXT_RANGE* textRange);
    HRESULT (STDMETHODCALLTYPE *Draw)(
        IDWriteTextLayout* This,
        void* clientDrawingContext,
        IDWriteTextRenderer* renderer,
        FLOAT originX,
        FLOAT originY);
    HRESULT (STDMETHODCALLTYPE *GetLineMetrics)(
        IDWriteTextLayout* This,
        DWRITE_LINE_METRICS* lineMetrics,
        UINT32 maxLineCount,
        UINT32* actualLineCount);
    HRESULT (STDMETHODCALLTYPE *GetMetrics)(
        IDWriteTextLayout* This,
        DWRITE_TEXT_METRICS* textMetrics);
    HRESULT (STDMETHODCALLTYPE *GetOverhangMetrics)(
        IDWriteTextLayout* This,
        DWRITE_OVERHANG_METRICS* overhangs);
    HRESULT (STDMETHODCALLTYPE *GetClusterMetrics)(
        IDWriteTextLayout* This,
        DWRITE_CLUSTER_METRICS* clusterMetrics,
        UINT32 maxClusterCount,
        UINT32* actualClusterCount);
    HRESULT (STDMETHODCALLTYPE *DetermineMinWidth)(
        IDWriteTextLayout* This,
        FLOAT* minWidth);
    HRESULT (STDMETHODCALLTYPE *HitTestPoint)(
        IDWriteTextLayout* This,
        FLOAT pointX,
        FLOAT pointY,
        BOOL* isTrailingHit,
        BOOL* isInside,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics);
    HRESULT (STDMETHODCALLTYPE *HitTestTextPosition)(
        IDWriteTextLayout* This,
        UINT32 textPosition,
        BOOL isTrailingHit,
        FLOAT* pointX,
        FLOAT* pointY,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics);
    HRESULT (STDMETHODCALLTYPE *HitTestTextRange)(
        IDWriteTextLayout* This,
        UINT32 textPosition,
        UINT32 textLength,
        FLOAT originX,
        FLOAT originY,
        DWRITE_HIT_TEST_METRICS* hitTestMetrics,
        UINT32 maxHitTestMetricsCount,
        UINT32* actualHitTestMetricsCount);
} IDWriteTextLayoutVtbl;

struct IDWriteTextLayout {
    const IDWriteTextLayoutVtbl* lpVtbl;
};

DEFINE_GUID(IID_IDWriteTextLayout, // {53737037-6D14-410B-9BFE-0B182BB70961}
0x53737037, 0x6D14, 0x410B, 0x9B, 0xFE, 0x0B, 0x18, 0x2B, 0xB7, 0x09, 0x61);

typedef struct IDWriteFontFaceVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFace* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFace* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFace* This);
    DWRITE_FONT_FACE_TYPE (STDMETHODCALLTYPE *GetType)(IDWriteFontFace* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFiles)(
        IDWriteFontFace* This,
        UINT32* numberOfFiles,
        IDWriteFontFile** fontFiles);
    UINT32 (STDMETHODCALLTYPE *GetIndex)(IDWriteFontFace* This);
    DWRITE_FONT_SIMULATIONS (STDMETHODCALLTYPE *GetSimulations)(IDWriteFontFace* This);
    BOOL (STDMETHODCALLTYPE *IsSymbolFont)(IDWriteFontFace* This);
    void (STDMETHODCALLTYPE *GetMetrics)(
        IDWriteFontFace* This,
        DWRITE_FONT_METRICS* fontMetrics);
    UINT16 (STDMETHODCALLTYPE *GetGlyphCount)(IDWriteFontFace* This);
    HRESULT (STDMETHODCALLTYPE *GetDesignGlyphMetrics)(
        IDWriteFontFace* This,
        const UINT16* glyphIndices,
        UINT32 glyphCount,
        DWRITE_GLYPH_METRICS* glyphMetrics,
        BOOL isSideways);
    HRESULT (STDMETHODCALLTYPE *GetGlyphIndices)(
        IDWriteFontFace* This,
        const UINT32* codePoints,
        UINT32 codePointCount,
        UINT16* glyphIndices);
    HRESULT (STDMETHODCALLTYPE *TryGetFontTable)(
        IDWriteFontFace* This,
        UINT32 openTypeTableTag,
        const void** tableData,
        UINT32* tableSize,
        void** tableContext,
        BOOL* exists);
    void (STDMETHODCALLTYPE *ReleaseFontTable)(
        IDWriteFontFace* This,
        void* tableContext);
    HRESULT (STDMETHODCALLTYPE *GetGlyphRunOutline)(
        IDWriteFontFace* This,
        FLOAT emSize,
        const UINT16* glyphIndices,
        const FLOAT* glyphAdvances,
        const DWRITE_GLYPH_OFFSET* glyphOffsets,
        UINT32 glyphCount,
        BOOL isSideways,
        BOOL isRightToLeft,
        ID2D1SimplifiedGeometrySink* geometrySink);
    HRESULT (STDMETHODCALLTYPE *GetRecommendedRenderingMode)(
        IDWriteFontFace* This,
        FLOAT emSize,
        FLOAT pixelsPerDip,
        DWRITE_MEASURING_MODE measuringMode,
        IDWriteRenderingParams* renderingParams,
        DWRITE_RENDERING_MODE* renderingMode);
    HRESULT (STDMETHODCALLTYPE *GetGdiCompatibleMetrics)(
        IDWriteFontFace* This,
        FLOAT emSize,
        FLOAT pixelsPerDip,
        const DWRITE_MATRIX* transform,
        DWRITE_FONT_METRICS* fontMetrics);
    HRESULT (STDMETHODCALLTYPE *GetGdiCompatibleGlyphMetrics)(
        IDWriteFontFace* This,
        FLOAT emSize,
        FLOAT pixelsPerDip,
        const DWRITE_MATRIX* transform,
        BOOL useGdiNatural,
        const UINT16* glyphIndices,
        UINT32 glyphCount,
        DWRITE_GLYPH_METRICS* glyphMetrics,
        BOOL isSideways);
} IDWriteFontFaceVtbl;

struct IDWriteFontFace {
    const IDWriteFontFaceVtbl* lpVtbl;
};

typedef struct IDWriteTextRendererVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteTextRenderer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteTextRenderer* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteTextRenderer* This);
    HRESULT (STDMETHODCALLTYPE *DrawGlyphRun)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        DWRITE_MEASURING_MODE measuringMode,
        const DWRITE_GLYPH_RUN* glyphRun,
        const DWRITE_GLYPH_RUN_DESCRIPTION* glyphRunDescription,
        IUnknown* clientDrawingEffect);
    HRESULT (STDMETHODCALLTYPE *DrawUnderline)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        const DWRITE_UNDERLINE* underline,
        IUnknown* clientDrawingEffect);
    HRESULT (STDMETHODCALLTYPE *DrawStrikethrough)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        FLOAT baselineOriginX,
        FLOAT baselineOriginY,
        const DWRITE_STRIKETHROUGH* strikethrough,
        IUnknown* clientDrawingEffect);
    HRESULT (STDMETHODCALLTYPE *DrawInlineObject)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        FLOAT originX,
        FLOAT originY,
        IDWriteInlineObject* inlineObject,
        BOOL isSideways,
        BOOL isRightToLeft,
        IUnknown* clientDrawingEffect);
    HRESULT (STDMETHODCALLTYPE *IsPixelSnappingDisabled)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        BOOL* isDisabled);
    HRESULT (STDMETHODCALLTYPE *GetCurrentTransform)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        DWRITE_MATRIX* transform);
    HRESULT (STDMETHODCALLTYPE *GetPixelsPerDip)(
        IDWriteTextRenderer* This,
        void* clientDrawingContext,
        FLOAT* pixelsPerDip);
} IDWriteTextRendererVtbl;

struct IDWriteTextRenderer {
    const IDWriteTextRendererVtbl* lpVtbl;
};

typedef struct IDWriteInlineObjectVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteInlineObject* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteInlineObject* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteInlineObject* This);
    HRESULT (STDMETHODCALLTYPE *Draw)(
        IDWriteInlineObject* This,
        void* clientDrawingContext,
        IDWriteTextRenderer* renderer,
        FLOAT originX,
        FLOAT originY,
        BOOL isSideways,
        BOOL isRightToLeft,
        IUnknown* clientDrawingEffect);
    HRESULT (STDMETHODCALLTYPE *GetMetrics)(
        IDWriteInlineObject* This,
        DWRITE_INLINE_OBJECT_METRICS* metrics);
    HRESULT (STDMETHODCALLTYPE *GetOverhangMetrics)(
        IDWriteInlineObject* This,
        DWRITE_OVERHANG_METRICS* overhangs);
    HRESULT (STDMETHODCALLTYPE *GetBreakConditions)(
        IDWriteInlineObject* This,
        DWRITE_BREAK_CONDITION* breakConditionBefore,
        DWRITE_BREAK_CONDITION* breakConditionAfter);
} IDWriteInlineObjectVtbl;

struct IDWriteInlineObject {
    const IDWriteInlineObjectVtbl* lpVtbl;
};

typedef struct IDWriteFontFileLoaderVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFileLoader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFileLoader* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFileLoader* This);
    HRESULT (STDMETHODCALLTYPE *CreateStreamFromKey)(
        IDWriteFontFileLoader* This,
        const void* fontFileReferenceKey,
        UINT32 fontFileReferenceKeySize,
        IDWriteFontFileStream** fontFileStream);
} IDWriteFontFileLoaderVtbl;

struct IDWriteFontFileLoader {
    const IDWriteFontFileLoaderVtbl* lpVtbl;
};


DEFINE_GUID(IID_IDWriteFontFileLoader, // {72755049-5ff7-435d-8348-4be97cfa6c7c}
0x72755049, 0x5ff7, 0x435d, 0x83, 0x48, 0x4b, 0xe9, 0x7c, 0xfa, 0x6c, 0x7c);

typedef struct IDWriteFontFileStreamVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFileStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFileStream* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFileStream* This);
    HRESULT (STDMETHODCALLTYPE *ReadFileFragment)(
        IDWriteFontFileStream* This,
        const void** fragmentStart,
        UINT64 fileOffset,
        UINT64 fragmentSize,
        void** fragmentContext);
    void (STDMETHODCALLTYPE *ReleaseFileFragment)(
        IDWriteFontFileStream* This,
        void* fragmentContext);
    HRESULT (STDMETHODCALLTYPE *GetFileSize)(
        IDWriteFontFileStream* This,
        UINT64* fileSize);
    HRESULT (STDMETHODCALLTYPE *GetLastWriteTime)(
        IDWriteFontFileStream* This,
        UINT64* lastWriteTime);
} IDWriteFontFileStreamVtbl;

struct IDWriteFontFileStream {
    const IDWriteFontFileStreamVtbl* lpVtbl;
};

DEFINE_GUID(IID_IDWriteFontFileStream,  // {6D4865FE-0AB8-4D91-9A4C-50A7A3C8E3DE}
0x6d4865fe, 0x0ab8, 0x4d91, 0x9a, 0x4c, 0x50, 0xa7, 0xa3, 0xc8, 0xe3, 0xde);

typedef struct IDWriteFontFileVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFile* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFile* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFile* This);
    HRESULT (STDMETHODCALLTYPE *GetReferenceKey)(
        IDWriteFontFile* This,
        const void** fontFileReferenceKey,
        UINT32* fontFileReferenceKeySize);
    HRESULT (STDMETHODCALLTYPE *GetLoader)(
        IDWriteFontFile* This,
        IDWriteFontFileLoader** fontFileLoader);
    HRESULT (STDMETHODCALLTYPE *Analyze)(
        IDWriteFontFile* This,
        BOOL* isSupportedFontType,
        DWRITE_FONT_FILE_TYPE* fontFileType,
        DWRITE_FONT_FACE_TYPE* fontFaceType,
        UINT32* numberOfFaces);
} IDWriteFontFileVtbl;

struct IDWriteFontFile {
    const IDWriteFontFileVtbl* lpVtbl;
};

typedef struct IDWriteFontVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFont* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFont* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFont* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFamily)(
        IDWriteFont* This,
        IDWriteFontFamily** fontFamily);
    DWRITE_FONT_WEIGHT (STDMETHODCALLTYPE *GetWeight)(IDWriteFont* This);
    DWRITE_FONT_STRETCH (STDMETHODCALLTYPE *GetStretch)(IDWriteFont* This);
    DWRITE_FONT_STYLE (STDMETHODCALLTYPE *GetStyle)(IDWriteFont* This);
    BOOL (STDMETHODCALLTYPE *IsSymbolFont)(IDWriteFont* This);
    HRESULT (STDMETHODCALLTYPE *GetFaceNames)(
        IDWriteFont* This,
        IDWriteLocalizedStrings** names);
    HRESULT (STDMETHODCALLTYPE *GetInformationalStrings)(
        IDWriteFont* This,
        DWRITE_INFORMATIONAL_STRING_ID informationalStringID,
        IDWriteLocalizedStrings** informationalStrings,
        BOOL* exists);
    DWRITE_FONT_SIMULATIONS (STDMETHODCALLTYPE *GetSimulations)(IDWriteFont* This);
    void (STDMETHODCALLTYPE *GetMetrics)(
        IDWriteFont* This,
        DWRITE_FONT_METRICS* fontMetrics);
    HRESULT (STDMETHODCALLTYPE *HasCharacter)(
        IDWriteFont* This,
        UINT32 unicodeValue,
        BOOL* exists);
    HRESULT (STDMETHODCALLTYPE *CreateFontFace)(
        IDWriteFont* This,
        IDWriteFontFace** fontFace);
} IDWriteFontVtbl;

struct IDWriteFont {
    const IDWriteFontVtbl* lpVtbl;
};

typedef struct IDWriteLocalizedStringsVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteLocalizedStrings* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteLocalizedStrings* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteLocalizedStrings* This);
    UINT32 (STDMETHODCALLTYPE *GetCount)(IDWriteLocalizedStrings* This);
    HRESULT (STDMETHODCALLTYPE *FindLocaleName)(
        IDWriteLocalizedStrings* This,
        const WCHAR* localeName,
        UINT32* index,
        BOOL* exists);
    HRESULT (STDMETHODCALLTYPE *GetLocaleNameLength)(
        IDWriteLocalizedStrings* This,
        UINT32 index,
        UINT32* length);
    HRESULT (STDMETHODCALLTYPE *GetLocaleName)(
        IDWriteLocalizedStrings* This,
        UINT32 index,
        WCHAR* localeName,
        UINT32 size);
    HRESULT (STDMETHODCALLTYPE *GetStringLength)(
        IDWriteLocalizedStrings* This,
        UINT32 index,
        UINT32* length);
    HRESULT (STDMETHODCALLTYPE *GetString)(
        IDWriteLocalizedStrings* This,
        UINT32 index,
        WCHAR* string,
        UINT32 size);
} IDWriteLocalizedStringsVtbl;

struct IDWriteLocalizedStrings {
    const IDWriteLocalizedStringsVtbl* lpVtbl;
};


typedef struct IDWriteFontFamilyVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFamily* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFamily* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFamily* This);
    HRESULT (STDMETHODCALLTYPE *GetFontCollection)(
        IDWriteFontFamily* This,
        IDWriteFontCollection** fontCollection);
    UINT32 (STDMETHODCALLTYPE *GetFontCount)(IDWriteFontFamily* This);
    HRESULT (STDMETHODCALLTYPE *GetFont)(
        IDWriteFontFamily* This,
        UINT32 index,
        IDWriteFont** font);
    HRESULT (STDMETHODCALLTYPE *GetFamilyNames)(
        IDWriteFontFamily* This,
        IDWriteLocalizedStrings** names);
} IDWriteFontFamilyVtbl;

struct IDWriteFontFamily {
    const IDWriteFontFamilyVtbl* lpVtbl;
};

typedef struct IDWriteFontCollectionVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontCollection* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontCollection* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontCollection* This);
    UINT32 (STDMETHODCALLTYPE *GetFontFamilyCount)(IDWriteFontCollection* This);
    HRESULT (STDMETHODCALLTYPE *GetFontFamily)(
        IDWriteFontCollection* This,
        UINT32 index,
        IDWriteFontFamily** fontFamily);
    HRESULT (STDMETHODCALLTYPE *FindFamilyName)(
        IDWriteFontCollection* This,
        const WCHAR* familyName,
        UINT32* index,
        BOOL* exists);
    HRESULT (STDMETHODCALLTYPE *GetFontFromFontFace)(
        IDWriteFontCollection* This,
        IDWriteFontFace* fontFace,
        IDWriteFont** font);
} IDWriteFontCollectionVtbl;

struct IDWriteFontCollection {
    const IDWriteFontCollectionVtbl* lpVtbl;
};

typedef struct IDWriteFontCollectionLoaderVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontCollectionLoader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontCollectionLoader* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontCollectionLoader* This);
    HRESULT (STDMETHODCALLTYPE *CreateEnumeratorFromKey)(
        IDWriteFontCollectionLoader* This,
        IDWriteFactory* factory,
        const void* collectionKey,
        UINT32 collectionKeySize,
        IDWriteFontFileEnumerator** fontFileEnumerator);
} IDWriteFontCollectionLoaderVtbl;

struct IDWriteFontCollectionLoader {
    const IDWriteFontCollectionLoaderVtbl* lpVtbl;
};

typedef struct IDWriteFontFileEnumeratorVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDWriteFontFileEnumerator* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDWriteFontFileEnumerator* This);
    ULONG (STDMETHODCALLTYPE *Release)(IDWriteFontFileEnumerator* This);
    HRESULT (STDMETHODCALLTYPE *MoveNext)(
        IDWriteFontFileEnumerator* This,
        BOOL* hasCurrentFile);
    HRESULT (STDMETHODCALLTYPE *GetCurrentFontFile)(
        IDWriteFontFileEnumerator* This,
        IDWriteFontFile** fontFile);
} IDWriteFontFileEnumeratorVtbl;

struct IDWriteFontFileEnumerator {
    const IDWriteFontFileEnumeratorVtbl* lpVtbl;
};

#endif


#ifdef __cplusplus
} // extern "C"
#endif

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#endif // DirectWrite_h
