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
//
// Formatting is pinned below: the parasoft-suppress directive and its
// justification string have to stay on one line or Parasoft stops
// recognising the suppression, which silently reinstates the 8.2.10
// violation that DEV-0001 covers. NOLINTNEXTLINE has to stay directly
// above the signature for the same reason, so both comments sit inside
// the pinned region.
// clang-format off
// NOLINTNEXTLINE(misc-no-recursion)
FloodFillStatus floodFillBounded(OccupancyGrid& grid, // parasoft-suppress MISRACPP2023-8_2_10-a "DEV-0001: bounded recursion per DEVIATIONS.md"
                                 std::int32_t start_x, std::int32_t start_y,
                                 std::uint8_t cluster_id,
                                 std::int32_t depth) {
    // clang-format on
    if (depth > kMaxSafeDepth) {
        return FloodFillStatus::kDepthLimitExceeded;
    }
    if (((start_x < 0) || (start_x >= grid.width)) ||
        ((start_y < 0) || (start_y >= grid.height))) {
        return FloodFillStatus::kCompleted;
    }
    if (cellAt(grid, start_x, start_y) != kCellOccupied) {
        return FloodFillStatus::kCompleted;
    }
    cellAt(grid, start_x, start_y) = cluster_id;

    // The depth increment is 1, not kNeighbourStep. kNeighbourStep is a
    // spatial offset to an adjacent cell; the two are equal today only by
    // coincidence, and reusing it here would silently break the
    // kMaxSafeDepth stack derivation if the neighbourhood ever changed.
    const std::int32_t next_depth = depth + 1;

    const FloodFillStatus s1 = floodFillBounded(
        grid, start_x + kNeighbourStep, start_y, cluster_id, next_depth);
    if (s1 == FloodFillStatus::kDepthLimitExceeded) {
        return s1;
    }
    const FloodFillStatus s2 = floodFillBounded(
        grid, start_x - kNeighbourStep, start_y, cluster_id, next_depth);
    if (s2 == FloodFillStatus::kDepthLimitExceeded) {
        return s2;
    }
    const FloodFillStatus s3 = floodFillBounded(
        grid, start_x, start_y + kNeighbourStep, cluster_id, next_depth);
    if (s3 == FloodFillStatus::kDepthLimitExceeded) {
        return s3;
    }
    return floodFillBounded(
        grid, start_x, start_y - kNeighbourStep, cluster_id, next_depth);
}

}  // namespace ch3
