#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string find_super_match(std::vector<std::string> const & patterns)
{
  std::vector<std::string> first_patterns;

  for (auto const & pattern : patterns)
    {
      std::string::size_type n = pattern.find('*');

      if (n != 0)
        {
          first_patterns.emplace_back(pattern.substr(0, n));
        }
    }

  std::sort(first_patterns.begin(), first_patterns.end(),
            [](std::string lhs, std::string rhs)
              {
                return lhs.size() < rhs.size();
              });

  std::string result_front = "";

  if (first_patterns.size() > 0)
    {
      result_front = first_patterns.back();

      // Check if the other match
      for (std::size_t i = 0; i < first_patterns.size() - 1; ++i)
        {
          std::string::size_type n = result_front.find(first_patterns[i]);

          if (n == std::string::npos || n != 0)
            {
              return "*";
            }
        }
    }

  std::vector<std::string> last_patterns;

  for (auto const & pattern : patterns)
    {
      std::string::size_type n = pattern.rfind('*');

      if (n != pattern.size() - 1)
        {
          last_patterns.emplace_back(pattern.substr(n + 1, pattern.size() - n - 1));
        }
    }

  std::sort(last_patterns.begin(), last_patterns.end(),
            [](std::string lhs, std::string rhs)
              {
                return lhs.size() < rhs.size();
              });

  std::string result_back = "";

  if (last_patterns.size() > 0)
    {
      result_back = last_patterns.back();

      // Check if the other match
      for (std::size_t i = 0; i < last_patterns.size() - 1; ++i)
        {
          std::string::size_type n = result_back.rfind(last_patterns[i]);

          if (n == std::string::npos || n != result_back.size() - last_patterns[i].size())
            {
              return "*";
            }
        }
    }


  std::string result_mid = "";

  for (auto const & pattern : patterns)
    {
      std::string mid_string = pattern;

      std::string::size_type n1 = mid_string.find('*');

      if (n1 != std::string::npos)
        {
          mid_string = mid_string.substr(n1 + 1, mid_string.size() - n1 - 1);

          std::string::size_type n2 = mid_string.rfind('*');

          if (n2 != std::string::npos)
            {
              mid_string = mid_string.substr(0, n2);

              if (mid_string.size() > 0)
                {
                  mid_string.erase(std::remove(mid_string.begin(), mid_string.end(), '*'),
                                   mid_string.end());
                  result_mid += mid_string;
                }
            }
        }
    }

  return result_front + result_mid + result_back;
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_patterns;
        std::cin >> number_patterns;

        std::string dummy;
        std::getline(std::cin, dummy); // removes the left over new line character

        std::vector<std::string> patterns;

        for (std::size_t i = 0; i < number_patterns; ++i)
          {
            std::string pattern;
            std::getline(std::cin, pattern);
            patterns.emplace_back(pattern);
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_super_match(patterns) << "\n";
      }
  }
}
