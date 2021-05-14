__declspec(thread) int foo;

__declspec(dllexport)
int* FooTraditional(void)
{
    // Four instructions plus ret.
    return &foo;
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


// Support portable assembly-free form, but requires initialization in caller.
#ifdef _WIN64
#define TLS (0x58)
#else
#define TLS (0x2C)
#endif

char** Tls(void)
{
#ifdef _M_AMD64
    return (char**)__readgsqword(TLS); // save one instruction
#elif defined(_M_IX86)
    return (char**)__readfsdword(TLS); // save one instruction
#else
    return *(char***)(TLS + (char*)NtCurrentTeb());
#endif
}

char* DllTls(unsigned tlsIndex)
{
    return Tls()[tlsIndex];
}

__declspec(dllexport) unsigned GetFooIndex(void)
{
    // Do not use this in hot path. Cache the result
    // or import data (see version 1 or 2).
    return _tls_index;
}

__declspec(dllexport) unsigned GetFooOffset(void)
{
    // This like FooOffset, but requires no assembly, but requires running code.
    //
    // Do not use this in hot path. Cache the result
    // or import data (see version 1 or 2).
    return (char*)&foo - DllTls(GetFooIndex());
}
