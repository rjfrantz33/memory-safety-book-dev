#include "flood_fill/recursive.h"

#include <gtest/gtest.h>

#include "flood_fill/internal/depth_observer.h"
#include "flood_fill/internal/recursive_instrumented.h"
#include "occupancy_grid.h"
#include "types.h"

TEST(FloodFillRecursive, SmallGridCompletes) {
    auto grid =
        ch3::makeFullyOccupiedGrid(ch3::kSmallGridSize, ch3::kSmallGridSize);
    ch3::floodFill(grid, 0, 0, ch3::kFirstClusterId);

    const int expected = ch3::kSmallGridSize * ch3::kSmallGridSize;
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), expected);
}

TEST(FloodFillRecursive, FreeCellsUntouched) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    ch3::cellAt(grid, 2, 0) = ch3::kCellFree;  // cut the grid in two
    ch3::cellAt(grid, 2, 1) = ch3::kCellFree;
    ch3::cellAt(grid, 2, 2) = ch3::kCellFree;
    ch3::cellAt(grid, 2, 3) = ch3::kCellFree;
    ch3::cellAt(grid, 2, 4) = ch3::kCellFree;

    ch3::floodFill(grid, 0, 0, ch3::kFirstClusterId);

    // Only the left 2-column region (2*5 = 10 cells) should be labelled.
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 10);
    // Right side should remain occupied.
    EXPECT_EQ(ch3::cellAt(grid, 3, 0), ch3::kCellOccupied);
}

TEST(FloodFillInstrumented, ObserverTracksDepth) {
    auto grid = ch3::makeFullyOccupiedGrid(3, 3);
    ch3::DepthObserver obs;
    ch3::floodFillInstrumented(grid, 0, 0, ch3::kFirstClusterId, obs);

    // After return the observer's current() must be back at zero
    // (every enter() was matched by a leave()).
    EXPECT_EQ(obs.current(), 0);
    // The 3x3 grid forces some recursion - max depth must be > 1.
    EXPECT_GT(obs.max(), 1);
}
