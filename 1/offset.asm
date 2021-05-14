ifdef rax

extern foo:dword
.const

; Get the link time offset of the thread local within the dll's thread locals.
; This is usually in the middle of an instruction.
; The C++ compiler does not expose getting this statically initialized, so use assembly.
; sectionrel is the key. The C++ compiler puts foo in the .tls$ section which
; must be special to the linker (w/o the $ presumably).
public FooOffset
FooOffset dd sectionrel foo

else

.model flat
extern _foo:dword
.const

public __tls_array
__tls_array equ 2ch

public _FooOffset
_FooOffset dd sectionrel _foo

endif

end
