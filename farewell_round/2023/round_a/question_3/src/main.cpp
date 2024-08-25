#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

std::string find_color_order(std::vector<std::uint32_t> & colors) {

  std::unordered_set<std::uint32_t> seenColors;

  for (std::size_t i = 0; i < colors.size(); ++i) {
    auto const & search = seenColors.find(colors[i]);

    if (search == seenColors.end()) {
      seenColors.emplace(colors[i]);
    } else if (colors[i] != colors[i - 1]) {
      return "IMPOSSIBLE";
    }
  }

  colors.erase(std::unique(colors.begin(), colors.end()), colors.end());

  std::string result = "";

  for (std::size_t i = 0; i < colors.size(); ++i) {
    if (i != 0) {result += ' ';}
    result += std::to_string(colors[i]);
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t nbCards;
      std::cin >> nbCards;

      std::vector<std::uint32_t> colors(nbCards);
      for (std::size_t i = 0; i < colors.size(); ++i) {
        std::cin >> colors[i];
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_color_order(colors) << '\n';
    }
  }
}
