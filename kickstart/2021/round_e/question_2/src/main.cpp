#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>

std::uint32_t find_minimum_cuts(std::uint32_t const rows,
                                std::uint32_t const columns,
                                std::uint32_t const max_cut_length,
                                std::uint32_t const top_left_row,
                                std::uint32_t const top_left_column,
                                std::uint32_t const bottom_rigth_row,
                                std::uint32_t const bottom_rigth_column)
{
  std::uint32_t result = 0;

  std::uint32_t min_get_to_circumference = rows;

  // Circumference
  if (top_left_row != 1)
    {
      result += (bottom_rigth_column - top_left_column + max_cut_length) / max_cut_length;

      min_get_to_circumference = std::min(min_get_to_circumference,
                                          (top_left_row - 2 + max_cut_length) / max_cut_length);
    }
  else {min_get_to_circumference = 0;}

  if (top_left_column != 1)
    {
      result += (bottom_rigth_row - top_left_row + max_cut_length) / max_cut_length;

      min_get_to_circumference = std::min(min_get_to_circumference,
                                          (top_left_column - 2 + max_cut_length) / max_cut_length);
    }
  else {min_get_to_circumference = 0;}

  if (bottom_rigth_row != rows)
    {
      result += (bottom_rigth_column - top_left_column + max_cut_length) / max_cut_length;

      min_get_to_circumference = std::min(min_get_to_circumference,
                                          (rows - bottom_rigth_row - 1 + max_cut_length) / max_cut_length);
    }
  else {min_get_to_circumference = 0;}

  if (bottom_rigth_column != columns)
    {
      result += (bottom_rigth_row - top_left_row + max_cut_length) / max_cut_length;

      min_get_to_circumference = std::min(min_get_to_circumference,
                                          (columns - bottom_rigth_column - 1 + max_cut_length) / max_cut_length);
    }
  else {min_get_to_circumference = 0;}

  result += min_get_to_circumference;

  // Fill in with squares
  std::uint32_t const number_of_squares =
    ((bottom_rigth_row - top_left_row + 1) / max_cut_length) *
    ((bottom_rigth_column - top_left_column + 1) / max_cut_length);

  result += (2 + (max_cut_length*max_cut_length - 1)) * number_of_squares;

  // Remove duplicate circumference part
  if (((bottom_rigth_row - top_left_row + 1) % max_cut_length) == 0)
    {
      result -= (bottom_rigth_column - top_left_column + 1) / max_cut_length;
    }
  if (((bottom_rigth_column - top_left_column + 1) % max_cut_length) == 0)
    {
      result -= (bottom_rigth_row - top_left_row + 1) / max_cut_length;
    }

  // Fill in leftover rectangles
  if (((bottom_rigth_row - top_left_row + 1) % max_cut_length)  != 0)
    {
      result += bottom_rigth_column - top_left_column;
      result += (bottom_rigth_column - top_left_column + 1) *
                (((bottom_rigth_row - top_left_row + 1) % max_cut_length) - 1);
    }

  if (((bottom_rigth_column - top_left_column + 1) % max_cut_length)  != 0)
    {
      if (((top_left_row - bottom_rigth_row + 1) / max_cut_length) > 0)
        {
          result += bottom_rigth_row - top_left_row -
                    ((bottom_rigth_row - top_left_row + 1) % max_cut_length);
          result += (bottom_rigth_row - top_left_row + 1 -
                     ((bottom_rigth_column - top_left_column + 1) % max_cut_length)) *
                    (((bottom_rigth_column - top_left_column + 1) % max_cut_length) - 1);

          if (((bottom_rigth_row - top_left_row + 1) % max_cut_length)  != 0)
            {
              ++result;
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
        std::uint32_t rows;
        std::cin >> rows;

        std::uint32_t columns;
        std::cin >> columns;

        std::uint32_t max_cut_length;
        std::cin >> max_cut_length;

        std::uint32_t top_left_row;
        std::cin >> top_left_row;

        std::uint32_t top_left_column;
        std::cin >> top_left_column;

        std::uint32_t bottom_right_row;
        std::cin >> bottom_right_row;

        std::uint32_t bottom_right_column;
        std::cin >> bottom_right_column;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_minimum_cuts(rows, columns, max_cut_length,
                                       top_left_row, top_left_column,
                                       bottom_right_row, bottom_right_column)
                  << "\n";
      }
  }
}
