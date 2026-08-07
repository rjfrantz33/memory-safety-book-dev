/// @file occupancy_grid.h
/// @brief OccupancyGrid data structure and helpers for the flood-fill examples.
///
/// Row-major flat storage. Each cell holds either kCellFree, kCellOccupied,
/// or a cluster id (>= kFirstClusterId) once it has been labelled.
///
/// The recursive demo (PART I) uses std::vector for storage; the iterative
/// solutions (PART III) operate on the same struct so the comparison is
/// apples-to-apples. The choice of std::vector here is deliberate - the
/// chapter is about stack safety, not about heap allocation.

#ifndef CH3_OCCUPANCY_GRID_H
#define CH3_OCCUPANCY_GRID_H

#include <cstdint>
#include <vector>

namespace ch3 {

/// @brief 2D occupancy grid stored as a flat row-major vector.
///
/// All flood-fill variants operate on this struct. Fields are public
/// because OccupancyGrid is a POD aggregate by design.
struct OccupancyGrid {
    std::int32_t width;               ///< Number of columns.
    std::int32_t height;              ///< Number of rows.
    std::vector<std::uint8_t> cells;  ///< Flat row-major cell storage (width_ * height_ elements).
};

/// @brief Mutable element accessor using row-major indexing.
///
/// Computes cells_[x * height_ + y]. The index arithmetic widens to
/// std::size_t before the multiply to avoid bugprone-misplaced-widening-cast.
///
/// @param grid The grid to access.
/// @param x Column index.
/// @param y Row index.
/// @return Reference to the cell at (x, y).
std::uint8_t& cellAt(OccupancyGrid& grid, std::int32_t x, std::int32_t y);

/// @brief Const element accessor using row-major indexing.
///
/// @param grid The grid to read from.
/// @param x Column index.
/// @param y Row index.
/// @return Value of the cell at (x, y).
std::uint8_t cellAt(const OccupancyGrid& grid, std::int32_t x, std::int32_t y);

/// @brief Construct a fully-occupied grid of the requested dimensions.
///
/// Every cell is initialised to kCellOccupied. The fully-occupied case is
/// the worst case for flood-fill and is what the chapter's demos exercise.
///
/// @param width Number of columns.
/// @param height Number of rows.
/// @return A new OccupancyGrid with all cells set to kCellOccupied.
OccupancyGrid makeFullyOccupiedGrid(std::int32_t width, std::int32_t height);

/// @brief Count cells holding a given cluster id.
///
/// Used by the demo drivers to verify how much of a region was labelled.
///
/// @param grid The grid to scan.
/// @param cluster_id The cluster label to count.
/// @return Number of cells whose value equals cluster_id.
std::int32_t countLabelled(const OccupancyGrid& grid, std::uint8_t cluster_id);

}  // namespace ch3

#endif  // CH3_OCCUPANCY_GRID_H
