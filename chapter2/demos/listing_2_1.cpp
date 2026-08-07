// Listing 2.1: a spatial violation, writing beyond buffer bounds.
//
// Both accesses are undefined behaviour. The write lands six positions past
// the end of an array the function owns; the read lands one position before
// the start. Neither is diagnosed at run time.
//
// The result is platform-specific by definition. Section 2.4.2 reports
// garbage on Linux and a crash on macOS (Apple clang++) and on Compiler
// Explorer (x86-64 gcc), all at -std=c++17 -Wall -Wextra -Wpedantic.
//
// On Ubuntu 24.04 with g++ 15.2.0 this build does both: the read produces
// a garbage value, the write corrupts the stack, and the process dies on
// return from main with exit status 139.
//
// What gets printed depends on where stdout goes. On a terminal the value
// appears first and differs on every run: 31122, 29545, 32240. Through a
// pipe nothing appears at all, because std::cout is fully buffered there
// and the buffer is still unflushed when the process dies. Compiler
// Explorer and CI logs both pipe stdout, so both show a bare crash.
//
// Clang warns here only because the indices are constants; make them
// run-time values and the warning disappears. g++ 15.2.0 says nothing
// either way.
//
// Listing 2.2 is the bounds-checked version.

#include <iostream>

int main() {
    int buffer[10];

    buffer[15] = 42;         // Out-of-bounds write: undefined behaviour.
    int value = buffer[-1];  // Out-of-bounds read: undefined behaviour.

    std::cout << "Value: " << value << "\n";
    return 0;
}
