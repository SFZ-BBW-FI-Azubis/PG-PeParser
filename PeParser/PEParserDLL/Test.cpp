#define PEPARSER_IMPORT_LIBRARY
#include <iostream>
#include "../Declarations.h"
#include "../ExplicitTemplateInstances.h"
#include "../PEParser.h"
extern "C" __declspec(dllexport) pPEParserHandle * __cdecl openFile(pPEParserHandleNoInheritence);
int main() {
	PEParserHandleNoInheritence pEParserHandle = {};
	openFile(&pEParserHandle);
	PEParserHandleNoInheritence cfx = PEParserHandleNoInheritence();
	PEParserNamespace::functionExecutionLog fx =
		PEParserNamespace::functionExecutionLog(
			(PEParserNamespace::functionExecutionLog*)&(cfx.ppEParser.Dummy.pEParserFunctionExecutionLog)
			, &cfx
		);
	cfx.ppEParser.Dummy.pEParserFunctionExecutionLog.failed = true;
	cfx.ppEParser.Dummy.pEParserFunctionExecutionLog.code.codeInt = 12345;
	std::cout << fx.getFailed(&cfx) << "\n";
	std::cout << fx.getCode(&cfx).codeInt << "\n";
	//PEParserNamespace::openFile<const wchar_t*, PEParserNamespace::PEParser>({}, {});
}