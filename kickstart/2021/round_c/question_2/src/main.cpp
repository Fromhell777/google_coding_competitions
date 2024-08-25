#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>

std::uint64_t find_amount_of_starting_values(std::uint64_t const gold)
{
  std::uint64_t result = 0;

  std::uint64_t max_sequence_length = std::ceil(std::sqrt(gold)) * 2;

  for (std::uint64_t i = 1; i < max_sequence_length; ++i)
    {
      if ((2 * gold - i + i * i) % (2 * i) == 0 and
          (2 * gold - i + i * i) / (2 * i) >= i)
        {
          ++result;
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
        std::uint64_t gold;
        std::cin >> gold;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_amount_of_starting_values(gold) << "\n";
      }
  }
}
