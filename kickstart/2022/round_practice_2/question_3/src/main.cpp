#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

std::vector<std::bitset<26>> get_parities(std::string const & blocks) {
  std::vector<std::bitset<26>> result(1);

  for (auto const letter : blocks) {
    result.emplace_back(result.back());
    result.back().flip(letter - 65);
  }

  return result;
}

std::size_t answer_questions(std::size_t const numberOfQuestions,
                             std::vector<std::bitset<26>> const & parities) {
  std::size_t result = 0;

  for (std::size_t i = 0; i < numberOfQuestions; ++i) {
    std::size_t leftIndex;
    std::cin >> leftIndex;
    --leftIndex;

    std::size_t rigthIndex;
    std::cin >> rigthIndex;

    auto const sliceParities = parities[rigthIndex] ^ parities[leftIndex];

    if (sliceParities.count() <= 1) {++result;}
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t blockSize;
      std::cin >> blockSize;

      std::size_t numberOfQuestions;
      std::cin >> numberOfQuestions;

      std::string blocks;
      std::cin >> blocks;

      auto const parities = get_parities(blocks);

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << answer_questions(numberOfQuestions, parities) << '\n';
    }
  }
}
