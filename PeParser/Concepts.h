#pragma once
#include "DataStructures.h"
#include <Windows.h>
#include <concepts>
namespace PEParserNamespace {
	//remove_reference_t<_Dx>
	template <class _Ty>
	struct remove_reference {
		using type = _Ty;
		using thru_ref_type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&> {
		using type = _Ty;
		using thru_ref_type = _Ty&;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&> {
		using type = _Ty;
		using thru_ref_type = _Ty&&;
	};
	template<typename T> concept is_Const_Char_Ptr = std::same_as<T, const char*>;
	template<typename T> concept is_Const_Wchar_t_Ptr = std::same_as<T, const wchar_t*>;
	template<typename T> concept is_Const_Unsigned_Char_Ptr = std::same_as<T, const unsigned char*>;
	template<typename T> concept is_Unsigned_Char = std::same_as<T, unsigned char>;

	template<typename T> concept is_Pointer = std::same_as<typename remove_reference<T>::thru_ref_type, T*>;
	template<typename T> concept is_Right_Value_Reference = std::same_as<typename remove_reference<T>::thru_ref_type, T&>;
	template<typename T> concept is_Left_Value_Reference = std::same_as<typename remove_reference<T>::thru_ref_type, T&&>;
	
	template<class T> concept impl_PEParserHeader = requires(T type) {
		{type.pDosH} -> std::convertible_to<PIMAGE_DOS_HEADER>;
		{type.pNtH} -> std::convertible_to<PIMAGE_NT_HEADERS>;
		{type.pSecH} -> std::convertible_to<PIMAGE_SECTION_HEADER>;
		{type.pSecHSingle} -> std::convertible_to<PIMAGE_SECTION_HEADER>;
		{type.pFileH} -> std::convertible_to<PIMAGE_FILE_HEADER>;
		{type.pOptH} -> std::convertible_to<PIMAGE_OPTIONAL_HEADER>;
	};
	template<class T> concept impl_PEParserBase = requires(T type) {
		{type.hFile} -> std::convertible_to<HANDLE>;
		{type.dwFileSize} -> std::convertible_to<DWORD>;
		{type.bytes} -> std::convertible_to<DWORD>;
		{type.fileBuffer} -> std::convertible_to<void*>;
	};
	template<class T> concept impl_PEParserfunctionExecutionLog = requires(T type) {
		{type.failed} -> std::convertible_to<bool>;
	};
	//#deprecatet
	/*PIMAGE_DOS_HEADER		pDosH;
	PIMAGE_NT_HEADERS		pNtH;
	PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
	PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
	IMAGE_FILE_HEADER		FileH;
	IMAGE_OPTIONAL_HEADER	OptH;*/
/*	template<typename T> concept is_char = std::same_as<T, const char*>;
	template<typename T> concept is_uchar = std::same_as<T, const unsigned char*>;
	template<typename T> concept is_wchar_t = std::same_as<T, const wchar_t*>;
	template<typename T> concept is_byte = std::same_as<T, unsigned char>;*/
}