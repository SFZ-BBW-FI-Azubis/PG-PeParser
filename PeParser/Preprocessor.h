
#pragma once
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
#ifndef EXPORT
	#define EXPORT
#endif // !API
#ifndef _call
	#define _call
#endif // !_call