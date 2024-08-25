#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::uint64_t leftBrackets;
      std::cin >> leftBrackets;

      std::uint64_t rightBrackets;
      std::cin >> rightBrackets;

      std::uint64_t matchingBrackets = std::min(leftBrackets, rightBrackets);

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << matchingBrackets * (matchingBrackets + 1) / 2 << '\n';
    }
  }
}
