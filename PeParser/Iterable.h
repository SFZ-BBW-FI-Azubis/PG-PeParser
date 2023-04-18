#pragma once
#include "Preprocessor.h"
#include <type_traits>
namespace PEParserNamespace {
	template <class InIt, class Fn>
	inline void for_each(InIt _First, InIt _Last, Fn _Func) noexcept {
		disable
		auto _UFirst = _First;
		auto _ULast = _Last;
		for (; _UFirst <= _ULast; ++_UFirst) {
			_Func(/***/_UFirst);
		}

		return;
	}
	//remove_reference_t<_Dx>
	template <class _Ty>
	struct remove_reference {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&> {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty&;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&> {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty&&;
	};
	template<typename T, typename lambda = void*>
	class Iterable {
		typedef void(__cdecl* Function)(T);
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
		auto operator()(/*lambda*/auto callback) noexcept {
			return for_each(begin, end, callback);
		}
		auto operator()() noexcept {
			return for_each(begin, end, callback);
		}
	};
}