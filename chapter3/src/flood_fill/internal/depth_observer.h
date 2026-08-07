/// @file flood_fill/internal/depth_observer.h
/// @brief Depth-tracking observer used by floodFillInstrumented.
///
/// Caller-owned state. Replaces the namespace-scope counters the
/// original instrumented flood-fill used.
///
/// Internal to chapter3/src/flood_fill.

#ifndef CH3_FLOOD_FILL_INTERNAL_DEPTH_OBSERVER_H
#define CH3_FLOOD_FILL_INTERNAL_DEPTH_OBSERVER_H

namespace ch3 {

/// @brief Tracks current and maximum recursion depth observed so far.
///
/// The instrumented flood-fill calls enter() before each recursive
/// descent and leave() before returning. After the top-level call
/// returns (or is observed externally after a crash), max() reports
/// the high-water mark.
class DepthObserver {
   public:
    /// @brief Increment current depth and update max if exceeded.
    void enter() {
        ++current_;
        if (current_ > max_) {
            max_ = current_;
        }
    }

    /// @brief Decrement current depth.
    void leave() { --current_; }

    /// @brief Current recursion depth.
    [[nodiscard]] int current() const { return current_; }

    /// @brief Maximum recursion depth observed since construction or last reset.
    [[nodiscard]] int max() const { return max_; }

    /// @brief Reset both counters to zero.
    void reset() {
        current_ = 0;
        max_ = 0;
    }

   private:
    int current_ = 0;
    int max_ = 0;
};

}  // namespace ch3

#endif  // CH3_FLOOD_FILL_INTERNAL_DEPTH_OBSERVER_H
