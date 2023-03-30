#pragma once
#include "DataStructures.h"
#include <Windows.h>
#include <concepts>
namespace PEParserNamespace {
	template<typename T> concept is_char = std::same_as<T, const char*>;
	template<typename T> concept is_uchar = std::same_as<T, const unsigned char*>;
	template<typename T> concept is_wchar_t = std::same_as<T, const wchar_t*>;
	template<typename T> concept is_byte = std::same_as<T, unsigned char>;
	template<class T> concept impl_PEParserBase = requires(T type) {
		{type.hFile} -> std::convertible_to<HANDLE>;
		{type.dwFileSize} -> std::convertible_to<DWORD>;
		{type.bytes} -> std::convertible_to<DWORD>;
	};
	
}