/// @file flood_fill_iterative_bfs.h
/// @brief Solution 3: iterative BFS flood-fill with a function-local ring queue
///        (chapter 3 Listing 3.7).
///
/// Identical safety properties to Solution 2 (no recursion, no dynamic
/// allocation, explicit kWorklistFull failure mode, deterministic memory
/// footprint), but the worklist is accessed in FIFO order so the
/// traversal visits cells in increasing distance from the seed.
///
/// For pure clustering this is invisible - every connected cell gets
/// the same label either way. For related problems (shortest-path,
/// wavefront propagation, erosion/dilation) BFS gives "the nearest
/// thing" for free.
///
/// Storage placement and the per-call ~2 MB stack cost are identical
/// to flood_fill/iterative_dfs.h; see that header and section 3.6.7
/// for the trade-off. The caller-supplied buffer overload lives in
/// flood_fill/iterative_bfs_buffered.h.

#ifndef CH3_FLOOD_FILL_ITERATIVE_BFS_H
#define CH3_FLOOD_FILL_ITERATIVE_BFS_H

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

/// @brief Label a connected region using iterative breadth-first search.
///
/// @param grid The occupancy grid to label in-place.
/// @param start_x Starting column index.
/// @param start_y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @return FloodFillStatus::kCompleted if the full region was labelled,
///         FloodFillStatus::kWorklistFull if the queue capacity was exceeded.
FloodFillStatus floodFillIterativeBFS(OccupancyGrid& grid,
                                      std::int32_t start_x,
                                      std::int32_t start_y,
                                      std::uint8_t cluster_id);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_ITERATIVE_BFS_H
