#pragma once
#include "Preprocessor.h"
#include "DataStructures.h"
#include "Concepts.h"
#include "Offsets.h"
#include "Iterable.h"
#include <Windows.h>
#include <iostream>
namespace PEParserNamespace {
	template<typename T, class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl> && 
		(is_Const_Char_Ptr<T> || is_Const_Wchar_t_Ptr<T>)
	inline PEParserBaseImpl& openFile(T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		if constexpr (is_Const_Char_Ptr<T>) {
			pPEParserBaseImpl->hFile = ::CreateFileA(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			pPEParserBaseImpl->hFile = ::CreateFileW(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
		}
		pPEParserBaseImpl->failed = (pPEParserBaseImpl->hFile == INVALID_HANDLE_VALUE);
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	};
	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& getFileSize(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		pPEParserBaseImpl->dwFileSize = ::GetFileSize(pPEParserBaseImpl->hFile, 0);
		pPEParserBaseImpl->failed = (pPEParserBaseImpl->dwFileSize == INVALID_FILE_SIZE);
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	}

	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		pPEParserBaseImpl->fileBuffer = new char[pPEParserBaseImpl->dwFileSize];							//could cause some problems (pPEParserBaseImpl->dwFileSize)-1 ?
		pPEParserBaseImpl->failed = false;
		pPEParserBaseImpl->code.codeUnsignedLong = 0;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		pPEParserBaseImpl->failed =
			!ReadFile(pPEParserBaseImpl->hFile, pPEParserBaseImpl->fileBuffer, pPEParserBaseImpl->dwFileSize, &pPEParserBaseImpl->bytes, 0);
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	}
	//___________________________________________________________________________________________________________________PEHEADER
	template<class PEParserBaseImpl>
		requires impl_PEParserHeader<PEParserBaseImpl>
	inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		pPEParserBaseImpl->pDosH = DOSHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pFileH = FILEHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pOptH = OPTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pSecH = SECHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->failed = false;
		pPEParserBaseImpl->code.codeUnsignedLong = 0;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
		requires impl_PEParserHeader<PEParserBaseImpl>
	inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
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
		pPEParserBaseImpl->failed = false;
		pPEParserBaseImpl->code.codeInt = 0;
		return *pPEParserBaseImpl;
	}

	template<class PEParserBaseImpl, typename T>
		requires impl_PEParserHeader<PEParserBaseImpl> && 
		(is_Unsigned_Char<T> || is_Const_Unsigned_Char_Ptr<T>)
	inline bool mcompare(PEParserBaseImpl* pPEParserBaseImpl, size_t i, T n) noexcept {
		disable
		size_t totalSectionCount = pPEParserBaseImpl->pFileH->NumberOfSections;
		if (i >= totalSectionCount)	{
			pPEParserBaseImpl->pSecHSingle--;
			return false;
		}
		if constexpr (is_Unsigned_Char<T>) {
			return (i < n);
		} /*constexprs*/else {
			size_t nLength = strlen((const char*)n);
			constexpr size_t nMaxLength = (size_t)IMAGE_SIZEOF_SHORT_NAME;
			return (nLength <= nMaxLength)&&(memcmp((const char*)pPEParserBaseImpl->pSecHSingle->Name, (const char*)n, nLength) != 0);
		}
	}

	template<class PEParserBaseImpl, typename T>
		requires impl_PEParserHeader<PEParserBaseImpl> && 
		(is_Const_Unsigned_Char_Ptr<T> || is_Unsigned_Char<T>)	/*inline is propably not the best option*/
	PEParserBaseImpl& getSection(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {
		returnSignatur
		unsigned short& totalSectionCount = pPEParserBaseImpl->pFileH->NumberOfSections;
		pPEParserBaseImpl->pSecHSingle = pPEParserBaseImpl->pSecH;							//reset secHSingle to firstSecH
		size_t i;
		int arrayy[5] = {1,2,3,4,5};
		Iterable iterate(&pPEParserBaseImpl->pSecH, totalSectionCount);
		iterate([](auto){});
		for (i = 0; mcompare<PEParserBaseImpl, T>(pPEParserBaseImpl, i, n); i++) {
			pPEParserBaseImpl->pSecHSingle++;
		}
		if (i == pPEParserBaseImpl->pFileH->NumberOfSections)	{
			std::cout << n <<"	not found" << std::endl;
			return *pPEParserBaseImpl;
		}
		std::cout << pPEParserBaseImpl->pSecHSingle->Name << "	found"<< std::endl;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl, typename T>
		requires impl_PEParserBase<PEParserBaseImpl> && 
		(is_Unsigned_Char<T> || is_Unsigned_Char<T>)
	PEParserBaseImpl& getDataDirectoryEntry(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {
		returnSignatur
			for (size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)	{
				
			}
		/*each Datadirectory is 8 bytes long sizeof(_IMAGE_DATA_DIRECTORY) -> 8 byte
		* there are always 16 Directory entries (#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16)
		* but there are not always 16 Directorys, there can be lesss
		* check pPEParserBaseImpl->OptH.NumberOfRvaAndSizes
		* 
		* The Field, the RVA is pointing in each Data directory can be a Table or String
		*/
		//	IMAGE_EXPORT_DIRECTORY
		//	IMAGE_DIRECTORY_ENTRY_EXPORT
		//IMAGE_OPTIONAL_HEADER.DataDirectory
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		PEParserBaseImpl& getLastError(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur
		pPEParserBaseImpl->code = ::GetLastError();
		return *pPEParserBaseImpl;
	}
}