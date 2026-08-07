/// @file flood_fill_iterative_bfs_buffered.h
/// @brief Solution 3 evolution: iterative BFS with a caller-supplied
///        worklist buffer.
///
/// Symmetric to flood_fill/iterative_dfs_buffered.h. The traversal
/// uses FIFO ordering over the same caller-supplied WorklistBuffer.
/// The data array is used as a queue indexed by a head/tail pair;
/// buffer.top serves as the tail, and a function-local head index
/// advances on each dequeue.
///
/// Use this overload when more than one task may invoke the flood
/// fill, or when the per-call ~20 KB stack frame of the function-local
/// form does not fit the target stack budget.

#ifndef CH3_FLOOD_FILL_ITERATIVE_BFS_BUFFERED_H
#define CH3_FLOOD_FILL_ITERATIVE_BFS_BUFFERED_H

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

namespace ch3 {

/// @brief Iterative BFS flood-fill against a caller-supplied buffer.
///
/// @param grid The occupancy grid to label in-place.
/// @param start_x Starting column index.
/// @param start_y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @param buffer Caller-owned worklist storage. Used as a head/tail
///        queue; the top index is reset on entry.
/// @return FloodFillStatus::kCompleted if the full region was labelled,
///         FloodFillStatus::kWorklistFull if the buffer capacity was exceeded.
FloodFillStatus floodFillIterativeBFS(OccupancyGrid& grid,
                                                    std::int32_t start_x,
                                                    std::int32_t start_y,
                                                    std::uint8_t cluster_id,
                                                    WorklistBuffer& buffer);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_ITERATIVE_BFS_BUFFERED_H
