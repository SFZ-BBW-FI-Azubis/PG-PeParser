#include "Preprocessor.h"
namespace PEParserNamespace {
	template <class InIt, class Fn>
	void for_each(InIt _First, InIt _Last, Fn _Func) noexcept {
		auto _UFirst = _First;
		auto _ULast = _Last;
		for (; _UFirst <= _ULast; ++_UFirst) {
			_Func(*_UFirst);
		}

		return;
	}

	template<typename T>
	class Iterable {
		typedef void(__cdecl* Callback)(int&);
		T begin;
		T end;
		Callback callback;
	public:
		const Iterable(T t, size_t size) noexcept :
			begin(&t[0]),
			end(&t[size - 1]),
			callback(nullptr) {};
		const Iterable(T t, size_t size, Callback callback) noexcept :
			begin(&t[0]),
			end(&t[size - 1]),
			callback(callback) {};
		const auto operator()(Callback callback) noexcept {
			return for_each(begin, end, callback);
		}
		const auto operator()() noexcept {
			return for_each(begin, end, callback);
		}
	};
}