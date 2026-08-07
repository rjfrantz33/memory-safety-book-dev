#include "occupancy_grid.h"

#include <cstddef>
#include <cstdint>
#include <vector>

#include "types.h"

namespace ch3 {

// Index arithmetic widens to std::size_t BEFORE the multiply, not after.
// Doing `x * grid.height_` first and then casting is the
// bugprone-misplaced-widening-cast bug: the multiplication has already
// happened in int, so any overflow has already happened too. The cast
// after the fact is decoration. For a 50x50 demo grid the overflow case
// is hypothetical, but the chapter is about safety-critical habits, and
// "widen at the boundary" is one of them.
std::uint8_t& cellAt(OccupancyGrid& grid, std::int32_t x, std::int32_t y) {
    const std::size_t idx =
        ((static_cast<std::size_t>(x) * static_cast<std::size_t>(grid.height)) +
         (static_cast<std::size_t>(y)));
    return grid.cells[idx];
}

std::uint8_t cellAt(const OccupancyGrid& grid, std::int32_t x, std::int32_t y) {
    const std::size_t idx = ((static_cast<std::size_t>(x)) *
                             static_cast<std::size_t>(grid.height)) +
                            (static_cast<std::size_t>(y));
    return grid.cells[idx];
}

OccupancyGrid makeFullyOccupiedGrid(std::int32_t width, std::int32_t height) {
    const std::size_t cell_count =
        static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
    return OccupancyGrid{
        width, height, std::vector<std::uint8_t>(cell_count, kCellOccupied)};
}

std::int32_t countLabelled(const OccupancyGrid& grid, std::uint8_t cluster_id) {
    std::int32_t n = 0;
    for (auto c : grid.cells) {
        if (c == cluster_id) {
            ++n;
        }
    }
    return n;
}

}  // namespace ch3
