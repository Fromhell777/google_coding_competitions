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
      std::size_t numberOfBags;
      std::cin >> numberOfBags;

      std::uint64_t numberOfChildren;
      std::cin >> numberOfChildren;

      std::uint64_t totalCandy = 0;

      for (std::size_t i = 0; i < numberOfBags; ++i) {
        std::uint64_t amountOfCandy;
        std::cin >> amountOfCandy;

        totalCandy += amountOfCandy;
      }

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << totalCandy % numberOfChildren << "\n";
    }
  }
}
