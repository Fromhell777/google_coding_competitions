#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::uint64_t find_smaller_palindromes(std::string const & word,
                                       std::size_t number_of_letters)
{
  std::uint64_t result = 0;

  std::vector<std::uint64_t> possible_palindromes((word.size() + 1) / 2 - 1,
                                                  number_of_letters);

  for (std::size_t i = 1; i < possible_palindromes.size(); ++i)
    {
      possible_palindromes[i] = (possible_palindromes[i - 1] * number_of_letters) % 1'000'000'007ull;
    }

  for (std::size_t i = 0; i < (word.size() + 1) / 2; ++i)
    {
      std::uint64_t extra_palindromes = word[i] - 97;

      if ((word.size() + 1) / 2 - i - 1 != 0)
        {
          extra_palindromes =
            (extra_palindromes * possible_palindromes[(word.size() + 1) / 2 - i - 2]) % 1'000'000'007ull;
        }

      result = (result + extra_palindromes) % 1'000'000'007ull;
    }

  bool one_extra_palindrome = false;

  for (std::int32_t i = (word.size() / 2) - 1; i >= 0; --i)
    {
      if (word[i] < word[word.size() - i - 1])
        {
          one_extra_palindrome = true;
          break;
        }
      else if (word[i] > word[word.size() - i - 1]) {break;}
    }

  if (one_extra_palindrome)
    {
      result = (result + 1) % 1'000'000'007ull;
    }

  return result;
}


int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t string_size;
        std::cin >> string_size;

        std::size_t number_of_letters;
        std::cin >> number_of_letters;

        std::string word;
        std::cin >> word;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_smaller_palindromes(word, number_of_letters) << "\n";
      }
  }
}
