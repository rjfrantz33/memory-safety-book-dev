/// @file worklist_buffer.h
/// @brief Caller-owned worklist storage for the iterative flood-fill
///        variants (chapter 3 Listing 3.6).
///
/// Holds the worklist array and the top index. The buffered overloads
/// take one of these by reference and reset the top on entry. Where
/// the WorklistBuffer instance lives is the caller's call: file-scope
/// .bss, task-stack, or heap. Same recursion-elimination and
/// capacity-bound properties as the function-local form in Listing
/// 3.5; the per-call frame drops from ~20 KB to one reference, and
/// the function is reentrant.

#ifndef CH3_WORKLIST_BUFFER_H
#define CH3_WORKLIST_BUFFER_H

#include <array>
#include <cstddef>

#include "types.h"

namespace ch3 {

/// @brief Caller-owned worklist storage used by the buffered iterative
///        flood-fill overloads.
struct WorklistBuffer {
    std::array<Coordinate, kMaxCells> data;  ///< Underlying storage for cells to visit.
    std::size_t top;                          ///< Index of the next free slot.
};

}  // namespace ch3

#endif  // CH3_WORKLIST_BUFFER_H
