#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::string find_next_roaring_number(std::string const & number)
{

  if (number.size() == 1) {return "12";}

  unsigned long long result = -1;

  // Check perfect divisions
  for (std::size_t i = 1; i <= (number.size() + 1) / 2; ++i)
    {
      std::string current_number = number;

      if (current_number.size() % i != 0)
        {
          std::string prefix = "1";

          for (std::size_t j = i - 1; j > current_number.size() % i; --j)
            {
              prefix += '0';
            }

          current_number = prefix + std::string(number.size(), '0');
        }

      unsigned long long needed_number = std::stoull(current_number.substr(0, i));
      bool possible = true;
      bool already_increased = false;

      for (std::size_t j = i; j < current_number.size(); j += i)
        {
          if (already_increased)
            {
              ++needed_number;
            }
          else
            {
              ++needed_number;

              if (needed_number != std::stoull(current_number.substr(j, i)))
                {
                  already_increased = true;
                }

              if (needed_number < std::stoull(current_number.substr(j, i)))
                {
                  ++needed_number;
                }

            }

          if (std::to_string(needed_number).size() > i)
            {
              possible = false;
              break;
            }
        }

      if (possible)
        {
          std::string possible_result;

          for (std::size_t j = 0; j < current_number.size() / i; ++j)
            {
              possible_result = std::to_string(needed_number - j) +
                                possible_result;
            }

          if (std::stoull(possible_result) < result)
            {
              result = std::stoull(possible_result);
            }
        }
    }

  // Check magnitude transistions
  unsigned long long transistion_point = 10;
  for (std::size_t i = 1; i <= number.size() / 2; ++i)
    {
      for (unsigned long long j = transistion_point - 9; j < transistion_point; ++j)
        {
          std::string possible_result = std::to_string(j);
          std::size_t increment = 1;

          while (possible_result.size() < number.size())
            {
              possible_result += std::to_string(j + increment);
              ++increment;
            }

          if (std::stoull(possible_result) >= std::stoull(number) and
              std::stoull(possible_result) < result and
              increment > 1)
            {
              result = std::stoull(possible_result);
            }

          if (transistion_point == 10)
            {
              possible_result += std::to_string(j + increment);

              if (std::stoull(possible_result) >= std::stoull(number) and
                  std::stoull(possible_result) < result and
                  increment > 2)
                {
                  result = std::stoull(possible_result);
                }
            }
        }
      transistion_point *= 10;
    }

  return std::to_string(result);
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::uint64_t number;
        std::cin >> number;

        ++number;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_next_roaring_number(std::to_string(number)) << '\n';
      }
  }
}
