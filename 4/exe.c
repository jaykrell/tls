int* FooTraditional(void);
int __cdecl printf(const char* a, ...);

__declspec(thread) int* foo;

__declspec(noinline) int* FooSlow(void)
{
    int* f = FooTraditional();
    foo = f;
    return f;
}

// export just so we can disasm in isolation
// If you first capture the values, this can be faster.
__declspec(dllexport) extern __forceinline int* FooInlinable(void)
{
    int* f = foo;
    if (f) return f; // likely
    return FooSlow();
}

// name the strings for easier to read disasm
// extern so disasm shows symbols
extern const char pn[] = "%p\n";

int main(void)
{
    printf(pn, FooTraditional());
    printf(pn, FooInlinable());
    return 0;
}

// This is usually in the C runtime but this small program has no C runtime.
const unsigned _tls_index;

#include <windows.h>
// This is usually in the C runtime but this small program has no C runtime.
// This symbol _tls_used is special in the linker.
// The linker sets the TLS data directory to point to and size _tls_used.
extern const IMAGE_TLS_DIRECTORY _tls_used =
{
    0,              // StartAddressOfRawData
    0,              // EndAddressOfRawData
    (size_t)&_tls_index, // PDWORD AddressOfIndex
    0,              // AddressOfCallBacks
    0,              // SizeOfZeroFill
    0,              // Characteristics
};
