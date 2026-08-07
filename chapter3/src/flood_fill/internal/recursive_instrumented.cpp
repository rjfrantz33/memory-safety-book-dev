#include "flood_fill/internal/recursive_instrumented.h"

#include <cstdint>
#include <iostream>

#include "flood_fill/internal/depth_observer.h"
#include "occupancy_grid.h"
#include "types.h"

namespace ch3 {

// Same algorithm as the public floodFill. Adds enter/leave on the
// observer at each frame, and an occasional stderr breadcrumb on each
// new max depth so the demo prints something while the recursion
// grows.
//
// Recursion is still the chapter's counter-example; misc-no-recursion
// suppression stays.
// NOLINTNEXTLINE(misc-no-recursion)
void floodFillInstrumented(OccupancyGrid& grid,
                           int x, int y,
                           std::uint8_t cluster_id,
                           DepthObserver& obs) {
    const int prev_max = obs.max();
    obs.enter();
    const int new_max = obs.max();

    if (new_max > prev_max &&
        new_max % kDepthReportInterval == 0) {
        std::cerr << "[depth " << new_max << "]\n";
    }

    if (x < 0 || x >= grid.width || y < 0 || y >= grid.height) {
        obs.leave();
        return;
    }
    if (cellAt(grid, x, y) != kCellOccupied) {
        obs.leave();
        return;
    }

    cellAt(grid, x, y) = cluster_id;

    floodFillInstrumented(grid, x + 1, y, cluster_id, obs);
    floodFillInstrumented(grid, x - 1, y, cluster_id, obs);
    floodFillInstrumented(grid, x, y + 1, cluster_id, obs);
    floodFillInstrumented(grid, x, y - 1, cluster_id, obs);

    obs.leave();
}

}  // namespace ch3
