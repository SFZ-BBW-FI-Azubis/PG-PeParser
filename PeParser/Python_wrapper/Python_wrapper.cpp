#include "../PeParser.h"
#include "pch.h"
#include <windows.h>
#include <stdio.h>

extern "C" __declspec(dllexport) PEParserNamespace::PEParserBase& _cdecl test(PEParserNamespace::PEParserBase* base) {
    printf("shitorm\n");
    base->bytes = 12345;
    return *base;
}
class PEHEADER {
public:
    PEParserNamespace::PEParserBase test;
};
extern "C" __declspec(dllexport) PEHEADER & _cdecl test2(PEHEADER * base) {
    printf("torm\n");
    base->test.bytes = 12345;
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