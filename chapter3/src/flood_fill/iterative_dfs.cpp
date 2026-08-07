#include "flood_fill/iterative_dfs.h"

#include <array>
#include <cstddef>
#include <cstdint>

#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

FloodFillStatus floodFillIterativeDFS(OccupancyGrid& grid,
                                 std::int32_t start_x,
                                 std::int32_t start_y,
                                 std::uint8_t cluster_id) {

    std::array<Coordinate, kMaxCells> worklist {};
    std::size_t worklist_top {};


    if (((start_x < 0) || (start_x >= grid.width)) ||
        ((start_y < 0) || (start_y >= grid.height))) {
        return FloodFillStatus::kCompleted;
    }
    if (cellAt(grid, start_x, start_y) != kCellOccupied) {
        return FloodFillStatus::kCompleted;
    }

    worklist[worklist_top++] = Coordinate{start_x, start_y};
    cellAt(grid, start_x, start_y) = cluster_id;

    while (worklist_top > 0) {
        const Coordinate c = worklist[--worklist_top];  // pop -> DFS order
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
            if (worklist_top >= worklist.size()) {
                return FloodFillStatus::kWorklistFull;
            }
            cellAt(grid, nx, ny) = cluster_id;          // mark on push
            worklist[worklist_top++] = Coordinate{nx, ny};
        }
    }
    return FloodFillStatus::kCompleted;
}

}  // namespace ch3
