#pragma once
#include "Preprocessor.h"
#include <Windows.h>
#include <concepts>
#include <type_traits>
//#include "PEParser.h"
//I think I will have to implement getter and setter either
//as methods in classes/structs (make everything privat and the compiler tells where to replace with new getter / setter)
//or as macros in präprocessor.h
namespace PEParserNamespace {
	typedef class functionExecutionLog {
		alignas(void*) bool failed;
		union alignas(void*) {
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
	public:
		//member variable either stores Data or points to Data
		//alignment???
		//do all by copy
		void setFailed(bool failed) {
			failed = failed;
		}
		void setCode(void* code) {
			code = { code };
		}
		bool getFailed() {
			return failed;
		}
		void* getCode() {
			return code.codeVoidptr;
		}
		//and now all by pointer/ref
		void setFailed(bool *failed) {
			void*(failed) = failed;		//now functionExecutionLog::failed contains Address of/ points to argument (passed by pointer/ref)
		}
		void setCode(void* code) {
			void*(code) = code;			//--'--
		}
		bool getFailed() {
			return failed;
		}
		void* getCode() {
			return code.codeVoidptr;
		}
	} PEParserfunctionExecutionLog;
	typedef struct signatur {
		const char* Signatur;
		const char* UnmangledSig;
	} PEParsersignatur;

	struct PEParserBase :
		virtual public functionExecutionLog,
		virtual public signatur 
	{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD bytes;
		void* fileBuffer;
	};
	typedef struct PEHEADER : 
		virtual public functionExecutionLog,
		virtual public signatur	
	{
		PIMAGE_DOS_HEADER		pDosH;
		PIMAGE_NT_HEADERS		pNtH;
		PIMAGE_SECTION_HEADER	pSecH;					//points to the first SecH
		PIMAGE_SECTION_HEADER	pSecHSingle;			//points to a selected SecH
		PIMAGE_FILE_HEADER		pFileH;
		PIMAGE_OPTIONAL_HEADER	pOptH;
		PIMAGE_DATA_DIRECTORY	pDataDir;
		PIMAGE_DATA_DIRECTORY	pDataDirSingle;
	} PEParserHeader;
	struct PEParser : 
		public PEParserBase, 
		public PEParserHeader
	{

	};
	template<typename Type>	//Type meight be for e.a. PEParserHeader
	auto ClassConverter(Type type) noexcept {
		if constexpr (std::is_base_of_v<functionExecutionLog, Type> /*not right!!!*/) {
			functionExecutionLog* fx;
			void* fxVBPTR;				//Virtual Base PoinTeR (displacement/offset/RVA from base of type to begin of virtualBase instance)
		};
		if constexpr (std::is_base_of_v<signatur, Type>) {
			signatur* sig;
			void* sigVBPTR;
		}
		if constexpr (std::is_base_of_v<Type, PEParser>)	{
			//if all ifs above true, than Diamandshape inheritence
		}
		/*
		* returns pointer of unnamed class
		*/
		return;
	}
}