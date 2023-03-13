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
	inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;
	inline PIMAGE_SECTION_HEADER NTHDROFFSET(void*, LONG*) noexcept;

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
		pPEParserBaseImpl->pDosH = (PIMAGE_DOS_HEADER)pPEParserBaseImpl->fileBuffer;
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer, pPEParserBaseImpl->pDosH->e_lfanew)/*(PIMAGE_NT_HEADERS)(pPEParserBaseImpl->fileBuffer + (pPEParserBaseImpl->pDosH->e_lfanew))*/;
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
		std::cout << "all signatures found";
		return *pPEParserBaseImpl;
	}
	inline PIMAGE_SECTION_HEADER SECHDROFFSET(void* a) noexcept {
		return (PIMAGE_SECTION_HEADER)((LPVOID)((LPBYTE)a + ((PIMAGE_DOS_HEADER)a)->e_lfanew + sizeof(IMAGE_NT_HEADERS)));
	}
	inline PIMAGE_SECTION_HEADER NTHDROFFSET(void* a, long& e_lfanew) noexcept {
		return (PIMAGE_NT_HEADERS)(a + e_lfanew);
	}
}