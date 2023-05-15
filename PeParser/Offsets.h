#pragma once
#include "Preprocessor.h"
#include "DataStructures.h"

#ifdef __cplusplus
namespace PEParserNamespace {
#endif // __cplusplus
	PEP_CONSTEXPR PIMAGE_DOS_HEADER DOSHDROFFSET(void* a) noexcept {
		return (PIMAGE_DOS_HEADER)a;
	}
	PEP_CONSTEXPR PIMAGE_NT_HEADERS NTHDROFFSET(void* a) noexcept {
		return (PIMAGE_NT_HEADERS)(((LPBYTE)a) + (DOSHDROFFSET(a)->e_lfanew));
	}
	PEP_CONSTEXPR PIMAGE_FILE_HEADER FILEHDROFFSET(void* a) noexcept {
		return &NTHDROFFSET(a)->FileHeader;
	}
	PEP_CONSTEXPR PIMAGE_OPTIONAL_HEADER OPTHDROFFSET(void* a) noexcept {
		return &NTHDROFFSET(a)->OptionalHeader;
	}
	PEP_CONSTEXPR PIMAGE_DATA_DIRECTORY DATADIROFFSET(void* a) noexcept {
		return OPTHDROFFSET(a)->DataDirectory;
	}
	/*(PIMAGE_DOS_HEADER)->e_lfanew = last member of DOS Header / beginning of NT Header*/
	PEP_CONSTEXPR PIMAGE_SECTION_HEADER SECHDROFFSET(void* a) noexcept {
		return (PIMAGE_SECTION_HEADER)((LPVOID)((LPBYTE)a + DOSHDROFFSET(a)->e_lfanew + sizeof(IMAGE_NT_HEADERS)));
	}
	//just some Helper Functions
	PEP_CONSTEXPR DWORD SecVSize(PIMAGE_SECTION_HEADER a) noexcept {
		return a->Misc.VirtualSize;
	}
	PEP_CONSTEXPR DWORD SecRawSize(PIMAGE_SECTION_HEADER a) noexcept {
		return a->SizeOfRawData;
	}
	PEP_CONSTEXPR DWORD NumberOfRvaAndSizes(PIMAGE_OPTIONAL_HEADER a) noexcept {
		return a->NumberOfRvaAndSizes;
	}
	PEP_CONSTEXPR PIMAGE_DATA_DIRECTORY DataDir(PIMAGE_DATA_DIRECTORY dataDirArray, unsigned int dataDir) noexcept {
		return &dataDirArray[dataDir];
	}
	PEP_CONSTEXPR void setErrorCode(void* a) noexcept {

	}
#ifdef __cplusplus
	template<class Base, class Derived>
	constexpr Base* Offset(Derived& derived, int offset) noexcept {
		return (Base*)(void*)((unsigned char*)derived + offset);
	}
}
#endif
// I am not sure if that constexpr works like makros
// here I calculate the offsets off the Headers from the file, 
/*reinterpret_cast<PIMAGE_DOS_HEADER>(a);   //C3615	The constexpr - Function "PEParserNamespace::DOSHDROFFSET" cannot result in a constant expression..
constexpr explicitly does not work with reinterpretcast,
but as far as I know (Newtype)a / Newtype(a) should reduce to reinterpret_cast<PIMAGE_DOS_HEADER>(a)
*/