// Listing 2.2: bounds checking to prevent spatial violations.
//
// The protection comes from the explicit check, not from the container.
// std::array::operator[] is not required to verify the index, so an
// out-of-range access through it is undefined behaviour exactly as with the
// raw array in Listing 2.1. What std::array adds is that it carries its own
// size and never decays to a pointer, so size() stays reliable across
// function boundaries.
//
// at() is the accessor guaranteed to check; it throws std::out_of_range.

#include <array>
#include <cstddef>
#include <iostream>

int main() {
    std::array<int, 10> buffer{};
    std::size_t index = 15;

    if (index < buffer.size()) {
        buffer[index] = 42;
    } else {
        std::cerr << "Index " << index << " out of bounds\n";
    }
    return 0;
}
