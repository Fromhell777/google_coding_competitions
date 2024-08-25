#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>
#include <algorithm>

// Calculates the diagonal starting at the starting_row
// The left_to_right argument indicates if the trace has to be measured from
// left to rigth or from right to left
std::uint32_t calculate_trace(std::vector<std::vector<std::uint32_t>> const & matrix,
                              std::size_t starting_row, bool left_to_right)
{
  std::uint32_t trace = 0;

  for (std::size_t i = 0; i < matrix.size(); ++i)
    {

      // Select the correct diagonal element
      std::size_t index = (starting_row + i) % matrix.size();

      if (left_to_right) {trace += matrix[index][i];}
      else {trace += matrix[index][matrix.size() - i - 1];}
    }

  return trace;
}

// Print the matrix.
// Starting at the starting row.
// The left_to_right argument indicates if the trace was measured from left to
// rigth or from right to left
void print_latin_square(std::vector<std::vector<std::uint32_t>> const & matrix,
                        std::size_t starting_row, bool left_to_right)
{
  for (std::size_t i = 0; i < matrix.size(); ++i)
    {

      std::cout << '\n';

      // Select the correct row to print
      std::size_t index;
      if (left_to_right) {index = (starting_row + i) % matrix.size();}
      else {index = (matrix.size() + starting_row - i - 1) % matrix.size();}


      for (std::size_t j = 0; j < matrix.size(); ++j)
        {
          if (j != 0)
            {
              std::cout << ' ';
            }

          std::cout << matrix[index][j];
        }
    }
}

bool create_matrix_and_check(std::vector<std::vector<std::uint32_t>> & matrix,
                             std::size_t index, std::uint32_t matrix_trace,
                             bool found)
{
  std::vector<std::uint32_t> row(matrix.size());
  std::iota(row.begin(), row.end(), 1);

  do {

    if (index < matrix.size())
      {
        bool col_uniqueness = true;
        for (std::size_t i = 0; i < matrix.size(); ++i)
          {
            for (std::size_t j = 0; j < index; ++j)
              {
                if (matrix[j][i] == row[i])
                  {
                    col_uniqueness = false;
                    break;
                  }
              }
          }

        if (not col_uniqueness) {continue;}

        matrix[index] = row;

        bool result = create_matrix_and_check(matrix, index + 1, matrix_trace,
                                              found);

        if (result) {return true;}
      }
    else
      {
        // for (std::size_t i = 0; i < matrix.size(); ++i)
        //   {
            std::uint32_t trace = calculate_trace(matrix, 0, true);

            if (trace == matrix_trace)
              {
                std::cout << "POSSIBLE";

                print_latin_square(matrix, 0, true);

                return true;
              }

         //    trace = calculate_trace(matrix, i, false);

         //    if (trace == matrix_trace)
         //      {
         //        std::cout << "POSSIBLE";

         //        print_latin_square(matrix, i, false);

         //        return true;
         //      }
         //  }
      }

  } while (std::next_permutation(row.begin(), row.end()));

  return false;
}


void find_latin_square(std::size_t matrix_size, std::size_t matrix_trace)
{
  // Create matrix
  std::vector<std::vector<std::uint32_t>> matrix(matrix_size,
                                                 std::vector<std::uint32_t>(matrix_size));

  bool result = create_matrix_and_check(matrix, 0, matrix_trace, false);

  if (not result) {std::cout << "IMPOSSIBLE";}
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

        std::size_t matrix_trace;
        std::cin >> matrix_trace;

        std::cout << "Case #" << t + 1 << ": ";
        find_latin_square(matrix_size, matrix_trace);
        std::cout << '\n';
      }
  }
}
