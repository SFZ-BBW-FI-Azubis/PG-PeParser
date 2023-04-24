#pragma once
#include "Preprocessor.h"
namespace PEParserNamespace {
    PEP_TEMPLATE PEP_LIB_API PEParser& _call openFile/*<const wchar_t*, PEParser>*/ (const wchar_t*, PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call openFile/*<const char*, PEParser>*/(const char*, PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParserBase& _call openFile/*<const wchar_t*, PEParserBase>*/ (const wchar_t*, PEParserBase*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParserBase& _call openFile/*<const char*, PEParserBase>*/(const char*, PEParserBase*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getFileSize(PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call allocMemory(PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call readFile(PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getImageHeaders(PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call checkHeader(PEParser*) noexcept;
    PEP_TEMPLATE PEP_LIB_API bool _call mcompare(unsigned char, unsigned char) noexcept;
    PEP_TEMPLATE PEP_LIB_API bool _call mcompare(const unsigned char*, const  unsigned char*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getSection(PEParser*, unsigned char n) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getSection(PEParser*, const unsigned char*) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getDataDirectoryEntry(PEParser*, unsigned int) noexcept;
    PEP_TEMPLATE PEP_LIB_API PEParser& _call getLastError(PEParser*) noexcept;
}