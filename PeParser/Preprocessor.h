#pragma once
/*
* build cooler Preprocessor tricks
*/
#ifdef PEPARSER_IMPORT_LIBRARY
	#define PEP_LIB_API __declspec(dllimport)
	#define _call _cdecl
	#define PEP_TEMPLATE
#endif
#ifdef PEPARSER_EXPORT_LIBRARY
	#define PEP_LIB_API __declspec(dllexport)
	#define _call _cdecl
	#define PEP_TEMPLATE template
#endif
#if !defined(PEPARSER_IMPORT_LIBRARY) && \
	!defined(PEPARSER_EXPORT_LIBRARY) && \
	!defined(PEPARSER_IMPORT_C_LIBRARY)
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
#define PEParser_OFFSET alignas(void*) /*volatile*/		// first element in class gets marked with this
												// assuming that class member(visible) get layd out in declaration order
												// when first member marked with this, member interpreted as offset from base of derived class to real, or adress to real  class
												// following members are ignored
#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER()()
#define EXPAND(...) __VA_ARGS__