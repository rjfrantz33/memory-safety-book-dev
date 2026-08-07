#include <gtest/gtest.h>

#include "flood_fill/iterative_dfs.h"
#include "flood_fill/iterative_dfs_buffered.h"
#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

TEST(FloodFillIterativeDFSBuffered, CompletesFullGrid) {
    auto grid = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    ch3::WorklistBuffer buffer{};
    auto status = ch3::floodFillIterativeDFS(grid, 0, 0, ch3::kFirstClusterId, buffer);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId),
              ch3::kGridSize * ch3::kGridSize);
}

TEST(FloodFillIterativeDFSBuffered, OutOfBoundsStartReturnsCompleted) {
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    ch3::WorklistBuffer buffer{};
    auto status = ch3::floodFillIterativeDFS(grid, 10, 10, ch3::kFirstClusterId, buffer);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
}

TEST(FloodFillIterativeDFSBuffered, BufferTopIsResetOnEntry) {
    // Pre-populate buffer.top with garbage; the function must reset it.
    auto grid = ch3::makeFullyOccupiedGrid(5, 5);
    ch3::WorklistBuffer buffer{};
    buffer.top = 12345;
    auto status = ch3::floodFillIterativeDFS(grid, 0, 0, ch3::kFirstClusterId, buffer);
    EXPECT_EQ(status, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid, ch3::kFirstClusterId), 25);
}

TEST(FloodFillIterativeDFSBuffered, MatchesFunctionLocalVariant) {
    auto grid_local    = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    auto grid_buffered = ch3::makeFullyOccupiedGrid(ch3::kGridSize, ch3::kGridSize);
    ch3::WorklistBuffer buffer{};

    auto s_local    = ch3::floodFillIterativeDFS(grid_local,    0, 0, ch3::kFirstClusterId);
    auto s_buffered = ch3::floodFillIterativeDFS(grid_buffered, 0, 0, ch3::kFirstClusterId, buffer);

    EXPECT_EQ(s_local,    ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(s_buffered, ch3::FloodFillStatus::kCompleted);
    EXPECT_EQ(ch3::countLabelled(grid_local,    ch3::kFirstClusterId),
              ch3::countLabelled(grid_buffered, ch3::kFirstClusterId));
}
