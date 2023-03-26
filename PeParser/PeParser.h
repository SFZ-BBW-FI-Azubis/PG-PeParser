// PeParser.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.
#pragma once
#include "DataStructures.h"
#include "Concepts.h"
#include "Templates.h"
#include <iostream>
#include <Windows.h>
#include <vector>
namespace PEParserNamespace {
	//declarations
	
	
	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_FILE_HEADER FILEHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_OPTIONAL_HEADER OPTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;
	constexpr inline DWORD SecVSize(void*) noexcept;




	//openFile implementation
	//"thin" wrapper
//___________________________________________________________________________________________________________________PEParserBase


}

// P in typename stands for (near) pointer (type*) (near)
// LP stands for far pointer (type*) far