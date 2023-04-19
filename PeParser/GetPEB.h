#pragma once
#include <winternl.h>
#include <Windows.h>
namespace PEParserNamespace {
	typedef _PEB* (_cdecl* RtlGetCurrentPeb)();
	_TEB* PEParserNtCurrentTeb() {
		return (struct _TEB*)__readgsqword(FIELD_OFFSET(NT_TIB, Self));
	}
	HINSTANCE PEParserLoadNTDLL() {
		return LoadLibrary("NTDLL.dll");
	}
	_PEB* peb = RtlGetCurrentPeb(GetProcAddress(PEParserLoadNTDLL(), "RtlGetCurrentPeb"))();
}
//FIELD_OFFSET()
//_TEB;
//NtCurrentTeb;
//PEParserNtCurrentTeb();