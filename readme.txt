This demonstrates cross dll inlined TLS access.
i.e. for https://github.com/rust-lang/rust/pull/84876

The dll housing the TLS is partially in assembly because
Visual C++ does not expose the required pieces efficiently.
That is, you can compute the offset at runtime,
but cannot make a link time constant without assembly.
