#pragma once
#include <winternl.h>
#include <Windows.h>
namespace PEParserNamespace {
	typedef _PEB* (_cdecl* RtlGetCurrentPeb)();
	inline PEB* NtCurrentPeb() {
#if defined(_M_X64) || defined(_M_AMD64 ) || defined(_AMD64_ )
		return (PEB*)(__readgsqword(0x60));
#elif defined(_M_IX86)
		return (PEB*)(__readfsdword(0x30));
#elif defined(_M_ARM)
		return *(PEB**)(_MoveFromCoprocessor(15, 0, 13, 0, 2) + 0x30);
#elif defined(_M_ARM64)
		return *(PEB**)(__getReg(18) + 0x60); // TEB in x18
#elif defined(_M_IA64)
		return *(PEB**)((size_t)_rdteb() + 0x60); // TEB in r13
#elif defined(_M_ALPHA)
		return *(PEB**)((size_t)_rdteb() + 0x30); // TEB pointer returned from callpal 0xAB
#elif defined(_M_MIPS)
		return *(PEB**)((*(size_t*)(0x7ffff030)) + 0x30); // TEB pointer located at 0x7ffff000 (PCR in user-mode) + 0x30
#elif defined(_M_PPC)
		// winnt.h of the period uses __builtin_get_gpr13() or __gregister_get(13) depending on _MSC_VER
		return *(PEB**)(__gregister_get(13) + 0x30); // TEB in r13
#else
#error "This architecture is currently unsupported"
#endif
	}
	//__readgsqword == x64
	//__readfsdword == x86
	HINSTANCE PEParserLoadNTDLL() {
		return LoadLibrary("NTDLL.dll");
	}
	constexpr _PEB* RTL_GET_CURRENT_PEB() {
		return RtlGetCurrentPeb(GetProcAddress(LoadLibrary("NTDLL.dll"), "RtlGetCurrentPeb"))();
	}
	//_TEB;
	_PEB* peb = RTL_GET_CURRENT_PEB();
	_PEB* peb2 = NtCurrentPeb();
}
//FIELD_OFFSET()
//_TEB;
//NtCurrentTeb;
//PEParserNtCurrentTeb();