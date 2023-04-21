#define PEPARSER_IMPORT_LIBRARY
#include <iostream>
#include "../Declarations.h"

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
extern "C" __declspec(dllimport) void __cdecl test();
int main() {
    test();
	PEParserNamespace::openFile<const wchar_t*, PEParserNamespace::PEParser>({}, {});
}