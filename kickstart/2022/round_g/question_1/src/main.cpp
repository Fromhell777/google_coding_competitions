#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::uint32_t find_extra_steps(std::vector<std::vector<std::uint32_t>> const & walks,
                               std::size_t const johnId) {

  std::uint32_t result = 0;

  for (std::size_t i = 0; i < walks[0].size(); ++i) {
    std::uint32_t max = 0;
    for (std::size_t j = 0; j < walks.size(); ++j) {

      if (j + 1 != johnId) {
        max = std::max(max, walks[j][i]);
      }
    }

    if (max > walks[johnId - 1][i]) {
      result += max - walks[johnId - 1][i];
    }
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t numberOfParticipants;
      std::cin >> numberOfParticipants;

      std::size_t numberOfdays;
      std::cin >> numberOfdays;

      std::size_t johnId;
      std::cin >> johnId;

      std::vector<std::vector<std::uint32_t>> walks(numberOfParticipants);

      for (std::size_t i = 0; i < numberOfParticipants; ++i) {
        for (std::size_t j = 0; j < numberOfdays; ++j) {
          std::size_t steps;
          std::cin >> steps;

          walks[i].emplace_back(steps);
        }
      }

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << find_extra_steps(walks, johnId) << "\n";
    }
  }
}
