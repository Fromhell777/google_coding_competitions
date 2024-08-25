#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::uint64_t ranks;
        std::cin >> ranks;

        std::uint64_t suits;
        std::cin >> suits;

        std::cout << "Case #" << t + 1 << ": ";
      }
  }
}
