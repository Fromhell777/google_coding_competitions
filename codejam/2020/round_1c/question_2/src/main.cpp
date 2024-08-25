#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>

std::pair<std::uint32_t, char> flip_pair(std::pair<char, std::uint32_t> const & p)
{
    return std::pair<std::uint32_t, char>(p.second, p.first);
}

std::string find_digit_string(std::vector<std::string> const & responses)
{
  std::map<char, std::uint32_t> frequencies;

  // Find 1-9
  for (auto const & response : responses)
    {
      ++frequencies[response[0]];
    }

  std::multimap<std::uint32_t, char, std::greater<std::uint32_t>> sorted_on_value;
  std::transform(frequencies.begin(), frequencies.end(),
                 std::inserter(sorted_on_value, sorted_on_value.begin()),
                 flip_pair);

  std::string digit_string = "";

  for (auto const & frequency : sorted_on_value)
    {
      digit_string += frequency.second;
    }

  // Find 0
  for (auto const & response : responses)
    {
      bool found = false;

      for (auto const character : response)
        {
          std::string::size_type n;
          n = digit_string.find(character);

          if (n == std::string::npos)
            {
              digit_string = character + digit_string;
              found = true;
              break;
            }
        }

      if (found) {break;}
    }

  return digit_string;
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t upper_bound_digits;
        std::cin >> upper_bound_digits;

        std::vector<std::string> responses;

        for (std::size_t i = 0; i < 10000; ++i)
          {
            std::int64_t querry_number;
            std::cin >> querry_number;

            std::string response;
            std::cin >> response;

            responses.emplace_back(response);
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_digit_string(responses) << "\n";
      }
  }
}
