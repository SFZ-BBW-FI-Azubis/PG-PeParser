#pragma once
#ifdef PEParserLibrary
	#define EXPORT __declspec(dllexport)
	#define _call _cdecl
#else
	#define EXPORT
	#define _call
#endif // PEParserLibrary

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