// PeParser.cpp: Definiert den Einstiegspunkt für die Anwendung.
//
#pragma once
#define _call // use standart calling convention, that is __thiscall
#include "Declarations.h"
#include <Windows.h>
/*
template <class InIt, class Fn>
void for_each(InIt _First, InIt _Last, Fn _Func) {
	auto _UFirst = _First;
	auto _ULast = _Last;
	for (; _UFirst <= _ULast; ++_UFirst) {
		_Func(*_UFirst);
	}

	return;
}

template<typename T>
class Iterable {
	typedef void (__cdecl * Callback)(int&);
	T begin;
	T end;
	Callback callback;
public:
	const Iterable(T t, size_t size) noexcept :
		end(&t[size -1]),
		begin(&t[0]) {};
	const Iterable(T t, size_t size, Callback callback) noexcept :
		begin(&t[0]),
		end(&t[size -1]), 
		callback(callback) {};
	const auto operator()(Callback callback) noexcept {
		return for_each(begin, end, callback);
	}
	const auto operator()() noexcept {
		return for_each(begin, end, callback);
	}
};
*/
using namespace std;
int main()	{
	typedef PEParserNamespace::PEParser PEParser;
	PEParser peparser;
	
	int myvector[5] = {0,1,2,3,4};
	PEParserNamespace::Iterable<int*> iterable(myvector, 5);
	iterable([](int *single)->void {
		std::cout << *single << std::endl;
		});
	int myvector2[5] = { 5,6,7,8,9 };
	PEParserNamespace::Iterable<int*> iterable2(myvector2, 5, [](int* single)->void {
		std::cout << *single << std::endl;
		});
	iterable2();	// I called iterable() -> that small mistake cost me a whole day to find :(
	
	char fileNamee[UINT16_MAX] = "C:/NeuerOrdner(2)/depends.exe";
	cout <<
		PEParserNamespace::openFile<const char*>(fileNamee, &peparser).hFile
		<<endl;
	cout <<
		PEParserNamespace::getFileSize<>(&peparser).dwFileSize
		<< endl;
	PEParserNamespace::allocMemory<>(&peparser);
	PEParserNamespace::readFile<>(&peparser);
	PEParserNamespace::getImageHeaders<>(&peparser);
	PEParserNamespace::checkHeader<>(&peparser);
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)".data");
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)"dataas");
	PEParserNamespace::getSection<>(&peparser, (BYTE)4);
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)".text");
	std::cout << PEParserNamespace::SecVSize(peparser.pSecHSingle)<<std::endl;
	//std::cout <<"SecVSize  "<<PEParserNamespace::SecVSize(peparser.pSecH) << std::endl;
	
	wchar_t fileName[UINT16_MAX] = L"C:/NeuerOrdner(2)/depends.exe";
	cout <<
		PEParserNamespace::openFile<const wchar_t*>(fileName, &peparser).hFile
		<<"	"<<peparser.code.codeInt << endl;
	cout <<
		PEParserNamespace::getFileSize<>(&peparser).dwFileSize
		<< "	" << peparser.code.codeInt << endl;
	std::cout << sizeof(IMAGE_SECTION_HEADER) << std::endl;
	std::cout << __FUNCTION__ << "\n" << __FUNCDNAME__ <<"\n";
	return 0;
}
//test test