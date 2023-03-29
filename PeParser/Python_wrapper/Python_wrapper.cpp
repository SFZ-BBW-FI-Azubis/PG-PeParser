#include "../PeParser.h"
#include "pch.h"
#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) PEParserNamespace::PEParserBase& _cdecl test(PEParserNamespace::PEParserBase* base) {
    printf("shitzttttttttttTTT\n");
    base->bytes = 12341234;
    return *base;
}
extern "C" __declspec(dllexport) PEParserNamespace::PEParser pEParser;
extern "C" __declspec(dllexport) int x = 100;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason)  {
        case DLL_PROCESS_ATTACH:    {
            printf("Initialize once for each new process...\n");
            break;
        }
        case DLL_THREAD_ATTACH: {
            printf("Do thread-specific initialization...\n");
            break;
        }
        case DLL_THREAD_DETACH:  {
            printf("Do thread-specific cleanup...\n");
            break;
        }
        case DLL_PROCESS_DETACH:    {
            printf("Perform any necessary cleanup...\n");
            break;
        }
    }
    return TRUE;
}