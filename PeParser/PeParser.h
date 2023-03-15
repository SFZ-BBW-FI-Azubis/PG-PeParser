// PeParser.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <iostream>
#include <Windows.h>
#include <typeinfo>
namespace PEParserNamespace {
	//concepts
	int test;
	template<typename T> concept is_char = std::same_as<T, const char*>;
	template<typename T> concept is_wchar_t = std::same_as<T, const wchar_t*>;
	template<class T> concept impl_PEParserBase = requires(T type) {
		{type.hFile} -> std::convertible_to<HANDLE>;
		{type.dwFileSize} -> std::convertible_to<DWORD>;
		{type.bytes} -> std::convertible_to<DWORD>;
	};
	
	//declarations
	template<typename T = const wchar_t*, class PEParserBaseImpl = PEParser>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl & openFile(T lpFileName, PEParserBaseImpl * pPEParserBaseImpl) noexcept;
	
	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& getFileSize(PEParserBaseImpl* pPEParserBaseImpl) noexcept;
	
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept;
	
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept;
	
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept;
	
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& getSection(PEParserBaseImpl*, const unsigned char*) noexcept;
	
	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_FILE_HEADER FILEHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_OPTIONAL_HEADER OPTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;

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
		IMAGE_FILE_HEADER		FileH;
		IMAGE_OPTIONAL_HEADER	OptH;
	};
	class PEParser : public PEParserBase, public PEHEADER{
	};
	//openFile implementation
	//"thin" wrapper for CreateFile
	template<typename T, class PEParserBaseImpl>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& openFile(T lpFileName , PEParserBaseImpl * pPEParserBaseImpl) noexcept {
		if constexpr (is_char<T>) {
			pPEParserBaseImpl->hFile = CreateFileA(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			pPEParserBaseImpl->hFile = CreateFileW(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			std::wcout << std::endl << lpFileName << std::endl;
		}
		return *pPEParserBaseImpl;
	};
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& getFileSize(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->dwFileSize = GetFileSize(pPEParserBaseImpl->hFile, 0);
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->fileBuffer = new char[pPEParserBaseImpl->dwFileSize];							//could cause some problems (pPEParserBaseImpl->dwFileSize)-1 ?
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		ReadFile(pPEParserBaseImpl->hFile, pPEParserBaseImpl->fileBuffer, pPEParserBaseImpl->dwFileSize, &pPEParserBaseImpl->bytes, 0);
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->pDosH = DOSHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->FileH = FILEHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->OptH = OPTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pSecH = SECHDROFFSET(pPEParserBaseImpl->fileBuffer);
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		if (pPEParserBaseImpl->pDosH->e_magic != IMAGE_DOS_SIGNATURE)	{
			std::cout << "IMAGE_DOS_SIGNATURE not found";
			return *pPEParserBaseImpl;
		}
		if (pPEParserBaseImpl->pNtH->Signature != IMAGE_NT_SIGNATURE)	{
			std::cout << "IMAGE_NT_SIGNATURE not found";
			return *pPEParserBaseImpl;
		}
		std::cout << "all signatures found\n";
		switch (pPEParserBaseImpl->OptH.Magic) {
		case 0x10b:
			std::cout << "PE32 format\n";
			return *pPEParserBaseImpl;
		case 0x20b:
			std::cout << "PE32+ format\n";
			return *pPEParserBaseImpl;
		default:
			std::cout << "invalid format\n";
			return *pPEParserBaseImpl;
		}
		//dont care about Rich Header, its undocumented anyways
		return *pPEParserBaseImpl;
	}

	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& getSection(PEParserBaseImpl* pPEParserBaseImpl, const unsigned char* name) noexcept {
		size_t nameLen = strlen((const char*)name);
		pPEParserBaseImpl->pTextSec = pPEParserBaseImpl->pSecH;
		if (nameLen <= (size_t)IMAGE_SIZEOF_SHORT_NAME) {
			size_t counter = 0;
			unsigned short totalSectionCount = pPEParserBaseImpl->FileH.NumberOfSections;
			while ((memcmp((const char*)pPEParserBaseImpl->pTextSec->Name, (const char*)name, nameLen) != 0) || (counter < totalSectionCount)) {
				std::cout << "SectionNO :" << counter << " out of " << totalSectionCount << "\n" << pPEParserBaseImpl->pTextSec->Name << " is not " << name << "\n";
				pPEParserBaseImpl->pTextSec++;
				counter++;
			};
			if ((pPEParserBaseImpl->FileH.NumberOfSections < counter))
			{
				std::cout << name << " Section found\n" << nameLen << "\n";
				return *pPEParserBaseImpl;
			}
		}
		std::cout << name << " Section not found\n";
		return *pPEParserBaseImpl;
	}

	// I am not sure if that constexpr works like makros
	// here I calculate the offsets off the Headers from the file, 
	/*reinterpret_cast<PIMAGE_DOS_HEADER>(a);   //C3615	The constexpr - Function "PEParserNamespace::DOSHDROFFSET" cannot result in a constant expression..
	constexpr explicitly does not work with reinterpretcast,
	but as far as I know (Newtype)a / Newtype(a) should reduce to reinterpret_cast<PIMAGE_DOS_HEADER>(a)
	*/
	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void* a) noexcept {
		return (PIMAGE_DOS_HEADER)a;
	}
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void* a) noexcept {
		return (PIMAGE_NT_HEADERS) (((LPBYTE)a) + (DOSHDROFFSET(a)->e_lfanew));
	}
	constexpr inline IMAGE_FILE_HEADER FILEHDROFFSET(void* a) noexcept {
		return NTHDROFFSET(a)->FileHeader;
	}
	constexpr inline IMAGE_OPTIONAL_HEADER OPTHDROFFSET(void* a) noexcept {
		return NTHDROFFSET(a)->OptionalHeader;
	}
	/*(PIMAGE_DOS_HEADER)->e_lfanew = last member of DOS Header / beginning of NT Header*/
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void* a) noexcept {
		return (PIMAGE_SECTION_HEADER)((LPVOID)((LPBYTE)a + DOSHDROFFSET(a)->e_lfanew + sizeof(IMAGE_NT_HEADERS)));
	}
}

// P in typename stands for (near) pointer (type*) (near)
// LP stands for far pointer (type*) far