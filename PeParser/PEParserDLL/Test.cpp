#define PEPARSER_IMPORT_LIBRARY
#include <iostream>
#include "../Declarations.h"
#include "../ExplicitTemplateInstances.h"
#include "../PEParser.h"
extern "C" __declspec(dllexport) pPEParserHandle * __cdecl openFile(pPEParserHandleNoInheritence);
extern "C" __declspec(dllimport) void __cdecl test();
int main() {
    test();
	PEParserHandleNoInheritence pEParserHandle = {};
	openFile(&pEParserHandle);
	PEParserHandleNoInheritence cfx = PEParserHandleNoInheritence();
	PEParserNamespace::functionExecutionLog fx =
		PEParserNamespace::functionExecutionLog(
			reinterpret_cast<PEParserNamespace::functionExecutionLog*>(&(cfx.ppEParser.Dummy.pEParserFunctionExecutionLog))
		);

	//PEParserNamespace::openFile<const wchar_t*, PEParserNamespace::PEParser>({}, {});
}