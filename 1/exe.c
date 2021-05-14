#include <windows.h>

__declspec(dllimport) extern const unsigned FooIndex;
__declspec(dllimport) extern const unsigned FooOffset;
int* FooTraditional(void);
int __cdecl printf(const char* a, ...);

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
__declspec(dllexport) extern __forceinline int* FooInlinable(void)
{
    // This is six instructions plus ret.
    // Some of the instructions can be reused across multiple TLS accesses.
    return (int*)(DllTls(FooIndex) + FooOffset);
}

// name the strings for easier to read disasm
// extern so disasm shows symbols
extern const char failed[] = "failed\n";
extern const char pn[] = "%p\n";

int main(void)
{
    if (FooTraditional() != FooInlinable())
    {
        printf(failed);
        if (IsDebuggerPresent()) __debugbreak();
    }
    printf(pn, FooTraditional());
    printf(pn, FooInlinable());
    return 0;
}
