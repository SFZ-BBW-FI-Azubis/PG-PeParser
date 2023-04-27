#define PEPARSER_IMPORT_C_LIBRARY
#define PEPARSER_IMPORT_LIBRARY
#include "../Declarations.h"

/*
* I have to manualy call each imported Function,
* to make it show up in ILT/IAT
* Damn it, this took me two days to figure out
*/



extern "C" __declspec(dllexport) pPEParserHandle* __cdecl openFile(pPEParserHandle ppEParserHandle) noexcept {
    //translate PEParserBase between PEParserHandle 
    PEParserNamespace::PEParser* ppEParser = nullptr;
    PEParserNamespace::PEParserBase* ppEParserBase = ppEParser;
    PEParserNamespace::PEParserHeader* ppEParserHeader = ppEParser;

    const char name[] = "C:/NeuerOrdner(2)/depends.exe";
    // I dont want to overwrite, ppEParserBase->hFile is pointing to (nullptr)
    PEParserNamespace::PEParserBase pEParserBase;
    //PEParserNamespace::"IntermedietCStruct" *Instance
    //ppEParserHandle->...
    //!!!note, that the members are not always layd out in declarationorder in memory
    //ppEParserBase->hFile = ppEParserHandle->hFile; // this does not work, obviesly
    PEParserNamespace::openFile<>(name, &pEParserBase);
    std::cout << ppEParser->hFile << std::endl;
    return &ppEParserHandle;

}       
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
        //PEParserNamespace::openFile<>({}, {});
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