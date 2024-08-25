#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

std::string calculate_paint_units(std::vector<std::vector<std::uint32_t>> const & printers) {
  std::uint32_t neededPaintUints = 1'000'000;
  std::vector<std::uint32_t> minPaintUints;

  for (std::uint32_t i = 0; i < printers[0].size(); i++) {
    auto minUnitsIt = std::min_element(printers.begin(), printers.end(),
      [&](auto const & lhs, auto const & rhs) {return lhs[i] < rhs[i];});

    minPaintUints.push_back((*minUnitsIt)[i]);
  }

  if (std::accumulate(minPaintUints.begin(), minPaintUints.end(), 0ull) < neededPaintUints) {
    return " IMPOSSIBLE";
  }

  std::uint32_t UsedPaintUints = 0;
  std::string result = "";

  for (auto const minPaintUint : minPaintUints) {
    result += ' ';
    if (UsedPaintUints + minPaintUint <= neededPaintUints) {
      result += std::to_string(minPaintUint);
      UsedPaintUints += minPaintUint;
    } else {
      result += std::to_string(neededPaintUints - UsedPaintUints);
      UsedPaintUints = neededPaintUints;
    }
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::uint32_t testCases;
    std::cin >> testCases;

    for (std::uint32_t t = 0; t < testCases; t++) {
      std::vector<std::vector<std::uint32_t>> printers(3, std::vector<std::uint32_t>(4));

      for (std::uint32_t j = 0; j < printers.size(); j++) {
        for (std::uint32_t k = 0; k < printers[0].size(); k++) {
          std::cin >> printers[j][k];
        }
      }

      std::cout << "Case #" << t + 1 << ':';
      std::cout << calculate_paint_units(printers) << '\n';
    }
  }
}
