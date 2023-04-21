#include "../Declarations.h"
#define EXPORT __declspec(dllexport)
#define _call _cdecl
extern "C" __declspec(dllexport) void __cdecl test() {
    
}
namespace PEParserNamespace {
    template __declspec(dllexport) PEParser& _call openFile<const wchar_t*, PEParser>(const wchar_t*, PEParser*) noexcept;
    template __declspec(dllexport) PEParser& _call openFile<const char*, PEParser>(const char*, PEParser*) noexcept;
    template EXPORT PEParser& _call getFileSize(PEParser*) noexcept;
    template EXPORT PEParser& _call allocMemory(PEParser*) noexcept;
    template EXPORT PEParser& _call readFile(PEParser*) noexcept;
    template EXPORT PEParser& _call getImageHeaders(PEParser*) noexcept;
    template EXPORT PEParser& _call checkHeader(PEParser*) noexcept;
    template EXPORT bool _call mcompare(unsigned char, unsigned char) noexcept;
    template EXPORT bool _call mcompare(const unsigned char*, const  unsigned char*) noexcept;
    template EXPORT PEParser& _call getSection(PEParser*, unsigned char n) noexcept;
    template EXPORT PEParser& _call getSection(PEParser*, const unsigned char*) noexcept;
    template EXPORT PEParser& _call getDataDirectoryEntry(PEParser*, unsigned int) noexcept;
    template EXPORT PEParser& _call getLastError(PEParser*) noexcept;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
        printf("Initialize once for each new process...\n");
        break;
    }
    case DLL_THREAD_ATTACH: {
        printf("Do thread-specific initialization...\n");
        break;
    }
    case DLL_THREAD_DETACH: {
        printf("Do thread-specific cleanup...\n");
        break;
    }
    case DLL_PROCESS_DETACH: {
        printf("Perform any necessary cleanup...\n");
        break;
    }
    }
    return TRUE;
}