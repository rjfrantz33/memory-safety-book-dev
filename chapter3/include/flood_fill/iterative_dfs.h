/// @file flood_fill_iterative_dfs.h
/// @brief Solution 2: iterative DFS flood-fill with a function-local worklist
///        (chapter 3 Listing 3.5).
///
/// No recursion. No dynamic allocation at call time. The worklist is a
/// std::array<Coordinate, kMaxCells> declared as a function-local
/// automatic variable, so it lives on the caller's stack frame. Per-call
/// stack cost is therefore ~20 KB for kMaxCells = 2500. Chapter 3
/// section 3.6.7 covers when that is and is not acceptable; for targets
/// where it is not, see the caller-supplied buffer overload in
/// flood_fill/iterative_dfs_buffered.h (Listing 3.6).
///
/// @par Failure mode
/// Returns FloodFillStatus::kWorklistFull instead of writing past the end of
/// the buffer if the input region exceeds kMaxCells.

#ifndef CH3_FLOOD_FILL_ITERATIVE_DFS_H
#define CH3_FLOOD_FILL_ITERATIVE_DFS_H

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

/// @brief Label a connected region using iterative depth-first search.
///
/// @param grid The occupancy grid to label in-place.
/// @param start_x Starting column index.
/// @param start_y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @return FloodFillStatus::kCompleted if the full region was labelled,
///         FloodFillStatus::kWorklistFull if the worklist capacity was exceeded.
FloodFillStatus floodFillIterativeDFS(OccupancyGrid& grid,
                                               std::int32_t start_x,
                                               std::int32_t start_y,
                                               std::uint8_t cluster_id);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_ITERATIVE_DFS_H
