#pragma once
#include "Preprocessor.h"
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
	template<typename T, typename lambda>
	class Iterable {
		//typedef void(__cdecl* Callback)(T);
		using lambdaNoRef = typename remove_reference<lambda>::_Const_thru_ref_type;
		T begin;
		T end;
		lambdaNoRef callback;
	public:
		Iterable(T t, size_t size) noexcept :
			begin(&t[0]),
			end(&t[size - 1])/*,
			callback([](T) ->void{}) */{};
		Iterable(T t, size_t size, lambdaNoRef callback) noexcept :
			begin(&t[0]),
			end(&t[size - 1]),
			callback(callback) {}
		auto operator()(lambda callback) noexcept {
			return for_each(begin, end, callback);
		}
		auto operator()() noexcept {
			return for_each(begin, end, callback);
		}
	};
}