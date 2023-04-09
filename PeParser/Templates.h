#pragma once
#include "DataStructures.h"
#include "Concepts.h"
#include "Offsets.h"
#include <Windows.h>
#include <iostream>
namespace PEParserNamespace {
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& init(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		*(pPEParserBaseImpl->code) = new char[8];		// = (64 bit) meight cause alignment problems
	};
	template<typename T, class PEParserBaseImpl>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& openFile(T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept {
#pragma comment(linker, "/EXPORT:" __FUNCTION__"5" "=" __FUNCDNAME__  )
		std::cout << __FUNCTION__ << "\n"<<__func__ << "\n" << __FUNCDNAME__ << "\n";
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
		if (pPEParserBaseImpl->hFile == INVALID_HANDLE_VALUE)	{
			pPEParserBaseImpl->failed = true;
			pPEParserBaseImpl->code.codeVoidptr = INVALID_HANDLE_VALUE;
			return *pPEParserBaseImpl;
		}
		pPEParserBaseImpl->failed = false;
		return *pPEParserBaseImpl;
	};
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& getFileSize(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->dwFileSize = GetFileSize(pPEParserBaseImpl->hFile, 0);
		if (pPEParserBaseImpl->dwFileSize == INVALID_FILE_SIZE) {
			std::cout << "INVALID_FILE_SIZE\n";
			pPEParserBaseImpl->failed = true;
			pPEParserBaseImpl->code.codeUlong = INVALID_FILE_SIZE;					//I hate that one. HEADACKE :( I could try some nasty typepunning tricks, but thats far from Elegant, and could cause sneaky Bugs (for ea. Unaligned Memory)
			return *pPEParserBaseImpl;
		}
		pPEParserBaseImpl->failed = false;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->fileBuffer = new char[pPEParserBaseImpl->dwFileSize];							//could cause some problems (pPEParserBaseImpl->dwFileSize)-1 ?
		pPEParserBaseImpl->failed = false;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		bool succes = ReadFile(pPEParserBaseImpl->hFile, pPEParserBaseImpl->fileBuffer, pPEParserBaseImpl->dwFileSize, &pPEParserBaseImpl->bytes, 0);
		pPEParserBaseImpl->failed = succes;
		return *pPEParserBaseImpl;
	}
	//___________________________________________________________________________________________________________________PEHEADER
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->pDosH = DOSHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->FileH = FILEHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->OptH = OPTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pSecH = SECHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->failed = false;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		if (pPEParserBaseImpl->pDosH->e_magic != IMAGE_DOS_SIGNATURE) {
			pPEParserBaseImpl->code.codeInt = IMAGE_DOS_SIGNATURE;
			pPEParserBaseImpl->failed = true;
			std::cout << "IMAGE_DOS_SIGNATURE not found";
			return *pPEParserBaseImpl;
		}
		if (pPEParserBaseImpl->pNtH->Signature != IMAGE_NT_SIGNATURE) {
			pPEParserBaseImpl->code.codeInt = IMAGE_NT_SIGNATURE;
			pPEParserBaseImpl->failed = true;
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
		case 0x107:
			std::cout << "ROM format\n";
			return *pPEParserBaseImpl;
		default:
			std::cout << "invalid format\n";
			pPEParserBaseImpl->failed = true;
			return *pPEParserBaseImpl;
		}
		//dont care about Rich Header, its undocumented anyways
		return *pPEParserBaseImpl;
	}
	//___________________________________________________________________________________________________________________PESection
		//this is ugly kind of but its working :)

	template<class PEParserBaseImpl, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_byte<T> || is_uchar<T>)
		inline bool mcompare(PEParserBaseImpl* pPEParserBaseImpl, size_t i, T n) noexcept {
		size_t totalSectionCount = pPEParserBaseImpl->FileH.NumberOfSections;
		if (i >= totalSectionCount)	{
			pPEParserBaseImpl->pSecHSingle--;
			return false;
		}
		if constexpr (is_byte<T>) {
			return (i < n);
		} else	{
			size_t nLength = strlen((const char*)n);
			constexpr size_t nMaxLength = (size_t)IMAGE_SIZEOF_SHORT_NAME;
			return (nLength <= nMaxLength)&&(memcmp((const char*)pPEParserBaseImpl->pSecHSingle->Name, (const char*)n, nLength) != 0);
		}
	}

	template<class PEParserBaseImpl, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)	/*inline is propably not the best option*/
		PEParserBaseImpl& getSection(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {
		unsigned short& totalSectionCount = pPEParserBaseImpl->FileH.NumberOfSections;
		pPEParserBaseImpl->pSecHSingle = pPEParserBaseImpl->pSecH;							//reset secHSingle to firstSecH
		size_t i;
		for (i = 0; mcompare<PEParserBaseImpl, T>(pPEParserBaseImpl, i, n); i++) {
			pPEParserBaseImpl->pSecHSingle++;
		}
		if (i == pPEParserBaseImpl->FileH.NumberOfSections)	{
			std::cout << n <<"	not found" << std::endl;
			return *pPEParserBaseImpl;
		}
		std::cout << pPEParserBaseImpl->pSecHSingle->Name << "	found"<< std::endl;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)
		PEParserBaseImpl& getDataDirectoryEntry(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {

		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		PEParserBaseImpl& getLastError(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->code = ::GetLastError();
		return *pPEParserBaseImpl;
	}
}