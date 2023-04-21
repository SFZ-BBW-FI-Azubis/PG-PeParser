#define PEParserLibrary
#include <iostream>
#include "../Declarations.h"
namespace PEParserNamespace {
    template _declspec(dllimport) PEParser& _call openFile<const wchar_t*, PEParser>(const wchar_t*, PEParser*) noexcept;
    template _declspec(dllimport) PEParser& _call openFile<const char*, PEParser>(const char*, PEParser*) noexcept;
}

int main() {

	PEParserNamespace::openFile<const wchar_t*, PEParserNamespace::PEParser>({}, {});
}