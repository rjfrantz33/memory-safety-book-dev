#include "flood_fill/iterative_bfs_buffered.h"

#include <array>
#include <cstddef>
#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"
#include "worklist_buffer.h"

namespace ch3 {

FloodFillStatus floodFillIterativeBFS(OccupancyGrid& grid,
                                      std::int32_t start_x,
                                      std::int32_t start_y,
                                      std::uint8_t cluster_id,
                                      WorklistBuffer& buffer) {
    // buffer.top is reused as the tail index for the FIFO queue.
    // The head is a function-local index since it is single-use per call.
    buffer.top = 0;
    std::size_t head = 0;

    if (((start_x < 0) || (start_x >= grid.width)) ||
        ((start_y < 0) || (start_y >= grid.height))) {
        return FloodFillStatus::kCompleted;
    }
    if (cellAt(grid, start_x, start_y) != kCellOccupied) {
        return FloodFillStatus::kCompleted;
    }

    buffer.data[buffer.top++] = Coordinate{start_x, start_y};
    cellAt(grid, start_x, start_y) = cluster_id;

    while (head < buffer.top) {
        const Coordinate c = buffer.data[head++];  // dequeue -> BFS order
        constexpr std::array<std::int32_t, 4> kDxs = {kNeighbourStep, -kNeighbourStep, 0, 0};
        constexpr std::array<std::int32_t, 4> kDys = {0, 0, kNeighbourStep, -kNeighbourStep};
        for (std::size_t i = 0; i < kDxs.size(); ++i) {
            const std::int32_t nx = c.x + kDxs[i];
            const std::int32_t ny = c.y + kDys[i];
            if (((nx < 0) || (nx >= grid.width)) || ((ny < 0) || (ny >= grid.height))) {
                continue;
            }
            if (cellAt(grid, nx, ny) != kCellOccupied) {
                continue;
            }
            if (buffer.top >= buffer.data.size()) {
                return FloodFillStatus::kWorklistFull;
            }
            cellAt(grid, nx, ny) = cluster_id;
            buffer.data[buffer.top++] = Coordinate{nx, ny};
        }
    }
    return FloodFillStatus::kCompleted;
}

}  // namespace ch3
