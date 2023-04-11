#pragma once
#include <Windows.h>
namespace PEParserNamespace {
	class PEParserBase {
	public:
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	class PEHEADER {
	public:
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		IMAGE_FILE_HEADER		FileH;
		IMAGE_OPTIONAL_HEADER	OptH;
	};
	class functionExecutionLog {
	public:
		bool failed;
		union alignas(64){
			void* codeVoidptr;
			unsigned long codeUlong;
			int codeInt;
		} code;			//64bit alignment
	};
	class signatur {
	public:
		const char* Signatur;
		const char* UnmangledSig;
	};
	class PEParser : public PEParserBase, public PEHEADER, public functionExecutionLog, public signatur	{

	};
}