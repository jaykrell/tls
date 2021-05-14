# This version has no assembly.

# -GL building an .exe will assume _tls_index is 0.
CFLAGS=    -Gy -O2 -Z7 -Zl -nologo

# x86 requires libcmt.lib for _tls_array, absolute symbol equal to 2c.
LINK_FLAGS=-incremental:no -opt:ref,icf -nodefaultlib libcmt.lib

all: exe.exe exe.pdb dll.dll dll.pdb

# Delete is required to prevent incremental build from building every time.
msvcrt.lib: msvcrt.c Makefile
 -del msvcrt.lib 2>nul:
 cl $(CFLAGS) -LD msvcrt.c -link -noentry $(LINK_FLAGS)
 del msvcrt.dll msvcrt.pdb

kernel32.lib: kernel32.c Makefile kernel32.def
 -del kernel32.lib 2>nul:
 cl $(CFLAGS) -LD kernel32.c -link -noentry $(LINK_FLAGS) -def:kernel32.def
 del kernel32.dll kernel32.pdb

# Delete is required to prevent incremental build from building every time.
dll.dll dll.lib dll.pdb: dll.c Makefile
 -del dll.lib 2>nul:
 cl $(CFLAGS) -LD dll.c -link -noentry $(LINK_FLAGS)

exe.exe exe.pdb: dll.dll dll.lib Makefile msvcrt.lib kernel32.lib
 cl $(CFLAGS) exe.c dll.lib .\msvcrt.lib -link -entry:main .\kernel32.lib $(LINK_FLAGS)

test: exe.exe exe.pdb
 exe.exe

clean:
 -del 2>nul: \
    dll.exp \
    dll.lib \
    dll.dll \
    dll.obj \
    dll.pdb \
    exe.exe \
    exe.exp \
    exe.lib \
    exe.obj \
    exe.pdb \
    kernel32.dll \
    kernel32.exp \
    kernel32.lib \
    kernel32.obj \
    kernel32.pdb \
    msvcrt.dll \
    msvcrt.exp \
    msvcrt.lib \
    msvcrt.obj \
    msvcrt.pdb \
