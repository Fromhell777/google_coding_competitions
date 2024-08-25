#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

std::size_t find_longest_straight(std::vector<std::uint32_t> & sides) {
  std::sort(sides.begin(), sides.end());

  std::size_t result = 0;
  for (std::uint32_t i = 0; i < sides.size(); i++) {
    if (sides[i] > result) {result += 1;}
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::uint32_t testCases;
    std::cin >> testCases;

    for (std::uint32_t t = 0; t < testCases; t++) {
      std::uint32_t nbDice;
      std::cin >> nbDice;

      std::vector<std::uint32_t> sides(nbDice);
      for (std::uint32_t j = 0; j < sides.size(); j++) {
        std::cin >> sides[j];
      }

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << find_longest_straight(sides) << '\n';
    }
  }
}
