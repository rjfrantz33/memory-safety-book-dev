// Demo driver for the original recursive flood-fill (defective).
//
// Two runs:
//   1. kSmallGridSize x kSmallGridSize fully-occupied grid -> finishes
//   silently.
//   2. kLargeGridSize x kLargeGridSize fully-occupied grid -> on a default
//      8 MB Linux user stack at -O2, the process is killed by SIGSEGV.
//
// The second std::cout in the large-run block does not print on a
// machine where the crash actually happens. That is the point - the
// mystery of *why* the process died is what PART II investigates.

#include <iostream>

#include "flood_fill/recursive.h"
#include "occupancy_grid.h"
#include "types.h"

int main() {
    {
        std::cout << "Small run: " << ch3::kSmallGridSize << " x "
                  << ch3::kSmallGridSize << " fully occupied grid\n";
        ch3::OccupancyGrid small_grid = ch3::makeFullyOccupiedGrid(
            ch3::kSmallGridSize, ch3::kSmallGridSize);
        ch3::floodFill(small_grid, 0, 0, ch3::kFirstClusterId);
        std::cout << "  completed successfully\n\n";
    }

    {
        std::cout << "Large run: " << ch3::kLargeGridSize << " x "
                  << ch3::kLargeGridSize << " fully occupied grid\n"
                  << std::flush;
        ch3::OccupancyGrid large_grid = ch3::makeFullyOccupiedGrid(
            ch3::kLargeGridSize, ch3::kLargeGridSize);
        ch3::floodFill(large_grid, 0, 0, ch3::kFirstClusterId);
        std::cout << "  completed successfully\n";
    }

    return 0;
}
