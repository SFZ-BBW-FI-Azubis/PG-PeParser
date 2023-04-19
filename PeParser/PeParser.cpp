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
	std::cout << std::endl;
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)"dataas");
	std::cout << std::endl;
	if (peparser.failed) {
		std::cout << "not found\n";
	}
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)".text");
	std::cout << std::endl;
	PEParserNamespace::getSection<>(&peparser, (BYTE)0);
	std::cout << std::endl;
	PEParserNamespace::getDataDirectoryEntry<>(&peparser, (BYTE)15);
	std::cout << std::endl;
	if (peparser.failed)	{
		std::cout << "not found\n";
	}
	//std::cout <<"SecVSize  "<<PEParserNamespace::SecVSize(peparser.pSecH) << std::endl;
	return 0;
}
//test test