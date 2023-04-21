#pragma once
#include "Preprocessor.h"
#include <Windows.h>
//#include "PEParser.h"
namespace PEParserNamespace {
	typedef struct functionExecutionLog {
		bool failed;
		union alignas(64) {
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
	} PEParserfunctionExecutionLog;
	typedef struct signatur {
		const char* Signatur;
		const char* UnmangledSig;
	} PEParsersignatur;

	struct PEParserBase :
		virtual public functionExecutionLog,
		virtual public signatur 
	{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	typedef struct PEHEADER : 
		virtual public functionExecutionLog,
		virtual public signatur	
	{
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		PIMAGE_FILE_HEADER		pFileH;
		PIMAGE_OPTIONAL_HEADER	pOptH;
		PIMAGE_DATA_DIRECTORY	pDataDir;
		PIMAGE_DATA_DIRECTORY	pDataDirSingle;
	} PEParserHeader;
	struct PEParser : 
		public PEParserBase, 
		public PEParserHeader
	{

	};
}