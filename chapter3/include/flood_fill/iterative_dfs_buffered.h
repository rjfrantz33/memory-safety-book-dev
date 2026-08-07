/// @file flood_fill_iterative_dfs_buffered.h
/// @brief Solution 2 evolution: iterative DFS with a caller-supplied
///        worklist buffer (chapter 3 Listing 3.6).
///
/// Same algorithm as flood_fill/iterative_dfs.h. The worklist moves
/// off the per-call stack frame into a WorklistBuffer the caller owns.
/// The function resets buffer.top on entry and uses buffer.data for
/// storage; nothing else changes.
///
/// Use this overload when more than one task may invoke the flood
/// fill, or when the per-call ~20 KB stack frame of the function-local
/// form does not fit the target stack budget.

#ifndef CH3_FLOOD_FILL_ITERATIVE_DFS_BUFFERED_H
#define CH3_FLOOD_FILL_ITERATIVE_DFS_BUFFERED_H

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

namespace ch3 {

/// @brief Iterative DFS flood-fill against a caller-supplied buffer.
///
/// @param grid The occupancy grid to label in-place.
/// @param start_x Starting column index.
/// @param start_y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @param buffer Caller-owned worklist storage. The top index is
///        reset on entry.
/// @return FloodFillStatus::kCompleted if the full region was labelled,
///         FloodFillStatus::kWorklistFull if the buffer capacity was exceeded.
FloodFillStatus floodFillIterativeDFS(OccupancyGrid& grid,
                                      std::int32_t start_x,
                                      std::int32_t start_y,
                                      std::uint8_t cluster_id,
                                      WorklistBuffer& buffer);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_ITERATIVE_DFS_BUFFERED_H
