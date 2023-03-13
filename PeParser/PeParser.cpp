// PeParser.cpp: Definiert den Einstiegspunkt für die Anwendung.
//
#pragma once
#include "PeParser.h"
#include <Windows.h>
#include <type_traits>
#include <concepts>
#include "PeParser.h"
using namespace std;
int main()
{
	wchar_t fileName[UINT16_MAX] = L"C:/NeuerOrdner(2)/depends.exe";
	PEParserNamespace::PEParser peparser(fileName);
	std::cout<< peparser.hFile<<"\n";
	/*char fileNamee[UINT16_MAX] = "C:/NeuerOrdner(2)/depends.exe";
	cout <<
		PEParserNamespace::openFile<const char*>(fileNamee, &peparser).hFile
		<<endl;
	
	wchar_t fileName[UINT16_MAX] = L"C:/NeuerOrdner(2)/depends.exe";
	cout <<
		PEParserNamespace::openFile<const wchar_t*>(fileName, &peparser).hFile
		<< endl;
	*/
	return 0;
}
