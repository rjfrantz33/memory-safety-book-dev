#include "flood_fill/bounded.h"

#include <gtest/gtest.h>

#include "occupancy_grid.h"
#include "types.h"

TEST(FloodFillBounded, SmallGridCompletes) {
    // 3x3 = 9 cells, well within kMaxSafeDepth (64).
    auto grid = ch3::makeFullyOccupiedGrid(3, 3);
    auto status = ch3::floodFillBounded(grid, 0, 0, ch3::kFirstClusterId, 0);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 9);
}

TEST(FloodFillBounded, ExceedsDepthLimit) {
    // 50x50 = 2500 cells > kMaxSafeDepth (64). Must report truncation.
    auto grid = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto status = ch3::floodFillBounded(grid, 0, 0, ch3::kFirstClusterId, 0);
    EXPECT_EQ(status, ch3::FloodFillStatus::kDepthLimitExceeded);

    const int labelled = ch3::countLabelled(grid, ch3::kFirstClusterId);
    EXPECT_GT(labelled, 0);
    EXPECT_LT(labelled, ch3::kGridSize * ch3::kGridSize);
}

TEST(FloodFillBounded, OutOfBoundsStartReturnsCompleted) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    auto status = ch3::floodFillBounded(grid, -1, 0, ch3::kFirstClusterId, 0);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
}
