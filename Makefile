DIRS=1 2 3 4

all: $(DIRS)
  !pushd $** && nmake -nologo -$(MAKEFLAGS) $@

clean: $(DIRS)
  !pushd $** && nmake -nologo -$(MAKEFLAGS) $@

test: $(DIRS)
  !pushd $** && nmake -nologo -$(MAKEFLAGS) $@
