#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>

char find_letter(std::uint64_t const position) {

  long double iteration = (std::sqrt(1ull + 8ull * (position - 1) / 26) - 1) / 2;
  std::uint64_t iterationTruncated = static_cast<std::uint64_t>(iteration);

  std::uint64_t startSequence = 13 * iterationTruncated * (iterationTruncated + 1);

  std::uint64_t letter = ((position - 1) - startSequence) /
                         (iterationTruncated + 1);

  return static_cast<char>(letter + 65);
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::uint64_t position;
      std::cin >> position;

      std::cout << "Case #" << t + 1 << ": "
                << find_letter(position) << '\n';
    }
  }
}
