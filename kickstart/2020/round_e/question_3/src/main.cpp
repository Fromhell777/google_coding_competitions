#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

using toy_t = std::pair<std::uint32_t, std::uint32_t>;

std::string find_longest_play_time(std::vector<toy_t> const & toys)
{
  std::size_t removed_toys     = 0;
  std::size_t min_removed_toys = 0;

  std::uint64_t one_cycle_enjoyment = 0;

  for (auto const & toy : toys)
    {
      one_cycle_enjoyment += toy.first;
    }

  std::uint64_t max_enjoyment = one_cycle_enjoyment;

  std::uint64_t second_cycle_enjoyment = 0;

  auto remembrance_compare = [](toy_t lhs, toy_t rhs)
                               {
                                 return lhs.first + lhs.second <
                                        rhs.first + rhs.second;
                               };

  std::priority_queue<toy_t,
                      std::vector<toy_t>,
                      decltype(remembrance_compare)> played_toys(remembrance_compare);

  for (auto const & toy : toys)
    {
      played_toys.emplace(toy.first, toy.second);

      second_cycle_enjoyment += toy.first;

      auto largest_remmembrance_toy = played_toys.top();

      while (largest_remmembrance_toy.second + largest_remmembrance_toy.first >
             one_cycle_enjoyment)
        {
          ++removed_toys;
          one_cycle_enjoyment    -= largest_remmembrance_toy.first;
          second_cycle_enjoyment -= largest_remmembrance_toy.first;

          played_toys.pop();

          if (played_toys.empty()) {break;}

          largest_remmembrance_toy = played_toys.top();
        }

      if (one_cycle_enjoyment + second_cycle_enjoyment > max_enjoyment)
        {
          max_enjoyment = one_cycle_enjoyment + second_cycle_enjoyment;
          min_removed_toys = removed_toys;
        }
    }

  if (played_toys.size() > 0)
    {
      return std::to_string(removed_toys) + " INDEFINITELY";
    }

  return std::to_string(min_removed_toys) + " " + std::to_string(max_enjoyment);
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_of_toys;
        std::cin >> number_of_toys;

        std::vector<toy_t> toys(number_of_toys);

        for (std::size_t i = 0; i < number_of_toys; ++i)
          {
            std::uint32_t enjoyment;
            std::cin >> enjoyment;

            std::uint32_t remembrance;
            std::cin >> remembrance;

            toys[i] = std::make_pair(enjoyment, remembrance);
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_longest_play_time(toys) << "\n";
      }
  }
}
