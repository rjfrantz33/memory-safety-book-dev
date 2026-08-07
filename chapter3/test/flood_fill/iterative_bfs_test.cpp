#include "flood_fill/iterative_bfs.h"

#include <gtest/gtest.h>

#include "flood_fill/iterative_dfs.h"
#include "occupancy_grid.h"
#include "types.h"

TEST(FloodFillIterativeBFS, CompletesFullGrid) {
    auto grid = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto status = ch3::floodFillIterativeBFS(grid, 0, 0, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId),
              ch3::kGridSize * ch3::kGridSize);
}

TEST(FloodFillIterativeBFS, OutOfBoundsStartReturnsCompleted) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    auto status = ch3::floodFillIterativeBFS(grid, -1, 0, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
}

TEST(FloodFillIterativeBFS, DisconnectedRegions) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    for (int y = 0; y < 5; ++y) {
        ch3::cellAt(grid, 2, y) = ch3::kCellFree;
    }
    auto status = ch3::floodFillIterativeBFS(grid, 0, 0, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 10);
    EXPECT_EQ(ch3::cellAt(grid, 3, 0), ch3::kCellOccupied);
}

// Cross-solution consistency: DFS and BFS label the same number of cells
// on the same input. Lives with the BFS test by convention - one of the
// two has to host it; choosing BFS arbitrarily.
TEST(CrossSolution, DFSAndBFSAgree) {
    auto grid_dfs = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto grid_bfs = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);

    auto s1 = ch3::floodFillIterativeDFS(grid_dfs, 0, 0, ch3::kFirstClusterId);
    auto s2 = ch3::floodFillIterativeBFS(grid_bfs, 0, 0, ch3::kFirstClusterId);

    EXPECT_EQ(s1, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(s2, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid_dfs, ch3::kFirstClusterId),
              ch3::countLabelled(grid_bfs, ch3::kFirstClusterId));
}
