#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::size_t count_countdowns(std::vector<std::size_t> const & numbers,
                             std::size_t countdown)
{
  std::size_t countdowns = 0;
  bool in_countdown = false;
  std::size_t current_number = 0;

  for (auto const number : numbers)
    {
      if ((not in_countdown) and (number == countdown))
        {
          in_countdown   = true;
          current_number = countdown;
        }

      if (in_countdown)
        {
          if (number != current_number)
            {
              if (number == countdown)
                {
                  in_countdown   = true;
                  current_number = countdown;
                }
              else
                {
                  in_countdown = false;
                }
            }
          else if (number == 1)
            {
              in_countdown = false;
              ++countdowns;
            }


          --current_number;
        }
    }

  return countdowns;
}


int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t array_size;
        std::cin >> array_size;

        std::size_t countdown;
        std::cin >> countdown;

        std::vector<std::size_t> numbers;

        for (std::size_t i = 0; i < array_size; ++i)
          {
            std::int32_t number;
            std::cin >> number;

            numbers.emplace_back(number);
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << count_countdowns(numbers, countdown) << "\n";
      }
  }
}
