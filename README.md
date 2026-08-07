# Memory Safety in Safety-Critical C++

[![CI](https://github.com/rjfrantz33/memory-safety-book-dev/actions/workflows/ci.yml/badge.svg)](https://github.com/rjfrantz33/memory-safety-book-dev/actions/workflows/ci.yml)

Companion code for the book *Memory Safety in Safety-Critical C++*.
Every numbered listing in the book maps to a runnable Bazel target in
this repository, so the case studies can be built, scanned, and run
exactly as the chapters describe them.

## Repository layout

Each chapter lives under its own top-level directory and follows the
same structure:

```
chapterN/
├── include/             Public headers
├── src/                 Library implementations
├── demos/               Runnable binaries
└── test/                Unit tests
```

Chapter 2 is the exception: its listings are self-contained `main()`s with
no library behind them, so it ships `demos/` only.

A `README.md` inside each chapter directory covers that chapter's
listings, demo binaries, and static-analysis results:

- [Chapter 2: spatial and temporal memory safety](chapter2/README.md)
- [Chapter 3: stack overflow in flood-fill](chapter3/README.md)

## Tested platforms

| OS      | Compiler                    | Build | Test | clang-tidy |
| ------- | --------------------------- | :---: | :--: | :--------: |
| Linux   | GCC 13+                     |  yes  | yes  |    yes     |
| macOS   | Apple Clang 15+             |  yes  | yes  |     no     |
| Windows | MSVC 19.40+ (Visual Studio) |  yes  | yes  |     no     |

clang-tidy runs on Linux only; macOS and Windows compile and test but
skip the lint pass. CI runs the full matrix on every push and pull
request.

## Prerequisites

Three things: `git`, a C++17 compiler, and Bazel. A small number of
examples provide optional C++20 alternatives, which require a C++20
compiler. Bazelisk is the recommended way to install Bazel because it
pins the version from `.bazelversion` automatically.

Nothing else needs installing. GoogleTest and `rules_cc` are fetched by
Bazel on the first build, so that build needs network access. Everything
after it works offline.

### Linux (Debian or Ubuntu)

```bash
sudo apt update
sudo apt install -y build-essential git curl
sudo curl -fLo /usr/local/bin/bazel \
  https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64
sudo chmod +x /usr/local/bin/bazel
```

### macOS

```bash
xcode-select --install
brew install bazelisk
```

### Windows

Install Bazelisk from the
[releases page](https://github.com/bazelbuild/bazelisk/releases)
and add it to `PATH`. Visual Studio with the C++ workload supplies the
compiler.

Verify the install:

```bash
git --version
bazel --version
```

## Quick start

```bash
git clone https://github.com/rjfrantz33/memory-safety-book-dev.git
cd memory-safety-book-dev
bazel build //...
bazel test //...
```

The first build downloads GoogleTest and `rules_cc` from the Bazel
Central Registry, so it takes a few minutes and needs network access.
Subsequent builds are incremental.

## Build

```bash
bazel build //...
```

## Test

```bash
bazel test //...
```

For verbose test output:

```bash
bazel test //... --test_output=all
```

## Running the examples

`bazel test` covers the unit tests, but the listings themselves are
binaries you run. Every demo below works from a fresh clone with no
arguments and no setup.

Chapter 2, one target per listing:

| Run                                       | What it does                                                                                                                    |
| ----------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `bazel run //chapter2/demos:listing_2_1` | Listing 2.1, the spatial violation. Prints a garbage value, then crashes. **This crash is the point of the listing, not a defect.** |
| `bazel run //chapter2/demos:listing_2_2` | Listing 2.2, the bounds check. Reports the out-of-range index instead of corrupting memory.                                       |
| `bazel run //chapter2/demos:listing_2_3` | Listing 2.3, the temporal violation. Prints a different garbage value on every run and exits 0. **Silent corruption, by design.**  |
| `bazel run //chapter2/demos:listing_2_4` | Listing 2.4, `make_unique`. Prints 42.                                                                                          |
| `bazel run //chapter2/demos:listing_2_5` | Listing 2.5, both checks combined. Prints a reading, then two refusals.                                                          |

Chapter 3:

| Run                                       | What it does                                                                                              |
| ----------------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| `bazel run //chapter3/demos:original`     | Recursive flood-fill. The 50x50 grid finishes; the 500x500 grid crashes with SIGSEGV. **The crash is the chapter's argument.** |
| `bazel run //chapter3/demos:instrumented` | Same algorithm with a depth observer showing how deep it got before being killed.                          |
| `bazel run //chapter3/demos:solutions`    | All five Part II variants on a 50x50 grid, printing status and labelled-cell count for each.               |

Two of these crash on purpose. `//chapter2/demos:listing_2_1` and
`//chapter3/demos:original` are counter-examples, and a non-zero exit is
the expected result. Everything else exits 0.

To watch a sanitizer catch the use-after-free in listing 2.3:

```bash
bazel run //chapter2/demos:listing_2_3 --config=asan
```

The per-chapter READMEs explain what each listing demonstrates and how it
maps to the book.

## MISRA C++ 2023 compliance

The case-study chapters, chapter 3 onward, are scanned with Parasoft
C/C++test against the MISRA C++ 2023 rule set. Per-chapter results live
in the chapter READMEs, and the deviation register with justifications
is in [DEVIATIONS.md](DEVIATIONS.md). Chapter 2 is introductory and is
not scanned.

## Lint (optional)

clang-tidy is configured in `.clang-tidy` and runs on the Linux CI job.
To run locally on Linux:

```bash
bazel build //... --config=clang-tidy
```

The config treats lint warnings as errors. To target a single
translation unit, pass its label instead of `//...`.

Chapter 2's demos are excluded from the lint pass. They reproduce the
book's listings verbatim, and satisfying the style checks would mean
diverging from the printed text. Chapter 3 onward are held to the full
pass.

## Sanitizers (optional)

Three sanitizer configurations live in `.bazelrc`:

```bash
bazel run <target> --config=asan      # AddressSanitizer
bazel run <target> --config=ubsan     # UndefinedBehaviorSanitizer
bazel run <target> --config=tsan      # ThreadSanitizer
```

Sanitizer builds run roughly twice as slowly as the default build. Use
them when verifying a chapter's specific bug-catching behaviour.

## Cleaning

```bash
bazel clean
```

To remove all Bazel output, including the cached build server:

```bash
bazel clean --expunge
```

## Contributing

N/A until further notice.

## License

See [`LICENSE`](LICENSE).
