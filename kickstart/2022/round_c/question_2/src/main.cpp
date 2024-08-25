#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

void find_ratio(std::uint64_t const maxInt, std::uint64_t const ratioX,
                std::uint64_t const ratioY) {

  std::uint64_t total_sum = (maxInt * (maxInt + 1)) / 2;
  std::uint64_t candidate_sumX = ratioX;
  std::uint64_t candidate_sumY = ratioY;

  while (candidate_sumX + candidate_sumY != total_sum) {
    if (candidate_sumX > total_sum or candidate_sumY > total_sum) {
      std::cout << "IMPOSSIBLE\n";
      return;
    }
    candidate_sumX += ratioX;
    candidate_sumY += ratioY;
  }

  std::vector<std::uint64_t> result;
  std::uint64_t current_sum = 0;

  for (std::uint64_t i = maxInt; i > 0; --i) {
    if (current_sum + i <= candidate_sumX) {
      current_sum += i;
      result.emplace_back(i);
    }
  }

  if (current_sum != candidate_sumX) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  std::cout << "POSSIBLE\n";
  std::cout << result.size() << '\n';
  for (std::size_t i = 0; i < result.size(); ++i) {
    if (i > 0) {std::cout << ' ';}
    std::cout << result[i];
  }

  std::cout << '\n';
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::uint64_t maxInt;
      std::cin >> maxInt;

      std::uint64_t ratioX;
      std::cin >> ratioX;

      std::uint64_t ratioY;
      std::cin >> ratioY;

      std::cout << "Case #" << t + 1 << ": ";
      find_ratio(maxInt, ratioX, ratioY);
    }
  }
}
