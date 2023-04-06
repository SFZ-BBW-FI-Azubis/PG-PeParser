#include "../Declarations.h"
#include "pch.h"
#include <windows.h>
#include <stdio.h>
//__declspec(code_seg("ffopenFile"))    except, I am not even sure how this could help
// work with .def Files                 export by ordinal
// write Linkerscripts, to resolve extern "C" problem when overloading by providing my own "namemangaling system"
// use pointers that point to every single explicite instantiation of template function
#define USEDEF
#ifdef USEDEF
    #define EXPORT
#endif // USEDEF

namespace PEParserNamespace {
    template EXPORT PEParser & _call openFile<>(
        const wchar_t*, PEParser*) noexcept;
    extern "C" template EXPORT PEParser & _call openFile<>(
        const char*, PEParser*) noexcept;
}

extern "C" EXPORT PEParserNamespace::PEParserBase& _cdecl test(PEParserNamespace::PEParserBase* base) {
    typedef PEParserNamespace::PEParser PEParser;
    PEParser peparser;

    wchar_t fileNamee[123] = L"C:/NeuerOrdner(2)/depends.exe";
    PEParserNamespace::openFile<const wchar_t*>(fileNamee, &peparser).hFile;

    return *base;
}
class PEHEADER {
public:
    PEParserNamespace::PEParserBase test;
};
extern "C" EXPORT PEHEADER & _cdecl test2(PEHEADER * base) {
    printf("torm\n");
    base->test.bytes = 12345;
    return *base;
}
extern "C" EXPORT PEParserNamespace::PEParser pEParser;
extern "C" EXPORT int x = 100;
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