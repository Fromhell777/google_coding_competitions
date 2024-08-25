#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::size_t find_longest_arithmetic(std::vector<std::uint32_t> const & numbers)
{
  std::size_t result = 0;
  std::size_t current_array_length = 2;
  std::int32_t current_step_size = numbers[0] - numbers[1];

  for (std::size_t i = 1; i < numbers.size() - 1; ++i)
    {
      std::int32_t new_step_size = numbers[i] - numbers[i + 1];

      if (new_step_size == current_step_size)
        {
          ++current_array_length;
        }
      else
        {
          if (current_array_length > result) {result = current_array_length;}

          current_array_length = 2;
          current_step_size    = new_step_size;
        }
    }

  if (current_array_length > result) {result = current_array_length;}

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
        std::size_t array_size;
        std::cin >> array_size;

        std::vector<std::uint32_t> numbers(array_size);

        for (std::size_t i = 0; i < array_size; ++i)
          {
            std::uint32_t number;
            std::cin >> number;

            numbers[i] = number;
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_longest_arithmetic(numbers) << "\n";
      }
  }
}
