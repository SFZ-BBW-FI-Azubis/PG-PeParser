#pragma once
#include "DataStructures.h"
#include "Concepts.h"
#include "Templates.h"
#ifndef _call
	#define _call _cdecl
#endif // !_call

namespace PEParserNamespace {
	class PEParserBase;
	class PEHEADER;
	class PEParser;
	class functionExecutionLog;
	template<typename T = const wchar_t*, class PEParserBaseImpl = PEParser>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call openFile (T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call getFileSize(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call allocMemory(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call readFile(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		inline PEParserBaseImpl& _call checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser, typename T>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_byte<T> || is_uchar<T>)
		inline bool mcompare(PEParserBaseImpl*, size_t, T) noexcept;

	template<class PEParserBaseImpl = PEParser, typename T = const unsigned char*>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)
		PEParserBaseImpl& _call getSection(PEParserBaseImpl*, T) noexcept;

	template<class PEParserBaseImpl = PEParser, typename T = const unsigned char*>
	requires impl_PEParserBase<PEParserBaseImpl> && (is_uchar<T> || is_byte<T>)
		PEParserBaseImpl& _call getDataDirectoryEntry(PEParserBaseImpl*, T) noexcept;

	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_FILE_HEADER FILEHDROFFSET(void*) noexcept;
	constexpr inline IMAGE_OPTIONAL_HEADER OPTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;
	constexpr inline DWORD SecVSize(void*) noexcept;
}