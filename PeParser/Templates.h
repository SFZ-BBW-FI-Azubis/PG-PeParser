#pragma onces
#ifndef PEPARSER_IMPORT_LIBRARY || PEPARSER_IMPORT_C_LIBRARY
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
		returnSignatur;
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
		returnSignatur;
		pPEParserBaseImpl->dwFileSize = ::GetFileSize(pPEParserBaseImpl->hFile, 0);
		pPEParserBaseImpl->failed = (pPEParserBaseImpl->dwFileSize == INVALID_FILE_SIZE);
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	}

	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur;
		pPEParserBaseImpl->fileBuffer = new char[pPEParserBaseImpl->dwFileSize];							//could cause some problems (pPEParserBaseImpl->dwFileSize)-1 ?
		pPEParserBaseImpl->failed = false;
		pPEParserBaseImpl->code.codeUnsignedLong = 0;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur;
		pPEParserBaseImpl->failed =
			!ReadFile(pPEParserBaseImpl->hFile, pPEParserBaseImpl->fileBuffer, pPEParserBaseImpl->dwFileSize, &pPEParserBaseImpl->bytes, 0);
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	}
	//___________________________________________________________________________________________________________________PEHEADER
	template<class PEParserBaseImpl>
		requires impl_PEParserHeader<PEParserBaseImpl>
	inline PEParserBaseImpl& getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur;
		pPEParserBaseImpl->pDosH = DOSHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pNtH = NTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pFileH = FILEHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pOptH = OPTHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pSecH = SECHDROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->pDataDir = DATADIROFFSET(pPEParserBaseImpl->fileBuffer);
		pPEParserBaseImpl->failed = false;
		pPEParserBaseImpl->code.codeUnsignedLong = 0;
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
		requires impl_PEParserHeader<PEParserBaseImpl>
	inline PEParserBaseImpl& checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur;
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

	template<typename T>
		requires (is_Unsigned_Char<T> || is_Const_Unsigned_Char_Ptr<T>)
	inline bool mcompare(T left, T right) noexcept {
		if constexpr (is_Const_Unsigned_Char_Ptr<T>) {
			size_t nLength = strlen((const char*)right);
			return (memcmp((const char*)left, (const char*)right, nLength) == 0);
		} /*constexprs*/else {
			return (left == right);
		}
	}

	template<class PEParserBaseImpl, typename T>
		requires impl_PEParserHeader<PEParserBaseImpl> && 
		(is_Const_Unsigned_Char_Ptr<T> || is_Unsigned_Char<T>)	/*inline is propably not the best option*/
	PEParserBaseImpl& getSection(PEParserBaseImpl* pPEParserBaseImpl, T n) noexcept {
		returnSignatur;
		unsigned short& totalSectionCount = pPEParserBaseImpl->pFileH->NumberOfSections;
		pPEParserBaseImpl->pSecHSingle = nullptr;							//reset secHSingle to nullptr
		Iterable<PIMAGE_SECTION_HEADER> iterate(pPEParserBaseImpl->pSecH, totalSectionCount);
		pPEParserBaseImpl->failed = !iterate([&](PIMAGE_SECTION_HEADER single, auto counter)->bool {
			std::cout << (unsigned int)counter << "	" << single->Name << std::endl;
			if constexpr(is_Const_Unsigned_Char_Ptr<T>)	{
				if (mcompare<T>(single->Name, n)) {
					pPEParserBaseImpl->pSecHSingle = single;
					return true;	//found
				} return false;		//not found
			} else {			
				if (mcompare(counter, n)) {
					pPEParserBaseImpl->pSecHSingle = single;
					return true;	//found
				} return false;		//not found
			}
		});
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
		requires impl_PEParserBase<PEParserBaseImpl>
	PEParserBaseImpl& getDataDirectoryEntry(PEParserBaseImpl* pPEParserBaseImpl, unsigned int index) noexcept {
			returnSignatur;
			pPEParserBaseImpl->pDataDirSingle = nullptr;
			pPEParserBaseImpl->failed = !(index < (IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1));
			if (pPEParserBaseImpl->failed)	{
				return *pPEParserBaseImpl;
			}
			//Array of (below)
			IMAGE_IMPORT_DESCRIPTOR	A;
			//last element zerod out

			//array of IMAGE_BOUND_... with first element being (belos)
			IMAGE_BOUND_IMPORT_DESCRIPTOR a;
			//emidiatly foolowed by NumberOfModuleForwarderRefs * (below)
			IMAGE_BOUND_FORWARDER_REF ab;


			pPEParserBaseImpl->pDataDirSingle = DataDir(pPEParserBaseImpl->pDataDir, index);
		return *pPEParserBaseImpl;
	}
	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		PEParserBaseImpl& getLastError(PEParserBaseImpl* pPEParserBaseImpl) noexcept {
		returnSignatur;
		pPEParserBaseImpl->code.codeUnsignedLong = ::GetLastError();
		return *pPEParserBaseImpl;
	}
}
#endif // !PEParserLibrary