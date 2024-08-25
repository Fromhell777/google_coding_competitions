#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

std::string find_spell(std::string const & spell) {
  std::string vowels = "";
  std::vector<std::size_t> vowelIndexes;

  for (std::size_t i = 0; i < spell.size(); ++i) {
    if (spell[i] == 'a' or
        spell[i] == 'e' or
        spell[i] == 'i' or
        spell[i] == 'o' or
        spell[i] == 'u') {
      vowels += spell[i];
      vowelIndexes.emplace_back(i);
    }
  }

  for (std::size_t i = 0; i + 4 < vowels.size(); ++i) {
    std::string const firstWord = spell.substr(vowelIndexes[i],
                                               vowelIndexes[i + 1] - vowelIndexes[i] + 1);

    auto const pos = spell.rfind(firstWord);

    if (pos > vowelIndexes[i + 2]) {
      return "Spell!";
    }

  }

  return "Nothing.";
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::string spell;
      std::cin >> spell;

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << find_spell(spell) << '\n';
    }
  }
}
