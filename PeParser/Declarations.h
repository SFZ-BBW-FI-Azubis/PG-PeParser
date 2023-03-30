#pragma once
#include "DataStructures.h"
#include "Concepts.h"
#include "Templates.h"
namespace PEParserNamespace {
	class PEParserBase;
	class PEHEADER;
	class PEParser;
	template<typename T = const wchar_t*, class PEParserBaseImpl = PEParser>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& openFile(T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept;

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

	template<class PEParserBaseImpl, typename T = const unsigned char*>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)
		PEParserBaseImpl& getSection(PEParserBaseImpl*, T) noexcept;

	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_FILE_HEADER FILEHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_OPTIONAL_HEADER OPTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;
	constexpr inline DWORD SecVSize(void*) noexcept;
}