#ifndef ALLOCATOR_INITIALIZED 
	#define ALLOCATOR_INITIALIZED 12345
#endif // !ALLOCATOR_INITIALIZED 
namespace PEParserNamespace {
	class Allocator {
		size_t size;
	public:
		int initialized;
		Allocator(size_t size) :size(size),initialized(ALLOCATOR_INITIALIZED) {
			
		}
		~Allocator() {

		}
		void* operator()() {
			return new char[size];
		}

	};
}

/*
Anforderungen
- Alignment
- muss Memory selber managen oder dem Aufrufer überlassen können
*/