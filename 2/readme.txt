This demonstrates cross dll inlined TLS access.
i.e. for https://github.com/rust-lang/rust/pull/84876

The dll housing the TLS is partially in assembly because
Visual C++ does not expose the required pieces efficiently.
That is, you can compute the offset at runtime,
but cannot make a link time constant without assembly.

---

In this version, the caller does some initialization and by paying
that, removes two memory accessing instructions from each TLS access.

This version uses assembly because the C compiler cannot produce
section relative relocations (other than part of larger constructs).

This version is not likely recommended, in that, if you can afford
to do initialization, then you can also remove the assembly See version 3.
