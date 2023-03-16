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
	PEParserNamespace::PEParser peparser;

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
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)".text");
	PEParserNamespace::getSection<>(&peparser, (const unsigned char*)"dataas");
	
	wchar_t fileName[UINT16_MAX] = L"C:/NeuerOrdner(2)/depends.exe";
	cout <<
		PEParserNamespace::openFile<const wchar_t*>(fileName, &peparser).hFile
		<< endl;
	cout <<
		PEParserNamespace::getFileSize<>(&peparser).dwFileSize
		<< endl;
	return 0;
}
