// Demo driver for the instrumented recursive flood-fill (chapter 3 PART I).
//
// Two runs:
//   1. kSmallGridSize x kSmallGridSize fully-occupied grid -> finishes,
//      reports the max recursion depth reached.
//   2. kLargeGridSize x kLargeGridSize fully-occupied grid -> on a
//      default 8 MB Linux user stack at -O2, the process is killed
//      by SIGSEGV somewhere past depth 170,000.
//
// The closing std::cout in the second block does not print on a
// machine where the crash actually happens. That is the point.

#include <iostream>

#include "flood_fill/internal/depth_observer.h"
#include "flood_fill/internal/recursive_instrumented.h"
#include "occupancy_grid.h"
#include "types.h"

int main() {
    // Small run: finishes and prints its max depth.
    {
        std::cout << "Small run: " << ch3::kSmallGridSize << " x "
                  << ch3::kSmallGridSize << " fully occupied grid\n";
        ch3::OccupancyGrid small_grid = ch3::makeFullyOccupiedGrid(
            ch3::kSmallGridSize, ch3::kSmallGridSize);
        ch3::DepthObserver obs;
        ch3::floodFillInstrumented(small_grid, 0, 0, ch3::kFirstClusterId, obs);
        std::cout << "  max recursion depth reached: " << obs.max() << "\n\n";
    }

    // Large run: does not finish on a machine with a default user stack.
    {
        std::cout << "Large run: " << ch3::kLargeGridSize << " x "
                  << ch3::kLargeGridSize << " fully occupied grid\n";
        std::cout
            << "(expect a crash; watch stderr for the last depth printed)\n";
        ch3::OccupancyGrid large_grid = ch3::makeFullyOccupiedGrid(
            ch3::kLargeGridSize, ch3::kLargeGridSize);
        ch3::DepthObserver obs;
        ch3::floodFillInstrumented(large_grid, 0, 0, ch3::kFirstClusterId, obs);
        std::cout << "  max recursion depth reached: " << obs.max() << "\n";
    }

    return 0;
}
