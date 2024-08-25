#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <cmath>

std::string find_min_minutes(std::pair<std::int32_t, std::int32_t> const & start_point,
                             std::string const & walk)
{
  std::pair<std::int32_t, std::int32_t> current_point = start_point;

  std::uint32_t past_minutes = 0;

  for (auto const & direction : walk)
    {
      if (direction == 'N') {++(current_point.second);}
      else if (direction == 'S') {--(current_point.second);}
      else if (direction == 'E') {++(current_point.first);}
      else {--(current_point.first);}

      ++past_minutes;

      std::uint32_t min_minutes = std::abs(current_point.first) +
                                  std::abs(current_point.second);

      if (past_minutes >= min_minutes)
        {
          return std::to_string(past_minutes);
        }
    }

  return "IMPOSSIBLE";
}


int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::int32_t x;
        std::cin >> x;

        std::int32_t y;
        std::cin >> y;

        std::pair<std::int32_t, std::int32_t> start_point(x, y);

        std::string walk;
        std::cin >> walk;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_min_minutes(start_point, walk) << "\n";
      }
  }
}
