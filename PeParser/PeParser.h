#include "Preprocessor.h"
#include <Windows.h>
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct PEParserFunctionExecutionLog {
		bool failed;
		union alignas(64) {
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
	} *pPEParserFunctionExecutionLog;
	typedef struct PEParserSignatur {
		const char* Signatur;
		const char* UnmangledSig;
	} *pPEParserSignatur;
	typedef struct PEParser
	{
		unsigned int PEParserStructurType;
		union {
			PEParserFunctionExecutionLog pEParserFunctionExecutionLog;
			PEParserSignatur pEParserSignatur;
		}Dummy;
	} *pPEParser;


	typedef struct PEParserHandle
	{
		pPEParser ppEParser;		
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	typedef struct PEParserHeader
	{
		pPEParser ppEParser;
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		PIMAGE_FILE_HEADER		pFileH;
		PIMAGE_OPTIONAL_HEADER	pOptH;
		PIMAGE_DATA_DIRECTORY	pDataDir;
		PIMAGE_DATA_DIRECTORY	pDataDirSingle;
	};


	typedef struct PEParserCombined
	{
		PEParser pEParser;
		PEParserHandle pEParserHandle;
		PEParserHeader pEParserHeader;
	};
#ifdef __cplusplus
}
#endif