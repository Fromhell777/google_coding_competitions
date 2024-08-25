#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::size_t find_record_breakers(std::vector<std::uint32_t> const & days)
{
  std::size_t result = 0;
  std::int32_t previous_max = -1;

  for (std::size_t i = 0; i < days.size(); ++i)
    {
      if (previous_max < static_cast<std::int32_t>(days[i]))
        {
          previous_max = days[i];

          if ((i == days.size() - 1) or (days[i + 1] < days[i]))
            {
              ++result;
              ++i;
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

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_of_days;
        std::cin >> number_of_days;

        std::vector<std::uint32_t> days(number_of_days);

        for (std::size_t i = 0; i < number_of_days; ++i)
          {
            std::size_t visitors;
            std::cin >> visitors;

            days[i] = visitors;
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_record_breakers(days) << "\n";
      }
  }
}
