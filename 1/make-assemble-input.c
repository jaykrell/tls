#ifdef _M_ARM64
 armasm64 -o offset.obj offset-arm64.asm
#endif
#ifdef _M_ARM
 armasm -o offset.obj offset-arm32.asm
#endif
#ifdef _M_AMD64
 ml64 -c -Zi offset.asm
#endif
#ifdef _M_IX86
 ml -c -Zi offset.asm
#endif
