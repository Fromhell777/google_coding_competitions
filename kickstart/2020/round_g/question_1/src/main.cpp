#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::uint32_t find_lucky_fragments(std::string const & text)
{
  std::vector<std::size_t> start_match_positions;

  for (std::size_t i = 0; i < text.size(); ++i)
    {
      if (text.substr(i, 5) == "START")
        {
          start_match_positions.emplace_back(i);
        }
    }

  std::uint32_t result = 0;

  for (std::size_t i = 0; i < text.size(); ++i)
    {
      if (text.substr(i, 4) == "KICK")
        {
          result += start_match_positions.size();
        }

      if (start_match_positions.size() > 0)
        {
          if (i == start_match_positions.front())
            {
              start_match_positions.erase(start_match_positions.begin());
            }
        }
    }

  return result;
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    std::string dummy;
    std::getline(std::cin, dummy);

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::string text;
        std::getline(std::cin, text);

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_lucky_fragments(text) << "\n";
      }
  }
}
