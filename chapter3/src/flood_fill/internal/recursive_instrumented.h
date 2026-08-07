/// @file flood_fill/internal/recursive_instrumented.h
/// @brief Instrumented recursive flood-fill used by the stack-exhaustion demo.
///
/// Same algorithm as the public `floodFill`, plus enter/leave calls on
/// a caller-supplied DepthObserver. Bazel visibility restricts use to
/// the stack-exhaustion demo and its tests.

#ifndef CH3_FLOOD_FILL_INTERNAL_RECURSIVE_INSTRUMENTED_H
#define CH3_FLOOD_FILL_INTERNAL_RECURSIVE_INSTRUMENTED_H

#include <cstdint>

#include "flood_fill/internal/depth_observer.h"
#include "occupancy_grid.h"

namespace ch3 {

/// @brief How often the depth instrumentation prints a progress line to stderr.
constexpr int kDepthReportInterval = 1000;

/// @brief Recursive flood-fill that reports depth to a caller-owned observer.
///
/// @warning Same crash semantics as `floodFill`. Demo only.
///
/// @param grid The occupancy grid to label in-place.
/// @param x Starting column index.
/// @param y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @param obs Depth observer, passed through every recursive call.
void floodFillInstrumented(OccupancyGrid& grid,
                           int x, int y,
                           std::uint8_t cluster_id,
                           DepthObserver& obs);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_INTERNAL_RECURSIVE_INSTRUMENTED_H
