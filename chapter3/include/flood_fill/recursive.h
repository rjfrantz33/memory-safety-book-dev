/// @file flood_fill/recursive.h
/// @brief Defective recursive flood-fill from chapter 3 PART I (Listing 3.1).
///
/// This function exists in this codebase EXCLUSIVELY to be the
/// counter-example. It compiles cleanly, passes the small-grid demo,
/// and crashes the process on the large-grid demo by exhausting the
/// call stack. Do not link this header from any code that needs to
/// stay alive on a constrained target.
///
/// The depth-tracking variant used by the stack-exhaustion demo
/// (`floodFillInstrumented` + `DepthObserver`) lives under
/// src/flood_fill/internal/ and is intentionally not part of the
/// public API.

#ifndef CH3_FLOOD_FILL_RECURSIVE_H
#define CH3_FLOOD_FILL_RECURSIVE_H

#include <cstdint>

#include "occupancy_grid.h"

namespace ch3 {

/// @brief Recursively label every occupied cell in the connected region
///        containing (x, y) with cluster_id.
///
/// @warning This function cannot fail gracefully - it either returns
///          normally or the process dies with SIGSEGV when the recursion
///          overruns the stack guard page.
///
/// @param grid The occupancy grid to label in-place.
/// @param start_x Starting column index.
/// @param start_y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
void floodFill(OccupancyGrid& grid,
               std::int32_t start_x,
               std::int32_t start_y,
               std::uint8_t cluster_id);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_RECURSIVE_H
