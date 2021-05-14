This demonstrates cross dll inlined TLS access.
i.e. for https://github.com/rust-lang/rust/pull/84876

---

In this version, the caller does some initialization and by paying
that, removes two memory accessing instructions from each TLS access.

As well, for the cost of doing some initialization, the assembly can be removed.
