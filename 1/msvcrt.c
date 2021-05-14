// A minimal C runtime -- import library only.

__declspec(dllexport) void __cdecl printf(const char* a, ...)
{
    __debugbreak();
}
