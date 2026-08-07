// Listing 2.1: a spatial violation, writing beyond buffer bounds.
//
// Both accesses are undefined behaviour. The write lands six positions past
// the end of an array the function owns; the read lands one position before
// the start. Neither is diagnosed at run time, and the program exits 0.
//
// The result is platform-specific by definition. Section 2.4.2 reports
// garbage on Linux and a crash on macOS (Apple clang++) and on Compiler
// Explorer (x86-64 gcc), all at -std=c++17 -Wall -Wextra -Wpedantic.
//
// On Ubuntu 24.04 with g++ 15.2.0 this build does both: it prints a garbage
// value, then segfaults on return from main. The two accesses do different
// damage. The read below produces the value; the write corrupts the stack
// and kills the process on return. The value is not stable either. Five
// runs on a terminal gave 29544, 29003, 32236, 31729, 29993, and the same
// binary with stdout piped printed 0 every time.
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
