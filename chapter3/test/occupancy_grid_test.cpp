#include "occupancy_grid.h"

#include <gtest/gtest.h>

#include "types.h"

TEST(OccupancyGrid, MakeFullyOccupied) {
    auto grid = ch3::makeFullyOccupiedGrid(10, 10);
    EXPECT_EQ(grid.width, 10);
    EXPECT_EQ(grid.height, 10);
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            EXPECT_EQ(ch3::cellAt(grid, x, y), ch3::kCellOccupied);
        }
    }
}

TEST(OccupancyGrid, CellAtWriteAndRead) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    ch3::cellAt(grid, 2, 3) = ch3::kFirstClusterId;
    EXPECT_EQ(ch3::cellAt(grid, 2, 3), ch3::kFirstClusterId);
    EXPECT_EQ(ch3::cellAt(grid, 0, 0), ch3::kCellOccupied);
}

TEST(OccupancyGrid, CountLabelled) {
    auto grid = ch3::makeFullyOccupiedGrid(3, 3);
    ch3::cellAt(grid, 0, 0) = ch3::kFirstClusterId;
    ch3::cellAt(grid, 1, 1) = ch3::kFirstClusterId;
    ch3::cellAt(grid, 2, 2) = ch3::kFirstClusterId;
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 3);
}
