#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::uint64_t find_highest_coin_path(std::vector<std::vector<std::uint64_t>> const & matrix)
{
  std::uint64_t result = 0;

  for (std::size_t i = 0; i < matrix.size(); ++i)
    {
      std::uint64_t max_coins = 0;

      for (std::size_t j = 0; j < matrix.size() - i; ++j)
        {
          max_coins += matrix[j][i + j];
        }

      if (max_coins > result)
        {
          result = max_coins;
        }
    }

  for (std::size_t i = 1; i < matrix.size(); ++i)
    {
      std::uint64_t max_coins = 0;

      for (std::size_t j = 0; j < matrix.size() - i; ++j)
        {
          max_coins += matrix[i + j][j];
        }

      if (max_coins > result)
        {
          result = max_coins;
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
        std::size_t matrix_size;
        std::cin >> matrix_size;

        std::vector<std::vector<std::uint64_t>> matrix(matrix_size);

        for (std::size_t i = 0; i < matrix_size; ++i)
          {
            for (std::size_t j = 0; j < matrix_size; ++j)
              {
                std::uint64_t coins;
                std::cin >> coins;

                matrix[i].emplace_back(coins);
              }
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_highest_coin_path(matrix) << "\n";
      }
  }
}
