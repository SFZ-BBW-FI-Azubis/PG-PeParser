#define PEPARSER_IMPORT_C_LIBRARY
#define PEPARSER_IMPORT_LIBRARY
#include "../Declarations.h"
extern "C" __declspec(dllexport) pPEParserHandle* __cdecl openFile(pPEParserHandle ppEParserHandle) noexcept {
    //translate PEParserBase between PEParserHandle 
    const char name[] = "lololol";
    PEParserNamespace::PEParserBase ppEParserBase;
    ppEParserBase.hFile;
    PEParserNamespace::openFile<>(name, &ppEParserBase);
    std::cout << ppEParserBase.hFile << std::endl;
    return &ppEParserHandle;
}
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
        PEParserNamespace::openFile<>({}, {});
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