#define PEPARSER_IMPORT_C_LIBRARY
#define PEPARSER_IMPORT_LIBRARY
#include "../Declarations.h"

/*
* I have to manualy call each imported Function,
* to make it show up in ILT/IAT
* Damn it, this took me two days to figure out
*/



extern "C" __declspec(dllexport) pPEParserHandleNoInheritence* __cdecl openFile(pPEParserHandleNoInheritence ppEParserHandle) noexcept {
    PEParserNamespace::PEParser ppEParser;                                      //temporary instance
    PEParserNamespace::PEParserBase* ppEParserBase = &ppEParser;
    PEParserNamespace::PEParserfunctionExecutionLog* ppEParserfx = &ppEParser;  //upcast
    PEParserNamespace::PEParsersignatur* ppEParsersig = &ppEParser;              //upcast

    ppEParserBase->hFile = ppEParserHandle->hFile;
    ppEParserBase->dwFileSize = ppEParserHandle->dwFileSize;
    ppEParserBase->bytes = ppEParserHandle->bytes;
    ppEParserBase->fileBuffer = ppEParserHandle->fileBuffer;
    ppEParserfx->setFailed(ppEParserHandle->ppEParser.Dummy.pEParserFunctionExecutionLog.failed);
    ppEParserfx->setCode(ppEParserHandle->ppEParser.Dummy.pEParserFunctionExecutionLog.code.codeVoidptr);
    ppEParsersig->Signatur = ppEParserHandle->ppEParser.Dummy.pEParserSignatur.Signatur;
    ppEParsersig->UnmangledSig = ppEParserHandle->ppEParser.Dummy.pEParserSignatur.UnmangledSig;
    
    const char name[] = "C:/NeuerOrdner(2)/depends.exe";
    PEParserNamespace::openFile<>(name, ppEParserBase);

    ppEParserHandle->hFile = ppEParserBase->hFile;
    ppEParserHandle->dwFileSize = ppEParserBase->dwFileSize;
    ppEParserHandle->bytes = ppEParserBase->bytes;
    ppEParserHandle->fileBuffer = ppEParserBase->fileBuffer;
    ppEParserHandle->ppEParser.Dummy.pEParserFunctionExecutionLog.failed = ppEParserfx->failed;
    ppEParserHandle->ppEParser.Dummy.pEParserFunctionExecutionLog.code.codeVoidptr = ppEParserfx->code.codeVoidptr;
    ppEParserHandle->ppEParser.Dummy.pEParserSignatur.Signatur = ppEParsersig->Signatur;
    ppEParserHandle->ppEParser.Dummy.pEParserSignatur.UnmangledSig = ppEParsersig->UnmangledSig;


    std::cout << ppEParserHandle->hFile << std::endl;
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