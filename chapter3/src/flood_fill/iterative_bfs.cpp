#include "flood_fill/iterative_bfs.h"

#include <array>
#include <cstddef>
#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

FloodFillStatus floodFillIterativeBFS(OccupancyGrid& grid,
                                 std::int32_t start_x,
                                 std::int32_t start_y,
                                 std::uint8_t cluster_id) {

    std::array<Coordinate, kMaxCells> queue {};
    std::size_t head {};
    std::size_t tail {};

    if (((start_x < 0) || (start_x >= grid.width)) ||
        ((start_y < 0) || (start_y >= grid.height))) {
        return FloodFillStatus::kCompleted;
    }
    if (cellAt(grid, start_x, start_y) != kCellOccupied) {
        return FloodFillStatus::kCompleted;
    }

    queue[tail++] = Coordinate{start_x, start_y};
    cellAt(grid, start_x, start_y) = cluster_id;

    while (head < tail) {
        const Coordinate c = queue[head++];   // dequeue -> BFS order
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
            if (tail >= queue.size()) {
                return FloodFillStatus::kWorklistFull;
            }
            cellAt(grid, nx, ny) = cluster_id;
            queue[tail++] = Coordinate{nx, ny};
        }
    }
    return FloodFillStatus::kCompleted;
}

}  // namespace ch3
