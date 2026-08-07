#include "flood_fill/bounded.h"

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

// Solution 1 STILL recurses, just with an explicit depth bound.
// MISRA C++ 2023 Rule 8.2.10 forbids any direct or indirect recursion;
// this function is covered by a formal rule deviation pointing at the
// kMaxSafeDepth derivation above as the safety case. See
// DEVIATIONS.md DEV-0001 (at repo root).
// NOLINTNEXTLINE(misc-no-recursion)
FloodFillStatus floodFillBounded(OccupancyGrid& grid, // parasoft-suppress MISRACPP2023-8_2_10-a "DEV-0001: bounded recursion per DEVIATIONS.md"
                                 std::int32_t x, std::int32_t y,
                                 std::uint8_t cluster_id,
                                 std::int32_t depth) {
    if (depth > kMaxSafeDepth) {
        return FloodFillStatus::kDepthLimitExceeded;
    }
    if (((x < 0) || (x >= grid.width)) || ((y < 0) || (y >= grid.height))) {
        return FloodFillStatus::kCompleted;
    }
    if (cellAt(grid, x, y) != kCellOccupied) {
        return FloodFillStatus::kCompleted;
    }
    cellAt(grid, x, y) = cluster_id;

    const std::int32_t next_depth = depth + kNeighbourStep;
    const std::int32_t x_east  = x + kNeighbourStep;
    const std::int32_t x_west  = x - kNeighbourStep;
    const std::int32_t y_south = y + kNeighbourStep;
    const std::int32_t y_north = y - kNeighbourStep;

    const FloodFillStatus s1 = floodFillBounded(grid, x_east, y,       cluster_id, next_depth);
    if (s1 == FloodFillStatus::kDepthLimitExceeded) {
        return s1;
    }
    const FloodFillStatus s2 = floodFillBounded(grid, x_west, y,       cluster_id, next_depth);
    if (s2 == FloodFillStatus::kDepthLimitExceeded) {
        return s2;
    }
    const FloodFillStatus s3 = floodFillBounded(grid, x,      y_south, cluster_id, next_depth);
    if (s3 == FloodFillStatus::kDepthLimitExceeded) {
        return s3;
    }
    return floodFillBounded(grid, x, y_north, cluster_id, next_depth);
}

}  // namespace ch3
