#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <cmath>

std::string find_popo_jumps(std::int64_t const x, std::int64_t const y)
{
  std::string result = "";

  std::uint64_t normal_x = std::abs(x);
  std::uint64_t normal_y = std::abs(y);

  bool previous_x_was_one = false;
  bool previous_y_was_one = false;

  while (normal_x > 0 or normal_y > 0)
    {
      if (normal_x % 2 == 1 && normal_y % 2 == 0)
        {
          if (x > 0) {result += 'E';}
          else {result += 'W';}
        }
      else if (normal_x % 2 == 0 && normal_y % 2 == 1)
        {
          if (y > 0) {result += 'N';}
          else {result += 'S';}
        }
      else if (normal_x % 2 == 1 && normal_y % 2 == 1)
        {
          if (previous_x_was_one)
            {
              ++normal_x;

              if (x > 0) {result.back() = 'W';}
              else {result.back() = 'E';}

              if (y > 0) {result += 'N';}
              else {result += 'S';}
            }
          else if (previous_y_was_one)
            {
              ++normal_y;

              if (y > 0) {result.back() = 'S';}
              else {result.back() = 'N';}

              if (x > 0) {result += 'E';}
              else {result += 'W';}
            }
          else
            {
              return "IMPOSSIBLE";
            }
        }
      else if (normal_x % 2 == 0 && normal_y % 2 == 0)
        {
          if (previous_x_was_one)
            {
              ++normal_x;

              if (x > 0) {result.back() = 'W';}
              else {result.back() = 'E';}

              if (x > 0) {result += 'E';}
              else {result += 'W';}
            }
          else if (previous_y_was_one)
            {
              ++normal_y;

              if (y > 0) {result.back() = 'S';}
              else {result.back() = 'N';}

              if (y > 0) {result += 'N';}
              else {result += 'S';}
            }
          else
            {
              return "IMPOSSIBLE";
            }
        }
      else
        {
          return "IMPOSSIBLE";
        }

      if (normal_x % 2 == 1)
        {
          previous_x_was_one = true;
        }
      else
        {
          previous_x_was_one = false;
        }

      if (normal_y % 2 == 1)
        {
          previous_y_was_one = true;
        }
      else
        {
          previous_y_was_one = false;
        }

      normal_x >>= 1;
      normal_y >>= 1;
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
        std::int64_t x;
        std::cin >> x;

        std::int64_t y;
        std::cin >> y;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_popo_jumps(x, y) << "\n";
      }
  }
}
