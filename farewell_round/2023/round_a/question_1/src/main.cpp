#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::string find_collision(std::vector<std::uint32_t> const & mapping,
                           std::vector<std::string> const & words) {
  std::unordered_set<std::string> encoded_words;

  for (auto const & word : words) {
    std::string encoded_word;
    for (std::size_t i = 0; i < word.size(); ++i) {
      encoded_word += std::to_string(mapping[static_cast<std::uint32_t>(word[i]) - 65]);
    }

    auto const & search = encoded_words.find(encoded_word);

    if (search == encoded_words.end()) {encoded_words.emplace(encoded_word);}
    else {return "YES";}
  }

  return "NO";
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::vector<std::uint32_t> mapping(26);
      for (std::size_t i = 0; i < mapping.size(); ++i) {
        std::cin >> mapping[i];
      }

      std::size_t nbWords;
      std::cin >> nbWords;

      std::vector<std::string> words(nbWords);
      for (std::size_t i = 0; i < words.size(); ++i) {
        std::cin >> words[i];
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_collision(mapping, words) << '\n';
    }
  }
}
