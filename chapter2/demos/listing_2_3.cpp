// Listing 2.3: a temporal violation, accessing freed memory.
//
// The address stays in bounds. The object behind it does not survive the
// delete, so the dereference reads storage the program no longer owns.
//
// The read may return 42 if the memory has not been reused, or garbage, or
// it may crash. Section 2.4.2 reports a different garbage value on every run
// on Linux (g++) and the original value on macOS (Apple clang++), as if
// nothing had happened. All three outcomes are undefined behaviour, and no
// compiler on any of the three platforms diagnoses this one.
//
// Run under AddressSanitizer to make the read stop the program:
//   bazel run //chapter2/demos:listing_2_3 --config=asan
//
// Listing 2.4 removes the manual delete that opens the window.

#include <iostream>

int main() {
    int* ptr = new int(42);
    delete ptr;  // The object is gone; ptr still holds its address.

    int value = *ptr;  // Use-after-free: undefined behaviour.
    std::cout << value << "\n";
    return 0;
}
