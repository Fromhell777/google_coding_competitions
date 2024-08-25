#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t string_size;
      std::cin >> string_size;

      std::string password;
      std::cin >> password;

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << "\n";
    }
  }
}
