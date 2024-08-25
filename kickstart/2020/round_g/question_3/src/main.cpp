#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::uint64_t find_minimal_rotations(std::vector<std::int64_t> & wheels,
                                     std::int64_t const number_of_wheel_numbers)
{
  std::sort(wheels.begin(), wheels.end());

  double sum = wheels.front();

  for (std::size_t i = 1; i < wheels.size(); ++i)
    {
      double average = sum / i;

      if (std::abs(wheels[i] - average) >
          std::abs(wheels[i] - number_of_wheel_numbers - average))
          {
            sum += wheels[i] - number_of_wheel_numbers;
          }
      else
        {
          sum += wheels[i];
        }
    }

  double average = sum / wheels.size();

  std::int64_t average_int = std::round(average);

  if (average_int <= 0)
    {
      average_int += number_of_wheel_numbers;
    }

  std::uint64_t result = 0;

  for (auto const wheel_number : wheels)
    {
      if (average_int > wheel_number)
        {
          result += std::min(std::abs(wheel_number - average_int),
                             std::abs(wheel_number + number_of_wheel_numbers -
                                      average_int));
        }
      else
        {
          result += std::min(std::abs(wheel_number - average_int),
                             std::abs(wheel_number - number_of_wheel_numbers -
                                      average_int));
        }
    }

  return result;
}

int main()
{
  {
    timer timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_of_wheels;
        std::cin >> number_of_wheels;

        std::size_t number_of_wheel_numbers;
        std::cin >> number_of_wheel_numbers;

        std::vector<std::int64_t> wheels(number_of_wheels);

        for (std::size_t i = 0; i < number_of_wheels; ++i)
          {
            std::int64_t wheel_number;
            std::cin >> wheel_number;

            wheels[i] = wheel_number;
          }

        std::cout << "case #" << t + 1 << ": ";
        std::cout << find_minimal_rotations(wheels,
                                            number_of_wheel_numbers) << "\n";
      }
  }
}
