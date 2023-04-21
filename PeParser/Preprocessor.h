#pragma once

#ifdef PEPARSER_IMPORT_LIBRARY
	#define PEP_LIB_API __declspec(dllimport)
	#define _call _cdecl
#endif
#ifdef PEPARSER_EXPORT_LIBRARY
	#define PEP_LIB_API __declspec(dllexport)
	#define _call _cdecl
#endif
#if !defined(PEPARSER_IMPORT_LIBRARY) && !defined(PEPARSER_EXPORT_LIBRARY)
//	#define PEP_LIB_API		// when someone forgets to define PEPARSER_..._LIBRARY there will be syntax errors
	#define _call
#endif

#ifdef PEParserReturnSignatur
	#define returnSignatur											\
		pPEParserBaseImpl->Signatur = __FUNCDNAME__;				\
		pPEParserBaseImpl->sizeOfSignatur = sizeof(__FUNCDNAME__);	\
		pPEParserBaseImpl->UnmangledSig = __func__;					\
		pPEParserBaseImpl->sizeOfUnmangledSig = sizeof(__func__);	\
		return *pPEParserBaseImpl
	#define disable return{}
	#define CONSTEXPR constexpr
#else
	#define returnSignatur
	#define disable
	#define CONSTEXPR
#endif // PEParserReturnSignatur