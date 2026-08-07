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
               std::int32_t start_x,
               std::int32_t start_y,
               std::uint8_t cluster_id) {
    if (start_x < 0 || start_x >= grid.width || start_y < 0 ||
        start_y >= grid.height) {
        return;
    }
    if (cellAt(grid, start_x, start_y) != kCellOccupied) {
        return;
    }

    cellAt(grid, start_x, start_y) = cluster_id;

    floodFill(grid, start_x + 1, start_y, cluster_id);
    floodFill(grid, start_x - 1, start_y, cluster_id);
    floodFill(grid, start_x, start_y + 1, cluster_id);
    floodFill(grid, start_x, start_y - 1, cluster_id);
}

}  // namespace ch3
