/// @file types.h
/// @brief Shared compile-time constants and value types for the chapter 3 flood-fill examples.
///
/// This header has no .cpp counterpart on purpose: every entity is either
/// a constexpr or a trivial value type with no out-of-line definitions,
/// so there is nothing to compile separately.

#ifndef CH3_TYPES_H
#define CH3_TYPES_H

#include <cstdint>

namespace ch3 {

/// @name Cell-state encoding
/// @brief Constants encoding the state of each cell in the occupancy grid.
///
/// A cell is either free, occupied, or has been stamped with a cluster id.
/// Cluster ids start at kFirstClusterId and count up.
/// @{
constexpr std::uint8_t kCellFree = 0;  ///< Cell is unoccupied.
constexpr std::uint8_t kCellOccupied =
    1;  ///< Cell is occupied but not yet labelled.
constexpr std::uint8_t kFirstClusterId = 2;  ///< First valid cluster label.
/// @}

/// @name Grid sizing for demo runs
/// @{

/// @brief Side length of the small demo grid.
///
/// Small enough that every flood-fill variant finishes on every machine.
constexpr std::int32_t kSmallGridSize = 50;

/// @brief Side length of the large demo grid.
///
/// Large enough that the recursive variant exhausts an 8 MB Linux user
/// stack at -O2. See chapter3_draft.md @$3.2.1 for the arithmetic
/// (8 MB / 48 B per frame ~= 174,762, and 500*500 = 250,000).
constexpr std::int32_t kLargeGridSize = 500;

/// @brief Dimension the iterative solutions size their worklist against.
///
/// The worklist must hold at most one entry per cell, so the tight
/// worst-case bound is kMaxCells = kGridSize * kGridSize.
constexpr std::int32_t kGridSize = 50;

/// @brief Maximum number of cells in the worklist (kGridSize^2).
constexpr std::int32_t kMaxCells = kGridSize * kGridSize;

/// @brief Typed one-cell neighbour offset (MISRA C++ 2023 Rule 7.0.6).
constexpr std::int32_t kNeighbourStep = 1;
/// @}

/// @brief 2D coordinate pair used by the iterative worklists.
///
/// Plain old data - no constructors, no invariants - so it can sit in a
/// std::array<Coordinate, N> with zero overhead.
struct Coordinate {
    std::int32_t x;  ///< Column index.
    std::int32_t y;  ///< Row index.
};

/// @brief Return type shared by every flood-fill variant in chapter 3.
///
/// Distinguishes "the cluster was fully labelled" from the two partial
/// outcomes the recursive and iterative solutions can produce. A bool
/// would conflate them; see chapter3_draft.md @$3.3.1 for why that
/// conflation is the silent-failure bug the enum exists to prevent.
///
/// Explicit underlying type: 1 byte is enough for three states, and
/// the chapter is about safety-critical embedded code where every byte
/// of a status return is a deliberate decision.
enum class FloodFillStatus : std::uint8_t {
    kCompleted,           ///< The connected region was fully labelled.
    kDepthLimitExceeded,  ///< Recursion hit kMaxSafeDepth; region partially
                          ///< labelled.
    kWorklistFull,  ///< Worklist capacity exceeded; region partially labelled.
};

}  // namespace ch3

#endif  // CH3_TYPES_H
