#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  std::uint64_t result;

  {
    timer Timer;

  }

  std::cout << "Result: " << result << '\n';
}
