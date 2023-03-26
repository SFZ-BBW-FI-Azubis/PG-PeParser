#pragma once
#include "DataStructures.h"
namespace PEParserNamespace {
	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void* a) noexcept {
		return (PIMAGE_DOS_HEADER)a;
	}
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void* a) noexcept {
		return (PIMAGE_NT_HEADERS)(((LPBYTE)a) + (DOSHDROFFSET(a)->e_lfanew));
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
	constexpr inline DWORD SecVSize(void* a) noexcept {
		return PIMAGE_SECTION_HEADER(a)->Misc.VirtualSize;
	}
}
// I am not sure if that constexpr works like makros
// here I calculate the offsets off the Headers from the file, 
/*reinterpret_cast<PIMAGE_DOS_HEADER>(a);   //C3615	The constexpr - Function "PEParserNamespace::DOSHDROFFSET" cannot result in a constant expression..
constexpr explicitly does not work with reinterpretcast,
but as far as I know (Newtype)a / Newtype(a) should reduce to reinterpret_cast<PIMAGE_DOS_HEADER>(a)
*/