This demonstrates cross dll inlined TLS access.
i.e. for https://github.com/rust-lang/rust/pull/84876

---

In this version, the caller maintains its own thread local cache,
initialized on demand.

Like case 3, no assembly.