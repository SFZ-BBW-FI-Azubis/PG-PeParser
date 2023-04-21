#pragma once
#include "Declarations.h"
#include <Windows.h>
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
	PEParserNamespace::getDataDirectoryEntry<>(&peparser, IMAGE_DIRECTORY_ENTRY_EXPORT);
	std::cout << std::endl;
	if (peparser.failed) {
		std::cout << "not found\n";
	}
	PEParserNamespace::getDataDirectoryEntry<>(&peparser, IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR);
	std::cout << std::endl;
	if (peparser.failed)	{
		std::cout << "not found\n";
	}
	HINSTANCE NTDLL;
	NTDLL = PEParserNamespace::PEParserLoadNTDLL();
	std::cout << NTDLL<<"\n";
	PEParserNamespace::peb;
	PEParserNamespace::peb2;
	std::wcout << PEParserNamespace::peb->ProcessParameters->ImagePathName.Buffer << "\n";
	std::wcout << PEParserNamespace::peb2->ProcessParameters->ImagePathName.Buffer << "\n";
	//std::cout <<"SecVSize  "<<PEParserNamespace::SecVSize(peparser.pSecH) << std::endl;
	return 0;
}
//test test