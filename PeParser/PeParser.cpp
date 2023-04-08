// PeParser.cpp: Definiert den Einstiegspunkt für die Anwendung.
//
#pragma once
#define _call // use standart calling convention 
#include "Declarations.h"
#include <Windows.h>
using namespace std;
int main()
{
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