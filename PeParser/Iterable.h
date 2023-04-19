#pragma once
#include "Preprocessor.h"
#include <concepts>
#include <iostream>
namespace PEParserNamespace {
	template <typename InIt, class Fn>
	inline bool Iterable_for_each(InIt _First, InIt _Last, Fn _Func) noexcept {
		disable
			auto _UFirst = _First;
			auto _ULast = _Last;
			unsigned char counter = 0;	//byte
			for (; _UFirst <= _ULast; ++_UFirst) {
				if(_Func(_UFirst, counter++)) return true;
			}
		return false;
	}
	template<typename T, typename lambda = void*>
	class Iterable {
		typedef bool(__cdecl* Function)(T);
		using lambdaNoRef = typename remove_reference<lambda>::type;//_Const_thru_ref_type;
		T begin;
		T end;
		lambdaNoRef callback;	//still same as void(__cdecl* name)(T)
	public:
		Iterable(T t, size_t size) noexcept :
			begin(&t[0]),
			end(&t[size - 1])/*, callback([](T) ->void{}) // this wont work callback is not the same type!!!*/
		{	
			//if constexpr (/*std::is_default_constructible<lambdaNoRef>*/std::is_convertible<lambdaNoRef, Function> == true) {
			//	callback = lambdaNoRef();
			//};
			callback = lambdaNoRef();
		};
		/*Iterable(T t, size_t size, lambdaNoRef callback) noexcept :
			begin(&t[0]),
			end(&t[size - 1]),
			callback(callback) {}*/
		template<typename opT>
		bool operator()(opT callback) noexcept {
			return Iterable_for_each<T>(begin, end, callback);
		}
		bool operator()() noexcept {
			return Iterable_for_each<T,lambdaNoRef>(begin, end, callback);
		}
	};
	/*
	* for future: generic class Calable
	*		template<typename CallableType, typename AlgorithmType, typename ...AlgorithmParamsType>
	*		auto operator()(CallableType callback, AlgorithmType algorithm)
	*/
}

/*
//Demonstration __________________________________________________________________________________
	std::string lol = "Hallo welt";
	int myvector[5] = {0,1,2,3,4};
	PEParserNamespace::Iterable<int*, decltype([](int* single, auto counter)->bool {
		std::cout << *single << std::endl;
		return false;
		})> iterable(myvector, 5);
	iterable();
	int myvector2[5] = { 5,6,7,8,9 };
	PEParserNamespace::Iterable<int*> iterable2(myvector2, 5);
	iterable2([&](int* single, auto counter)->bool {
		std::cout << *single << std::endl;
		std::cout << lol << std::endl;
		return false;	//iterate to last element
		});	// I called iterable() -> that small mistake cost me a whole day to find :(
	//std::unique_ptr

*/