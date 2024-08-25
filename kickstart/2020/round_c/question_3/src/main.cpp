#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>

bool is_square(std::int64_t n, std::unordered_set<std::int64_t> const & squares)
{
  if (squares.find(n) != squares.end()) {return true;}
  else {return false;}
}

std::uint32_t find_perfect_subarrays(std::vector<std::int32_t> & numbers)
{
  std::uint32_t perfect_subarrays = 0;

  std::partial_sum(std::begin(numbers), std::end(numbers), std::begin(numbers));

  std::unordered_set<std::int64_t> squares;

  for (std::size_t i = 0; i < 3163; ++i)
    {
      squares.insert(i * i);
    }

  for (std::size_t i = 1; i <= numbers.size(); ++i)
    {
      std::int64_t current_sum = numbers[i - 1];
      //std::cout << "sum: "<< current_sum << "\n";

      if (is_square(current_sum, squares)) {++perfect_subarrays;}

      for (std::size_t j = i; j < numbers.size(); ++j)
        {
          current_sum = numbers[j] - numbers[j - i];

          //std::cout << "sum: "<< current_sum << "\n";
          if (is_square(current_sum, squares)) {++perfect_subarrays;}
        }
    }

  return perfect_subarrays;
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

        std::vector<std::int32_t> numbers(10000);

        for (std::size_t i = 0; i < array_size; ++i)
          {
            std::int32_t number;
            std::cin >> number;

            numbers[i] = number;
          }

        for (std::size_t i = 0; i < 10000; ++i)
          {
            numbers[i] = i;
          }

        //std::cout << "numbers: " << numbers << "\n";
        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_perfect_subarrays(numbers) << "\n";
      }
  }
}
