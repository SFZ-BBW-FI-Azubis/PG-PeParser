#pragma once
#include "Preprocessor.h"
#include <Windows.h>
#include <concepts>
#include <type_traits>
#include <concepts>
#include <iostream>
//#include "PEParser.h"
//I think I will have to implement getter and setter either
//as methods in classes/structs (make everything privat and the compiler tells where to replace with new getter / setter)
//or as macros in präprocessor.h
namespace PEParserNamespace {
	template<typename T1, typename ...Tn> 
	constexpr T1 unpack(T1 t1, Tn... ) noexcept {
		return t1;
	}	//compiletime function, disapears after compilation
	typedef struct functionExecutionLog {
		PEParser_OFFSET bool failed;
		union alignas(void*) Code {
			void* codeVoidptr;
			unsigned long codeUnsignedLong;
			int codeInt;
		} code;			//64bit alignment
		template<typename ...T>
		functionExecutionLog(functionExecutionLog* pfx, T*... pderived) {
			static_assert(!(sizeof...(pderived) > 1), "to much Arguments");
			std::cout << sizeof...(pderived)<<"	sadasdfasdfasdfasdfasdfasdfasdf\n";
			std::cout << (pfx->code.codeInt)<<"\n";
			std::cout << pfx<<"\n";
			std::cout << unpack(pderived...)->ppEParser.Dummy.pEParserFunctionExecutionLog.code.codeInt <<"\n";
			std::cout << unpack(pderived...)<<"\n";
			std::cout << (int)pfx - (int)unpack(pderived...)<<"\n";
			if constexpr (sizeof...(pderived) == 1) {
				//expand parameterpack
				//calculate offset
				// I dont want any typeconversions from bsp. uInt to Bool
				alignas(void*) unsigned int temp = 123012+(unsigned int)pfx - (unsigned int)unpack(pderived...);
				// memcpy does not seem to work, dest and src mem overlap, or some reordering problems
				memcpy(&(this->failed), &temp, sizeof(void*));
				//this->failed = 1234;//(unsigned int)pfx - (unsigned int)unpack(pderived...); //&(*variable)
			}	else	{
				//reinterpret_cast<functionExecutionLog*>(this->failed) = *pfx;
				this->failed = &(pfx->failed);
			}
		}
		functionExecutionLog() {};
		//getter
		template<typename ...T> bool getFailed(T... derived) {
			static_assert(sizeof...(derived) > 1, "to much Arguments");
			if constexpr(sizeof...(derived) = 1)	{
				return
					reinterpret_cast<functionExecutionLog*>(
						reinterpret_cast<unsigned char>(derived[0])[this->failed]	//when failed = 0 then instance of base is leftmost based inherited and non virtual (base needs to be non virtual anyways)
						)->failed;
			}	else {
				return reinterpret_cast<functionExecutionLog*>(this->failed)->failed;
			}
		}
		functionExecutionLog::Code getCode() {
			return reinterpret_cast<functionExecutionLog*>(this->failed)->code;
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