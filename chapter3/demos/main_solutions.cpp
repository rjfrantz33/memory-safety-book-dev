// Demo driver for the PART III solutions on a 50 x 50 grid.
//
// Each block exercises one of the chapter's listings against the same
// fully-occupied 50x50 grid. Listings 3.5 and 3.7 use a function-local
// worklist; Listing 3.6 (and its BFS counterpart in
// flood_fill/iterative_bfs_buffered.h) use a caller-supplied buffer.
//
// Expected output (verified at -O2 on a Linux x86-64 workstation):
//
//   Solution 1 (bounded recursion, limit=64) on 50x50: DepthLimitExceeded, labelled=65
//   Solution 2 (iterative DFS) on 50x50: Completed, labelled=2500
//   Solution 2b (iterative DFS, buffered) on 50x50: Completed, labelled=2500
//   Solution 3 (iterative BFS) on 50x50: Completed, labelled=2500
//   Solution 3b (iterative BFS, buffered) on 50x50: Completed, labelled=2500
//
// The Solution 1 result is the load-bearing one: 65 cells labelled
// (kMaxSafeDepth = 64 plus the entry frame) means 2,435 of the 2,500
// cells in the region were left unlabelled because the search was
// truncated. This is exactly the "partially labelled region" scenario
// the FloodFillStatus enum exists to surface to the caller. A bool
// return would have lost it. See chapter3_draft.md @$3.3.5.

#include <iostream>
#include <string_view>

#include "common/type_aliases.h"
#include "flood_fill/bounded.h"
#include "flood_fill/iterative_bfs.h"
#include "flood_fill/iterative_bfs_buffered.h"
#include "flood_fill/iterative_dfs.h"
#include "flood_fill/iterative_dfs_buffered.h"
#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

namespace {

std::string_view statusName(ch3::FloodFillStatus s) {
    switch (s) {
        case ch3::FloodFillStatus::kCompleted:           { return "Completed"; }
        case ch3::FloodFillStatus::kDepthLimitExceeded:  { return "DepthLimitExceeded"; }
        case ch3::FloodFillStatus::kWorklistFull:        { return "WorklistFull"; }
        default:                                         { return "Unknown"; }
    }
}

}  // namespace

// Function-try-block satisfies MISRA C++ 2023 Rule 18.3.1.
int main() try {
    // Solution 1: depth-bounded recursion. Expected: DepthLimitExceeded
    // because 50*50 = 2500 cells > kMaxSafeDepth.
    {
        ch3::OccupancyGrid g =
            ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
        const auto s = ch3::floodFillBounded(g, 0, 0, ch3::kFirstClusterId, 0);
        std::cout << "Solution 1 (bounded recursion, limit="
                  << static_cast<common::OstreamInt>(ch3::kMaxSafeDepth) << ") on "
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << "x"
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << ": "
                  << statusName(s)
                  << ", labelled="
                  << static_cast<common::OstreamInt>(ch3::countLabelled(g, ch3::kFirstClusterId))
                  << "\n";
    }

    // Solution 2: iterative DFS, function-local worklist (Listing 3.5).
    {
        ch3::OccupancyGrid g =
            ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
        const auto s = ch3::floodFillIterativeDFS(g, 0, 0, ch3::kFirstClusterId);
        std::cout << "Solution 2 (iterative DFS) on "
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << "x"
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << ": "
                  << statusName(s)
                  << ", labelled="
                  << static_cast<common::OstreamInt>(ch3::countLabelled(g, ch3::kFirstClusterId))
                  << "\n";
    }

    // Solution 2b: iterative DFS, caller-supplied buffer (Listing 3.6).
    // The WorklistBuffer is owned by main; only a reference is passed in.
    {
        ch3::OccupancyGrid g =
            ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
        ch3::WorklistBuffer buffer{};
        const auto s = ch3::floodFillIterativeDFS(g, 0, 0, ch3::kFirstClusterId, buffer);
        std::cout << "Solution 2b (iterative DFS, buffered) on "
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << "x"
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << ": "
                  << statusName(s)
                  << ", labelled="
                  << static_cast<common::OstreamInt>(ch3::countLabelled(g, ch3::kFirstClusterId))
                  << "\n";
    }

    // Solution 3: iterative BFS, function-local queue (Listing 3.7).
    {
        ch3::OccupancyGrid g =
            ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
        const auto s = ch3::floodFillIterativeBFS(g, 0, 0, ch3::kFirstClusterId);
        std::cout << "Solution 3 (iterative BFS) on "
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << "x"
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << ": "
                  << statusName(s)
                  << ", labelled="
                  << static_cast<common::OstreamInt>(ch3::countLabelled(g, ch3::kFirstClusterId))
                  << "\n";
    }

    // Solution 3b: iterative BFS, caller-supplied buffer.
    {
        ch3::OccupancyGrid g =
            ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
        ch3::WorklistBuffer buffer{};
        const auto s = ch3::floodFillIterativeBFS(g, 0, 0, ch3::kFirstClusterId, buffer);
        std::cout << "Solution 3b (iterative BFS, buffered) on "
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << "x"
                  << static_cast<common::OstreamInt>(ch3::kGridSize) << ": "
                  << statusName(s)
                  << ", labelled="
                  << static_cast<common::OstreamInt>(ch3::countLabelled(g, ch3::kFirstClusterId))
                  << "\n";
    }

    return 0;
} catch (...) {
    return 1;
}
