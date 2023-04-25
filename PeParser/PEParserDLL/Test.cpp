#define PEPARSER_IMPORT_LIBRARY
#include <iostream>
#include "../Declarations.h"
#include "../ExplicitTemplateInstances.h"
#include "../PEParser.h"
extern "C" __declspec(dllexport) pPEParserHandle * __cdecl openFile(pPEParserHandle);
extern "C" __declspec(dllimport) void __cdecl test();
int main() {
    test();
	PEParserHandle pEParserHandle = {};
	openFile(&pEParserHandle);
	//PEParserNamespace::openFile<const wchar_t*, PEParserNamespace::PEParser>({}, {});
}