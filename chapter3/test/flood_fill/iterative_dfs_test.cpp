#include "flood_fill/iterative_dfs.h"

#include <gtest/gtest.h>

#include "occupancy_grid.h"
#include "types.h"

TEST(FloodFillIterativeDFS, CompletesFullGrid) {
    auto grid = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto status = ch3::floodFillIterativeDFS(grid, 0, 0, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId),
              ch3::kGridSize * ch3::kGridSize);
}

TEST(FloodFillIterativeDFS, OutOfBoundsStartReturnsCompleted) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    auto status =
        ch3::floodFillIterativeDFS(grid, 10, 10, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
}

TEST(FloodFillIterativeDFS, DisconnectedRegions) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    for (int y = 0; y < 5; ++y) {
        ch3::cellAt(grid, 2, y) = ch3::kCellFree;
    }
    auto status = ch3::floodFillIterativeDFS(grid, 0, 0, ch3::kFirstClusterId);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 10);
    EXPECT_EQ(ch3::cellAt(grid, 3, 0), ch3::kCellOccupied);
}
