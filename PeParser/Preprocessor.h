#pragma once
/*#define returnSignatur	\
		pPEParserBaseImpl->Signatur = __FUNCDNAME__;	\
		pPEParserBaseImpl->UnmangledSig = __func__;		\
		return *pPEParserBaseImpl;
#define disable return{};*/
#ifndef returnSignatur
	#define returnSignatur
#endif // !returnSignatur
#ifndef disable
	#define disable
#endif // !disables
#ifndef EXPORT
	#define EXPORT
#endif // !API
#ifndef _call
	#define _call
#endif // !_call