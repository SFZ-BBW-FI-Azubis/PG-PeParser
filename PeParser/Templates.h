#pragma once
#include "DataStructures.h"
#include "Concepts.h"
#include "Offsets.h"
#include <Windows.h>
#include <iostream>
namespace PEParserNamespace {
	template<typename T, class PEParserBaseImpl>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& openFile(T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept {
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
	//___________________________________________________________________________________________________________________PEHEADER
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		pPEParserBaseImpl->pDosH = DOSHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->FileH = FILEHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->OptH = OPTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pSecH = SECHDROFFSET(pPEParserBaseImpl->fileBuffer);
		for (unsigned long i = 0; i < pPEParserBaseImpl->FileH.NumberOfSections; i++) {

		}
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		if (pPEParserBaseImpl->pDosH->e_magic != IMAGE_DOS_SIGNATURE) {
			std::cout << "IMAGE_DOS_SIGNATURE not found";
			return *pPEParserBaseImpl;
		}
		if (pPEParserBaseImpl->pNtH->Signature != IMAGE_NT_SIGNATURE) {
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
	//___________________________________________________________________________________________________________________PESection
		//this is ugly kind of but its working :)

	template<class PEParserBaseImpl, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_byte<T> || is_uchar<T>)
		inline bool mcompare(PEParserBaseImpl* pPEParserBaseImpl, size_t i, T n) {
		size_t totalSectionCount = pPEParserBaseImpl->FileH.NumberOfSections;
		if constexpr (is_byte<T>) {
			return ((i <= n) && (i <= totalSectionCount));
		}
		return (memcmp((const char*)pPEParserBaseImpl->pTextSec->Name, (const char*)n, strlen((const char*)n)) != 0);
	}

	template<class PEParserBaseImpl, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)	/*inline is propably not the best option*/
		PEParserBaseImpl& getSection(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {
		size_t totalSectionCount = pPEParserBaseImpl->FileH.NumberOfSections;
		for (size_t i = 0; mcompare<PEParserBaseImpl, T>(pPEParserBaseImpl, i, n); i++) {

		}
		size_t nameLen = strlen((const char*)n);
		pPEParserBaseImpl->pTextSec = pPEParserBaseImpl->pSecH;
		if (nameLen <= (size_t)IMAGE_SIZEOF_SHORT_NAME) {
			size_t counter = 0;
			while ((memcmp((const char*)pPEParserBaseImpl->pTextSec->Name, (const char*)n, nameLen) != 0) &&
				(strlen((const char*)pPEParserBaseImpl->pTextSec->Name) == nameLen) &&
				(counter < totalSectionCount)) {
				std::cout << "SectionNO :" << counter << " out of " << totalSectionCount << "\n" << pPEParserBaseImpl->pTextSec->Name << " is not " << n << "\n";
				pPEParserBaseImpl->pTextSec++;
				counter++;
			};
			if ((counter < totalSectionCount) && (strlen((const char*)pPEParserBaseImpl->pTextSec->Name) == nameLen))
			{
				std::cout << n << " Section found\n" << nameLen << "\n";
				return *pPEParserBaseImpl;
			}
		}
		std::cout << n << " Section not found\n";
		return *pPEParserBaseImpl;
	}
}