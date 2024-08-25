#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void find_time(std::uint64_t const first_time, std::uint64_t const second_time,
               std::uint64_t const third_time)
{
  std::vector<std::uint64_t> times = {first_time, second_time, third_time};
  std::sort(std::begin(times), std::end(times));

  long double rotation = 0.0;
  do {
    //long double hours   = times[0];
    //long double minutes = times[1];
    //long double seconds = times[2];

    //long double nanoseconds = (times[2] * 12.0 * 10000000000.0) / (720.0);
    //std::uint64_t minutes   = (times[1]) / (60.0 * 12.0 * 10000000000.0);

    //long double remainder;
    //if (std::modf((minutes - 12 * hours) / 11.0, &remainder) == 0.0)
    //  {
    //    rotation = (minutes - 12 * hours) / 11.0;

    //    std::cout << "rotation: " << rotation << '\n';

    //    if (std::modf((seconds + rotation) / 720.0, &remainder) == 0.0 and
    //        std::modf((minutes + rotation) / 12.0, &remainder) == 0.0)
    //      {
    //        if ((seconds + rotation) / 720.0 == (minutes + rotation) / 12.0 and
    //            (minutes + rotation) / 12.0 == hours + rotation)
    //          {
    //            break;
    //          }
    //      }
    //  }


  } while (std::next_permutation(std::begin(times), std::end(times)));

  std::uint64_t hours       = (times[0] + rotation) / (360.0 * 10000000000.0);
  std::uint64_t minutes     = (times[1] + rotation) / (60.0 * 12.0 * 10000000000.0);
  std::uint64_t seconds     = (times[2] + rotation) / (60.0 * 12.0 * 10000000000.0);
  std::uint64_t nanoseconds = (times[2] + rotation) / (360.0 * 12.0 * 10000000000.0);

  std::cout << hours << ' ' << minutes << ' ' << seconds << ' ' << nanoseconds
            << '\n';
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::uint64_t first_time;
        std::cin >> first_time;

        std::uint64_t second_time;
        std::cin >> second_time;

        std::uint64_t third_time;
        std::cin >> third_time;

        std::cout << "Case #" << t + 1 << ": ";
        find_time(first_time, second_time, third_time);

      }
  }
}
