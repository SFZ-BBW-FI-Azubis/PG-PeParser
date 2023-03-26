#ifndef Includes
	#define Includes
	#include "Concepts.h"
	#include "DataStructures.h"
	#include "Templates.h"
	#include <Windows.h>
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

template<class PEParserBaseImpl>
requires impl_PEParserBase<PEParserBaseImpl>
PEParserBaseImpl& getSection(PEParserBaseImpl*, const unsigned char*) noexcept;
#endif	//Includes

#ifdef Concepts
	#include "DataStructures.h"
	#include "Templates.h"
	#include <Windows.h>
#endif // Concepts
#ifdef Templates
	#include "Concepts.h"
	#include "DataStructures.h"
	#include <Windows.h>
#endif // Templates
#ifdef DataStructures
	#include "Concepts.h"
	#include "Templates.h"
	#include <Windows.h>
#endif // DataStructures
