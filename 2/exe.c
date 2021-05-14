#include <windows.h>

__declspec(dllimport) extern const unsigned FooIndex;
__declspec(dllimport) extern const unsigned FooOffset;
int* FooTraditional(void);
int __cdecl printf(const char* a, ...);

// Optional optimization if you can run init.
// Also would want to isolate these from frequenty writes.
// This saves two instructions per access, which are both memory reads.
// Cachealign because these are write-once read-many, avoid sharing cache
// with write-many.
DECLSPEC_CACHEALIGN struct
{
    unsigned Offset;
    unsigned Index;
} LocalFoo;

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

// export just so we can disasm in isolation
// If you first capture the values, this can be faster.
__declspec(dllexport) extern __forceinline int* FooInlinable(void)
{
    // This is four instructions plus ret.
    // Some of the instructions can be reused across multiple TLS accesses.
    return (int*)(DllTls(LocalFoo.Index) + LocalFoo.Offset);
}

// name the strings for easier to read disasm
// extern so disasm shows symbols
extern const char failed[] = "failed\n";
extern const char pn[] = "%p\n";

int main(void)
{
    // Init for possibly faster form.
    LocalFoo.Index = FooIndex;
    LocalFoo.Offset = FooOffset;

    if (FooTraditional() != FooInlinable())
    {
        printf(failed);
        if (IsDebuggerPresent()) __debugbreak();
    }
    printf(pn, FooTraditional());
    printf(pn, FooInlinable());
    return 0;
}
