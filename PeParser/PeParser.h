// PeParser.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <iostream>
#include <Windows.h>
namespace PEParserNamespace {
	//concepts
	template<typename T> concept is_char = std::same_as<T, const char*>;
	template<typename T> concept is_wchar_t = std::same_as<T, const wchar_t*>;
	template<class T> concept impl_PEParserBase = requires(T type) {
		{type.hFile};
	};
	template<typename T> concept has_this = requires(T type) {
		true;
	};
	//openFile declaration
	template<typename T = const wchar_t*, class PEParserBaseImpl = PEParser>
		requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl & openFile(T lpFileName, PEParserBaseImpl * pPEParserBaseImpl) noexcept;

	class PEParserBase {
	public:
		HANDLE hFile;
		DWORD dwFileSize;
	};
	//friends/hosts methods
	class PEParser : public PEParserBase{
	public:
		PEParser(const wchar_t* lpFileName) {
			openFile<const wchar_t*, PEParser>(lpFileName, this);
		}
		PEParser() {
		};
		template<typename T, class PEParserBaseImpl>
		friend inline PEParser& openFile<T, PEParserBaseImpl>(T, PEParserBaseImpl*) noexcept;
	};
	//openFile implementation
	//"thin" wrapper for CreateFile
	template<typename T, class PEParserBaseImpl>
	requires (is_char<T> || is_wchar_t<T>) && impl_PEParserBase<PEParserBaseImpl>
	inline PEParserBaseImpl& openFile(T lpFileName , PEParserBaseImpl * pPEParserBaseImpl) noexcept {
		if constexpr (is_char<T>) {
			pPEParserBaseImpl->hFile = CreateFileA(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else {
			pPEParserBaseImpl->hFile = CreateFileW(lpFileName, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			std::wcout << std::endl << lpFileName << std::endl;
		}
		return *pPEParserBaseImpl;
	};
	void test() {
		PEParser pepeDeFrog;
		
	};
}