#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

using matrix_t = std::vector<std::vector<char>>;

bool polyominos_left(matrix_t const & wall)
{
  for (auto const & row : wall)
    {
      if (row.size() != 0) {return true;}
    }

  return false;
}

bool check_polyomino(matrix_t const & wall, char polyomino)
{
  for (std::size_t i = 0; i < wall.size(); ++i)
    {
      bool stable = true;

      for (std::size_t j = 0; j < wall[i].size(); ++j)
        {
          if (wall[i][wall[i].size() - j - 1] != polyomino)
            {
              stable = false;
            }
          else if (not stable) {return false;}
        }
    }

  return true;
}

bool remove_polyomino(matrix_t & wall, char polyomino)
{
  for (std::size_t i = 0; i < wall.size(); ++i)
    {
      while (wall[i].size() > 0 and wall[i].back() == polyomino)
        {
          wall[i].pop_back();
        }
    }

  return true;
}

std::string find_stable_wall_build(matrix_t & wall)
{
  std::string build_order;

  while (polyominos_left(wall))
    {
      std::size_t current_buikd_size = build_order.size();

      for (std::size_t i = 0; i < wall.size(); ++i)
        {
          if (wall[i].size() != 0)
            {
              if (check_polyomino(wall, wall[i].back()))
                {
                  build_order += wall[i].back();
                  remove_polyomino(wall, wall[i].back());
                  break;
                }
            }
        }

      if (current_buikd_size == build_order.size()) {return "-1";}
    }

  return build_order;
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

        matrix_t wall(cols, std::vector<char>(rows));

        for (std::size_t i = 0; i < rows; ++i)
          {
            for (std::size_t j = 0; j < cols; ++j)
              {
                char polyomino;
                std::cin >> polyomino;

                wall[j][i] = polyomino;
              }
          }


        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_stable_wall_build(wall) << "\n";
      }
  }
}
