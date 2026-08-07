#include "flood_fill/recursive.h"

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

// floodFill is the chapter's counter-example. It violates MISRA C++
// 2023 Rule 7.5.2 / AUTOSAR C++14 A7-5-2 by calling itself, and the
// whole point of chapter 3 is that this violation produces a
// stack-exhaustion crash on realistic inputs. Solutions 1, 2, and 3
// in PART III show three ways to fix it. The misc-no-recursion
// suppression here is what makes the lesson visible at the tool
// level: if you grep for NOLINT(misc-no-recursion) across the
// codebase you find exactly the functions the chapter is criticising.
// NOLINTNEXTLINE(misc-no-recursion)
void floodFill(OccupancyGrid& grid,
               std::int32_t x, std::int32_t y,
               std::uint8_t cluster_id) {
    if (x < 0 || x >= grid.width || y < 0 || y >= grid.height) {
        return;
    }
    if (cellAt(grid, x, y) != kCellOccupied) {
        return;
    }

    cellAt(grid, x, y) = cluster_id;

    floodFill(grid, x + 1, y, cluster_id);
    floodFill(grid, x - 1, y, cluster_id);
    floodFill(grid, x, y + 1, cluster_id);
    floodFill(grid, x, y - 1, cluster_id);
}

}  // namespace ch3
