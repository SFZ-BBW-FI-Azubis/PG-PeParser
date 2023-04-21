#pragma once
#include "Preprocessor.h"
#include "DataStructures.h"
#include "Concepts.h"
#include "Templates.h"
#include "Iterable.h"
#include "GetPEB.h"

namespace PEParserNamespace {
	
	class PEParserBase;
	class PEHEADER;
	class PEParser;
	class functionExecutionLog;
	class signatur;

	template <class InIt, class Fn>
	extern inline bool Iterable_for_each(InIt, InIt, Fn) noexcept;

	template<typename T, typename lambda>
	class Iterable;

	template<typename T = const wchar_t*, class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl> && 
		(is_Const_Char_Ptr<T> || is_Const_Wchar_t_Ptr<T>)
		extern inline PEParserBaseImpl& _call openFile (T lpFileName, PEParserBaseImpl* pPEParserBaseImpl) noexcept;

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
	requires impl_PEParserHeader<PEParserBaseImpl>
		inline PEParserBaseImpl& _call getImageHeaders(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserHeader<PEParserBaseImpl>
		inline PEParserBaseImpl& _call checkHeader(PEParserBaseImpl* pPEParserBaseImpl) noexcept;

	template<typename T>
	requires (is_Unsigned_Char<T> || is_Const_Unsigned_Char_Ptr<T>)
		inline bool mcompare(T, T) noexcept;

	template<class PEParserBaseImpl = PEParser, typename T = const unsigned char*>
	requires impl_PEParserHeader<PEParserBaseImpl> && (is_Const_Unsigned_Char_Ptr<T> || is_Unsigned_Char<T>)
		PEParserBaseImpl& _call getSection(PEParserBaseImpl*, T) noexcept;

	template<class PEParserBaseImpl = PEParser>
	requires impl_PEParserBase<PEParserBaseImpl>
		PEParserBaseImpl& _call getDataDirectoryEntry(PEParserBaseImpl*, unsigned int) noexcept;

	template<class PEParserBaseImpl>
	requires impl_PEParserBase<PEParserBaseImpl>
		PEParserBaseImpl& _call getLastError(PEParserBaseImpl*) noexcept;

	constexpr inline PIMAGE_DOS_HEADER DOSHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_NT_HEADERS NTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_FILE_HEADER FILEHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_OPTIONAL_HEADER OPTHDROFFSET(void*) noexcept;
	constexpr inline PIMAGE_SECTION_HEADER SECHDROFFSET(void*) noexcept;
	constexpr inline DWORD SecVSize(void*) noexcept;
}