#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

std::uint64_t find_max_pancakes(std::vector<std::uint32_t> const & stacks,
                                std::size_t const leftA,
                                std::size_t const rightA,
                                std::size_t const leftB,
                                std::size_t const rightB) {
  if (rightA < leftB) {
    std::size_t midPosition = (rightA + leftB) / 2;
    return std::accumulate(stacks.begin(), stacks.begin() + midPosition + 1, 0ull);
  }

  if (rightB < leftA) {
    std::size_t midPosition = (rightB + leftA + 1) / 2;
    return std::accumulate(stacks.begin() + midPosition, stacks.end(), 0ull);
  }

  std::vector<std::uint64_t> preSum(stacks.size());
  preSum[0] = stacks[0];
  for (std::size_t i = 1; i < stacks.size(); ++i) {
    preSum[i] = preSum[i - 1] + stacks[i];
  }

  std::uint64_t result = 0;

  for (std::size_t i = std::max(leftA, leftB); i <= std::min(rightA, rightB); ++i) {
    std::uint64_t currentResult = 0;
    if (i == leftB) {
      currentResult = preSum[i];
    } else if (i == rightB) {
      if (i == 0) {currentResult = preSum.back();}
      else {currentResult = preSum.back() - preSum[i - 1];}
    } else {
      currentResult = stacks[i];
      currentResult += std::min(preSum[i - 1], preSum.back() - preSum[i]);
    }

    result = std::max(result, currentResult);
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t nbStacks;
      std::cin >> nbStacks;

      std::vector<std::uint32_t> stacks(nbStacks);
      for (std::size_t i = 0; i < stacks.size(); ++i) {
        std::cin >> stacks[i];
      }

      std::size_t leftA;
      std::cin >> leftA;

      std::size_t rightA;
      std::cin >> rightA;

      std::size_t leftB;
      std::cin >> leftB;

      std::size_t rightB;
      std::cin >> rightB;

      std::cout << "Case #" << t + 1 << ": "
                << find_max_pancakes(stacks, leftA - 1, rightA - 1, leftB - 1,
                                     rightB - 1) << '\n';
    }
  }
}
