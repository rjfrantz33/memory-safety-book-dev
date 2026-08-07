/// @file flood_fill_bounded.h
/// @brief Solution 1: depth-bounded recursive flood-fill (chapter 3 @$3.3.1).
///
/// Same algorithm as the original recursive flood-fill, with three changes
/// that turn it from "crashes on big inputs" into "fails loudly on big inputs":
///
///   1. The function takes an explicit @p depth parameter and returns
///      kDepthLimitExceeded the moment depth > kMaxSafeDepth.
///   2. The return type is a two-state enum, not bool/void. The chapter
///      argues that the distinction between "completed" and "ran out of
///      resources partway through" cannot be a single bit.
///   3. kMaxSafeDepth is derived from a target stack budget, not picked
///      arbitrarily. The derivation lives beside the constant below, where
///      a reviewer can audit it.
///
/// @note This solution still recurses, so it still violates MISRA C++
///       2023 Rule 7.5.2 / AUTOSAR C++14 Rule A7-5-2 in letter. It can
///       be shipped only with a formal rule deviation that points at the
///       kMaxSafeDepth derivation as the safety case.

#ifndef CH3_FLOOD_FILL_BOUNDED_H
#define CH3_FLOOD_FILL_BOUNDED_H

#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

/// @brief Maximum safe recursion depth.
///
///   Target: 4 KB per-task stack on a representative automotive RTOS task.
///   Measured per-frame cost of floodFillBounded at -O2: 48 bytes.
///           Reproducible via `g++ -fstack-usage` on bounded.cpp.
///   Arithmetic ceiling: 4096 / 48 = 85 frames if nothing else is
///           on the stack.
///   Margin reserved (25%): 1024 bytes for ISR frames, RTOS housekeeping,
///           the caller of floodFillBounded, and a buffer for compiler
///           changes that might widen the per-frame cost.
///   Chosen value: 64. Derived from (4096 - 1024) / 48 = 64.
///
/// If you change the target stack size, the optimization level, or the
/// compiler version, redo this derivation. Do not bump the constant
/// without redoing it.
inline constexpr std::int32_t kMaxSafeDepth = 64;

/// @brief Recursively label a connected region with a depth bound.
///
/// @param grid The occupancy grid to label in-place.
/// @param x Starting column index.
/// @param y Starting row index.
/// @param cluster_id Label to stamp onto each visited occupied cell.
/// @param depth Current recursion depth (pass 0 at the top-level call).
/// @return FloodFillStatus::kCompleted if the full region was labelled,
///         FloodFillStatus::kDepthLimitExceeded if the depth bound was hit.
FloodFillStatus floodFillBounded(OccupancyGrid& grid,
                                               std::int32_t x, std::int32_t y,
                                               std::uint8_t cluster_id,
                                               std::int32_t depth);

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_BOUNDED_H
