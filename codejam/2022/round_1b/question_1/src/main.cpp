#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::size_t find_paying_costumers(std::vector<std::uint32_t> const pancakes) {
  std::size_t result = 0;

  std::size_t start = 0;
  std::size_t end = pancakes.size() - 1;

  std::uint32_t currentDelicious = 0;

  while (start != end) {
    if (pancakes[start] < pancakes[end]) {
      if (pancakes[start] >= currentDelicious) {
        ++result;
        currentDelicious = pancakes[start];
      }
      ++start;
    } else {
      if (pancakes[end] >= currentDelicious) {
        ++result;
        currentDelicious = pancakes[end];
      }
      --end;
    }
  }

  if (pancakes[start] >= currentDelicious) {
    ++result;
    currentDelicious = pancakes[start];
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t nbPancakes;
      std::cin >> nbPancakes;

      std::vector<std::uint32_t> pancakes(nbPancakes);
      for (std::size_t i = 0; i < pancakes.size(); ++i) {
        std::cin >> pancakes[i];
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_paying_costumers(pancakes) << '\n';
    }
  }
}
