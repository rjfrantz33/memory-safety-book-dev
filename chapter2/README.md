# Chapter 2: spatial and temporal memory safety

Chapter 2 introduces the two dimensions every memory access has to get
right. A spatial violation reaches the wrong location. A temporal violation
reaches the right location at the wrong time, after the object that lived
there is gone. Section 2.4 pairs each violation with the check that prevents
it, and Listing 2.5 shows why neither check alone is enough.

Toolchain setup, build, test, lint, and sanitizer instructions are in
the [repository README](../README.md). To build only this chapter:

```bash
bazel build //chapter2/...
```

## Layout

```
chapter2/
└── demos/               Runnable binaries, one per listing
```

Every listing in this chapter is a self-contained `main()` with no shared
types or library code behind it, so there is no `include/`, `src/`, or
`test/` here. Chapter 3 onward use the full structure.

## Listings and their targets

| Listing | Description                                     | Where it lives in the repo       | Run in the browser                        |
| ------- | ----------------------------------------------- | -------------------------------- | ----------------------------------------- |
| 2.1     | Spatial violation: writing beyond buffer bounds | `chapter2/demos/listing_2_1.cpp` | [godbolt](https://godbolt.org/z/qbM698h5v) |
| 2.2     | Bounds checking to prevent spatial violations   | `chapter2/demos/listing_2_2.cpp` | [godbolt](https://godbolt.org/z/Mhzv99n9z) |
| 2.3     | Temporal violation: accessing freed memory      | `chapter2/demos/listing_2_3.cpp` | [godbolt](https://godbolt.org/z/nWGhGW418) |
| 2.4     | Smart pointers to prevent temporal violations   | `chapter2/demos/listing_2_4.cpp` | [godbolt](https://godbolt.org/z/enG6nos8a) |
| 2.5     | Combining spatial and temporal checks           | `chapter2/demos/listing_2_5.cpp` | [godbolt](https://godbolt.org/z/zY449ns1n) |

The Compiler Explorer links run the same source on x86-64 gcc 15.2 with
`-std=c++17 -Wall -Wextra -Wpedantic`, the compiler and flags section
2.4.2 reports. They need no toolchain, so they are the fastest way to
check a listing without cloning.

Listing 2.1 shows only a crash there, no `Value:` line, because Compiler
Explorer captures stdout through a pipe. See below for why that differs
from a terminal.

Listing 2.5 in the book ends at the `SensorBuffer` class. The demo adds a
`main()` that drives it through all three paths (in range, out of range,
freed) so the target is runnable like the rest.

```bash
bazel run //chapter2/demos:listing_2_1
bazel run //chapter2/demos:listing_2_2
bazel run //chapter2/demos:listing_2_3
bazel run //chapter2/demos:listing_2_4
bazel run //chapter2/demos:listing_2_5
```

## Listings 2.1 and 2.3 are undefined behaviour on purpose

These two are counter-examples. They compile, they are not diagnosed at run
time, and what they print is not reproducible across platforms or even
across runs. Section 2.4.2 reports the outputs observed on Ubuntu 24.04
(g++ 15.2.0), macOS 10.14.6 (Apple LLVM 10.0.1), and Compiler Explorer
(x86-64 gcc 15.2), all at `-std=c++17 -Wall -Wextra -Wpedantic`. Your
numbers will differ; that is the point.

Observed here on Ubuntu 24.04 with g++ 15.2.0:

| Target          | Result                                                                                                              |
| --------------- | ------------------------------------------------------------------------------------------------------------------- |
| `listing_2_1` | Prints a garbage value, then segfaults on return from `main`, exit 139. The two accesses do different damage: `buffer[-1]` produces the value, `buffer[15] = 42` corrupts the stack and kills the process on return. No warning from g++; Clang warns only because the indices are constants. |
| `listing_2_3` | Exits 0 and prints a different garbage value on every run. No warning from any compiler.                            |

Listing 2.1 prints three different things on the same machine depending
on where stdout goes.

| stdout                    | Output                                     |
| ------------------------- | ------------------------------------------ |
| A terminal                | `Value: 31122`, a different number each run |
| A pipe, default buffering | Nothing                                    |
| A pipe, unbuffered        | `Value: 0`, the same each run              |

Exit status is 139 in all three cases. The value varies because
`buffer[-1]` reads a stack slot holding whatever startup left there, and
that differs with the buffering mode. The line disappears on a pipe
because `std::cout` is fully buffered there, and the buffer is still
unflushed when `buffer[15] = 42` kills the process on return from
`main`.

Compiler Explorer and CI logs both capture stdout through a pipe, so
both show the crash with no output.

Because the behaviour is undefined, these are demonstrated with a sanitizer
rather than a unit test. A test that reads freed memory is itself undefined.

```bash
bazel run //chapter2/demos:listing_2_3 --config=asan
```

AddressSanitizer reports `heap-use-after-free` on the read at
`listing_2_3.cpp` and names the `delete` as the site that freed the region.

Both listings trip clang-tidy, which is expected and left as is.
