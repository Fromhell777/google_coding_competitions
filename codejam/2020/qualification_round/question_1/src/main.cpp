#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_set>

std::uint32_t calculate_trace(std::vector<std::vector<std::uint32_t>> const & matrix)
{
  std::uint32_t result = 0;

  for (std::size_t i = 0; i < matrix.size(); ++i)
    {
      result += matrix[i][i];
    }

  return result;
}

void find_duplicates(std::vector<std::vector<std::uint32_t>> const & matrix)
{
  std::size_t duplicate_rows = 0;
  std::size_t duplicate_cols = 0;

  for (auto const & row : matrix)
    {
      std::unordered_set<std::uint32_t> set(row.begin(), row.end());

      if (set.size() != row.size())
        {
          ++duplicate_rows;
        }
    }

  for (std::size_t i = 0; i < matrix.back().size(); ++i)
    {
      std::unordered_set<std::uint32_t> set;
      for (std::size_t j = 0; j < matrix.size(); ++j)
        {
          set.insert(matrix[j][i]);
        }

      if (set.size() != matrix.size())
        {
          ++duplicate_cols;
        }
    }

  std::uint32_t trace = calculate_trace(matrix);

  std::cout << trace << ' ' << duplicate_rows << ' ' << duplicate_cols << '\n';
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t rows;
        std::cin >> rows;
        std::vector<std::vector<std::uint32_t>> matrix;

        for (std::size_t i = 0; i < rows; ++i)
          {
            matrix.push_back({});
          for (std::size_t j = 0; j < rows; ++j)
            {
              std::uint32_t element;
              std::cin >> element;
              matrix.back().emplace_back(element);
            }
          }

        std::cout << "Case #" << t + 1 << ": ";
        find_duplicates(matrix);
      }
  }
}
