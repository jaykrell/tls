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
