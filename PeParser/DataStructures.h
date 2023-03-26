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
		PIMAGE_SECTION_HEADER	pSecH;
		PIMAGE_SECTION_HEADER	pTextSec;
		PIMAGE_SECTION_HEADER* pSecHs;			// is const and immutable, but not the Data its pointing on. SecCount in FileHeader
		IMAGE_FILE_HEADER		FileH;
		IMAGE_OPTIONAL_HEADER	OptH;
	};
	class PEParser : public PEParserBase, public PEHEADER {

	};
}