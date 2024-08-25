#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

struct Competitor
{
  Competitor()
    : skill_level(0)
    , left_neighbor(0)
    , up_neighbor(0)
    , right_neighbor(0)
    , down_neighbor(0)
  {
  }

  std::uint64_t skill_level;

  std::uint64_t left_neighbor;
  std::uint64_t up_neighbor;
  std::uint64_t right_neighbor;
  std::uint64_t down_neighbor;
};

using matrix_t = std::vector<std::vector<Competitor>>;

std::uint64_t find_total_interest_level(matrix_t & matrix)
{
  std::uint64_t result = 0;

  bool round_finished = false;

  while (not round_finished)
    {
      round_finished = true;

      // Eliminate candidates
      std::vector<std::uint64_t> up_neighbors(matrix[0].size(), 0);
      std::vector<std::int64_t> down_neighbor_indexes(matrix[0].size(), -1);

      for (std::size_t i = 0; i < matrix.size(); ++i)
        {
          std::uint64_t left_neighbor = 0;
          std::int64_t rigth_neighbor_index = -1;

          for (std::size_t j = 0; j < matrix[0].size(); ++j)
            {
              if (matrix[i][j].skill_level != 0)
                {
                  result += matrix[i][j].skill_level;

                  std::size_t number_compass_neighbors = 0;
                  float average_skill = 0;

                  if (matrix[i][j].left_neighbor != 0)
                    {
                      ++number_compass_neighbors;
                      average_skill += matrix[i][j].left_neighbor;
                    }

                  if (matrix[i][j].up_neighbor != 0)
                    {
                      ++number_compass_neighbors;
                      average_skill += matrix[i][j].up_neighbor;
                    }

                  if (matrix[i][j].right_neighbor != 0)
                    {
                      ++number_compass_neighbors;
                      average_skill += matrix[i][j].right_neighbor;
                    }

                  if (matrix[i][j].down_neighbor != 0)
                    {
                      ++number_compass_neighbors;
                      average_skill += matrix[i][j].down_neighbor;
                    }

                  average_skill /= number_compass_neighbors;

                  if (average_skill > matrix[i][j].skill_level)
                    {
                      matrix[i][j].skill_level = 0;
                      round_finished = false;
                    }
                  else
                    {
                      // Update left neighbor
                      matrix[i][j].left_neighbor = left_neighbor;
                      left_neighbor = matrix[i][j].skill_level;

                      // Update rigth neighbor
                      matrix[i][j].right_neighbor = 0;
                      if (rigth_neighbor_index != -1)
                        {
                          matrix[i][rigth_neighbor_index].right_neighbor =
                            matrix[i][j].skill_level;
                        }
                      rigth_neighbor_index = j;

                      // Update up neighbor
                      matrix[i][j].up_neighbor = up_neighbors[j];
                      up_neighbors[j] = matrix[i][j].skill_level;

                      // Update down neighbor
                      matrix[i][j].down_neighbor = 0;
                      if (down_neighbor_indexes[j] != -1)
                        {
                          matrix[down_neighbor_indexes[j]][j].down_neighbor =
                            matrix[i][j].skill_level;
                        }
                      down_neighbor_indexes[j] = i;
                    }

                }
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
        std::size_t rows;
        std::cin >> rows;

        std::size_t cols;
        std::cin >> cols;

        matrix_t matrix(rows, std::vector<Competitor>(cols));

        for (std::size_t i = 0; i < rows; ++i)
          {
            for (std::size_t j = 0; j < cols; ++j)
              {
                std::cin >> matrix[i][j].skill_level;

                if (j > 0)        {matrix[i][j - 1].right_neighbor = matrix[i][j].skill_level;}
                if (i > 0)        {matrix[i - 1][j].down_neighbor  = matrix[i][j].skill_level;}
                if (j < cols - 1) {matrix[i][j + 1].left_neighbor  = matrix[i][j].skill_level;}
                if (i < rows - 1) {matrix[i + 1][j].up_neighbor    = matrix[i][j].skill_level;}
              }
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_total_interest_level(matrix) << "\n";
      }
  }
}
