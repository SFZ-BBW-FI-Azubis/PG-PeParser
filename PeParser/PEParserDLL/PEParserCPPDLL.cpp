#define PEPARSER_EXPORT_LIBRARY
#include "../Declarations.h"
extern "C" __declspec(dllexport) void __cdecl test() {
    
}
namespace PEParserNamespace {
    template PEP_LIB_API PEParser& _call openFile<const wchar_t*, PEParser>(const wchar_t*, PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call openFile<const char*, PEParser>(const char*, PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call getFileSize(PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call allocMemory(PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call readFile(PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call getImageHeaders(PEParser*) noexcept;
    template PEP_LIB_API PEParser& _call checkHeader(PEParser*) noexcept;
    template PEP_LIB_API bool _call mcompare(unsigned char, unsigned char) noexcept;
    template PEP_LIB_API bool _call mcompare(const unsigned char*, const  unsigned char*) noexcept;
    template PEP_LIB_API PEParser& _call getSection(PEParser*, unsigned char n) noexcept;
    template PEP_LIB_API PEParser& _call getSection(PEParser*, const unsigned char*) noexcept;
    template PEP_LIB_API PEParser& _call getDataDirectoryEntry(PEParser*, unsigned int) noexcept;
    template PEP_LIB_API PEParser& _call getLastError(PEParser*) noexcept;
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