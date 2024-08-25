#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

void order_by_rank(std::uint64_t const ranks, std::uint64_t const suits)
{
  std::uint64_t total_moves = (ranks * (suits - 1) + 1) / 2;
  std::cout << total_moves << '\n';

  std::uint64_t pile_a = 2;
  std::uint64_t pile_b = ranks - pile_a + 1;

  std::uint64_t cards_moved = 0;

  std::uint64_t double_cancelation_moves = total_moves;
  if (ranks % 2 == 1 && suits % 2 == 0) {--double_cancelation_moves;}

  for (std::uint64_t i = 0; i < double_cancelation_moves; ++i)
    {
      std::cout << pile_a << ' ' << pile_b << '\n';

      cards_moved += pile_a;

      if (ranks % 2 == 0)
        {
          if ((i + 1) % (ranks / 2) == 0) {pile_a += 2;}
          else {pile_b += 2;}
        }
      else
        {
          if (i % ranks == ranks / 2 - 1)
            {
              ++pile_a;
              ++pile_b;
            }
          else if (i % ranks == ranks / 2)
            {
              ++pile_a;
              ++pile_b;
            }
          else if ((i + 1) % ranks == 0) {pile_a += 2;}
          else {pile_b += 2;}
        }
    }

  // When the total amount of errors that need to be fixed is uneven the last
  // step has to fix only one error
  if (ranks % 2 == 1 && suits % 2 == 0)
    {
      std::cout << suits - 1 << ' ' << suits * (ranks - 1) << '\n';
    }
}

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
        order_by_rank(ranks, suits);
      }
  }
}
