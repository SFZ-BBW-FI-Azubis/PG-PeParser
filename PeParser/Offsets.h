#pragma once
#include "Preprocessor.h"
#include "DataStructures.h"
namespace PEParserNamespace {
	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void* a) noexcept {
		return (PIMAGE_DOS_HEADER)a;
	}
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void* a) noexcept {
		return (PIMAGE_NT_HEADERS)(((LPBYTE)a) + (DOSHDROFFSET(a)->e_lfanew));
	}
	constexpr inline PIMAGE_FILE_HEADER FILEHDROFFSET(void* a) noexcept {
		return &NTHDROFFSET(a)->FileHeader;
	}
	constexpr inline PIMAGE_OPTIONAL_HEADER OPTHDROFFSET(void* a) noexcept {
		return &NTHDROFFSET(a)->OptionalHeader;
	}
	constexpr inline PIMAGE_DATA_DIRECTORY DATADIROFFSET(void* a) noexcept {
		return OPTHDROFFSET(a)->DataDirectory;
	}
	/*(PIMAGE_DOS_HEADER)->e_lfanew = last member of DOS Header / beginning of NT Header*/
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void* a) noexcept {
		return (PIMAGE_SECTION_HEADER)((LPVOID)((LPBYTE)a + DOSHDROFFSET(a)->e_lfanew + sizeof(IMAGE_NT_HEADERS)));
	}
	//just some Helper Functions
	constexpr inline DWORD SecVSize(PIMAGE_SECTION_HEADER a) noexcept {
		return a->Misc.VirtualSize;
	}
	constexpr inline DWORD SecRawSize(PIMAGE_SECTION_HEADER a) noexcept {
		return a->SizeOfRawData;
	}
	constexpr inline DWORD NumberOfRvaAndSizes(PIMAGE_OPTIONAL_HEADER a) noexcept {
		return a->NumberOfRvaAndSizes;
	}
	constexpr inline void setErrorCode(void* a) noexcept {

	}
}
// I am not sure if that constexpr works like makros
// here I calculate the offsets off the Headers from the file, 
/*reinterpret_cast<PIMAGE_DOS_HEADER>(a);   //C3615	The constexpr - Function "PEParserNamespace::DOSHDROFFSET" cannot result in a constant expression..
constexpr explicitly does not work with reinterpretcast,
but as far as I know (Newtype)a / Newtype(a) should reduce to reinterpret_cast<PIMAGE_DOS_HEADER>(a)
*/