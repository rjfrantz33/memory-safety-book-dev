#include "flood_fill/iterative_bfs_buffered.h"

#include <gtest/gtest.h>

#include "flood_fill/iterative_bfs.h"
#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

TEST(FloodFillIterativeBFSBuffered, CompletesFullGrid) {
    auto grid = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    ch3::WorklistBuffer buffer{};
    auto status =
        ch3::floodFillIterativeBFS(grid, 0, 0, ch3::kFirstClusterId, buffer);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId),
              ch3::kGridSize * ch3::kGridSize);
}

TEST(FloodFillIterativeBFSBuffered, OutOfBoundsStartReturnsCompleted) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    ch3::WorklistBuffer buffer{};
    auto status =
        ch3::floodFillIterativeBFS(grid, -1, 0, ch3::kFirstClusterId, buffer);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
}

TEST(FloodFillIterativeBFSBuffered, MatchesFunctionLocalVariant) {
    auto grid_local =
        ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto grid_buffered =
        ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    ch3::WorklistBuffer buffer{};

    auto s_local =
        ch3::floodFillIterativeBFS(grid_local, 0, 0, ch3::kFirstClusterId);
    auto s_buffered = ch3::floodFillIterativeBFS(
        grid_buffered, 0, 0, ch3::kFirstClusterId, buffer);

    EXPECT_EQ(s_local, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(s_buffered, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid_local, ch3::kFirstClusterId),
              ch3::countLabelled(grid_buffered, ch3::kFirstClusterId));
}
