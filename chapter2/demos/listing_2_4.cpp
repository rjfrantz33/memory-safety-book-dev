// Listing 2.4: smart pointers to prevent temporal violations.
//
// make_unique ties the object's lifetime to the scope, so nothing is freed
// manually and the use-after-free from Listing 2.3 cannot recur.
//
// Owning the lifetime is not the same as guaranteeing a live object. A
// unique_ptr can still be empty, after a move or a reset, and dereferencing
// an empty one is undefined just like any null dereference. Listing 2.5
// checks the pointer before using it.

#include <iostream>
#include <memory>

int main() {
  auto ptr = std::make_unique<int>(42);

  int value = *ptr;  // Safe: ptr still owns a live object.
  std::cout << value << "\n";
  return 0;
}  // ptr goes out of scope and frees the integer.
