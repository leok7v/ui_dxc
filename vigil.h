#ifndef vigil_h
#define vigil_h // https://github.com/munificent/vigil
// exports: trace_line_va() trace_line() traceln() swear() wrong() fatal_if_error() 
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>
#pragma warning(push)
#pragma warning(disable: 4005) // macro redefinition
#include <ntstatus.h>
#pragma warning(pop)

#pragma push_macro("null")
#pragma push_macro("countof")

#undef null
#undef countof
#define countof(a) _countof(a)

#ifdef __cplusplus
#define null nullptr
extern "C" {
#else
#define null ((void*)0)
#endif

static void trace_line_va(const char* file, int32_t line, const char* func, 
        const char* format, va_list args) {
    DWORD error = GetLastError();
    errno_t en = errno;
    unsigned long de = _doserrno;
    char text[1024];
    vsnprintf(text, countof(text) - 1, format, args);
    text[countof(text) - 1] = 0x00;
    char loc[1024]; // location
    snprintf(loc, countof(loc) - 1, "%s(%d)", file, line);
    loc[countof(loc) - 1] = 0x00;
    char s[4 * 1024];
    static int32_t max_loc;
    static int32_t max_func;
    max_loc  = max(max_loc, (int)strlen(loc));
    max_func = max(max_func, (int)strlen(func));
    snprintf(s, countof(s) - 1, "%-*s: %-*s %s\n", max_loc, loc, max_func, func, text);
    s[countof(s) - 1] = 0x00;
    OutputDebugStringA(s);
    // restore errors state:
    _doserrno = de;
    errno = en;
    SetLastError(error);
}

static void trace_line(const char* file, int32_t line, const char* func, 
        const char* format, ...) {
    va_list args;
    va_start(args, format);
    trace_line_va(file, line, func, format, args);
    va_end(args);
}

#define traceln(...) trace_line(__FILE__, __LINE__, __func__, "" __VA_ARGS__)

static const char* err2str(DWORD error) {
    static char str[1024];
    const DWORD language_id = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
    DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    HMODULE module = null;
    HRESULT hr = (HRESULT)error;
    if ((error & 0xC0000000U) == 0xC0000000U) { 
        // https://stackoverflow.com/questions/25566234/how-to-convert-specific-ntstatus-value-to-the-hresult
        static HMODULE ntdll; // RtlNtStatusToDosError implies linking to ntdll
        if (ntdll == null) { ntdll = GetModuleHandleA("ntdll.dll"); }
        if (ntdll == null) { ntdll = LoadLibraryA("ntdll.dll"); }
        module = ntdll;
        hr = HRESULT_FROM_WIN32(RtlNtStatusToDosError((NTSTATUS)error));
        flags |= FORMAT_MESSAGE_FROM_HMODULE;
    } 
    DWORD bytes = FormatMessageA(flags, module, error, 
                                 language_id, str, countof(str) - 1, null);
    while (bytes > 0 && str[bytes] < 0x20) { bytes--; } // '\r' '\n' '\t' etc
    str[bytes] = 0;
    return str;
}

static inline bool wrong(const char* call, const char* file, int32_t line,
        const char* func, const char* format, ...) {
    errno_t en = errno;
    HRESULT error = HRESULT_FROM_WIN32(GetLastError()); 
    DWORD   de = _doserrno;
    trace_line(file, line, func, "assertion: \"%s\" failed", call);
    if (format != null && format[0] != 0) {
        va_list args;
        va_start(args, format);
        trace_line_va(file, line, func, format, args);
        va_end(args);

    }
    // extra error information that may be useful for debugging:
    if (error != 0) {
        trace_line(file, line, func, "GetLastError(): 0x%08X (%d) %s", 
            error, error, err2str((DWORD)error));
    }
    if (en != 0) {
        trace_line(file, line, func, "errno:          0x%08X (%d) %s", 
            en, en, strerror(en));
        trace_line(file, line, func, "doserrno:       0x%08X (%d) %s", 
            de, de, err2str(de));
    }
    DebugBreak();
    if ((void*)ExitProcess != null) { ExitProcess(1); }
    return false;
}

#define swear(b, ...) (!(b) ? \
    wrong(#b, __FILE__, __LINE__, __func__, "" __VA_ARGS__) : true)

// https://learn.microsoft.com/en-us/windows/win32/com/using-macros-for-error-handling

#define fatal_if_error(hr, ...) swear(!IS_ERROR(hr), "" __VA_ARGS__)
 
#ifdef __cplusplus
} // extern "C"
#endif

#pragma pop_macro("countof")
#pragma pop_macro("null")

#pragma comment(lib, "ntdll")
#pragma comment(lib, "kernel32")

#endif // vigil_h
