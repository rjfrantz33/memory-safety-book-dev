// Listing 2.5: combining spatial and temporal checks.
//
// Every memory access has to get two things right: reach the correct
// location, and find the object at that location still alive. Get either
// wrong and the behaviour is undefined, so readSensor checks both before it
// touches an element and returns std::optional<int> so the caller can
// recover instead of reading through a freed or out-of-range address.
//
// Neither check alone is sufficient. Without the spatial check a live buffer
// could be read out of bounds; without the temporal check a freed buffer
// could be read at any index.
//
// The book listing ends at the class. main() below drives it so the demo is
// runnable, and exercises all three paths: in range, out of range, freed.

#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>

class SensorBuffer {
 public:
  void activate(std::size_t size) {
    buffer_ = std::make_unique<int[]>(size);
    size_ = size;
    for (std::size_t i = 0; i < size; ++i) {
      buffer_[i] = static_cast<int>(i * 10);
    }
  }

  void deactivate() {
    buffer_.reset();
    size_ = 0;
  }

  std::optional<int> readSensor(std::size_t index) {
    if (!buffer_) {
      return std::nullopt;  // Temporal check: freed or never allocated.
    }
    if (index >= size_) {
      return std::nullopt;  // Spatial check: index outside the buffer.
    }
    return buffer_[index];
  }

 private:
  std::unique_ptr<int[]> buffer_;
  std::size_t size_ = 0;
};

namespace {

void report(const char* label, std::optional<int> reading) {
  std::cout << label << ": ";
  if (reading.has_value()) {
    std::cout << *reading << "\n";
  } else {
    std::cout << "no reading\n";
  }
}

}  // namespace

int main() {
  SensorBuffer sensors;
  sensors.activate(8);

  report("index 3, buffer live ", sensors.readSensor(3));
  report("index 99, buffer live", sensors.readSensor(99));

  sensors.deactivate();
  report("index 3, buffer freed", sensors.readSensor(3));
  return 0;
}
