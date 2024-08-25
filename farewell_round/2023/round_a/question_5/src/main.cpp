#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::size_t find_minimum_changes(std::string const & choices) {

  std::vector<std::size_t> repetitionLengths = {1};

  for (std::size_t i = 1; i < choices.size(); ++i) {
    if (choices[i] == choices[i - 1]) {
      ++(repetitionLengths.back());
    } else {
      repetitionLengths.emplace_back(1);
    }
  }

  if (repetitionLengths.size() == 1) {
    return (repetitionLengths[0] + 1) / 2;
  }

  if (choices.front() == choices.back()) {
    repetitionLengths.front() += repetitionLengths.back();
    repetitionLengths.erase(--(repetitionLengths.end()), repetitionLengths.end());
  }

  std::size_t result = 0;

  for (auto const repetitionLength : repetitionLengths) {
    result += repetitionLength / 2;
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::string choices;
      std::cin >> choices;

      std::cout << "Case #" << t + 1 << ": "
                << find_minimum_changes(choices) << '\n';
    }
  }
}
