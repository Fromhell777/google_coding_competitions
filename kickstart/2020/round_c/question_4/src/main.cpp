#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::int64_t find_sweetness_score(std::vector<std::int32_t> & candies,
                                  std::uint32_t operations)
{
  std::int64_t sweetness_score = 0;

  std::vector<std::int64_t> candies_partial_sums(candies.size());
  candies_partial_sums[0] = candies[0];

  for (std::size_t i = 1; i < candies_partial_sums.size(); ++i)
    {
      if ((i % 2) == 1)
        {
          candies_partial_sums[i] = candies_partial_sums[i - 1] - candies[i];
        }
      else
        {
          candies_partial_sums[i] = candies_partial_sums[i - 1] + candies[i];
        }
    }

  std::vector<std::int64_t> candies_partial_factor_sums(candies.size());
  candies_partial_factor_sums[0] = candies[0];

  for (std::size_t i = 1; i < candies_partial_factor_sums.size(); ++i)
    {
      if ((i % 2) == 1)
        {
          candies_partial_factor_sums[i] = candies_partial_factor_sums[i - 1] - (i + 1) * candies[i];
        }
      else
        {
          candies_partial_factor_sums[i] = candies_partial_factor_sums[i - 1] + (i + 1) * candies[i];
        }
    }

  for (std::uint32_t i = 0; i < operations; ++i)
    {
      char operation;
      std::cin >> operation;

      if (operation == 'Q')
        {
          std::size_t left_index;
          std::cin >> left_index;

          std::size_t right_index;
          std::cin >> right_index;

          std::int64_t querry_sweetness_score = 0;

          // Extract the right range of numbers
          querry_sweetness_score += candies_partial_factor_sums[right_index - 1];
          if (left_index > 1)
            {
              querry_sweetness_score -= candies_partial_factor_sums[left_index - 2];
            }

          // subtract the extra multiples of the range numbers
          std::int64_t extra_multiples = 0;

          extra_multiples += candies_partial_sums[right_index - 1];
          if (left_index > 1)
            {
              extra_multiples -= candies_partial_sums[left_index - 2];
            }

          querry_sweetness_score -= (left_index - 1) * extra_multiples;

          if ((left_index % 2) == 1)
            {
              sweetness_score += querry_sweetness_score;
            }
          else
            {
              sweetness_score -= querry_sweetness_score;
            }

          //std::cout << "querry score: " << querry_sweetness_score << '\n';
          //std::cout << "sums: " << candies_partial_sums << '\n';
          //std::cout << "factor sums: " << candies_partial_factor_sums << '\n';
          //std::cout << "score: " << sweetness_score << '\n';
        }
      else
        {
          std::size_t update_index;
          std::cin >> update_index;

          std::int32_t update_value;
          std::cin >> update_value;

          std::int64_t change_sums = update_value - candies[update_index - 1];

          if ((update_index % 2) == 0)
            {
              change_sums = -change_sums;
            }

          for (std::size_t j = update_index - 1; j < candies_partial_sums.size(); ++j)
            {
              candies_partial_sums[j] += change_sums;
            }

          std::int64_t change_factor_sums = update_index * change_sums;

          for (std::size_t j = update_index - 1; j < candies_partial_factor_sums.size(); ++j)
            {
              candies_partial_factor_sums[j] += change_factor_sums;
            }

          candies[update_index - 1] = update_value;
        }
    }

  return sweetness_score;
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t array_size;
        std::cin >> array_size;

        std::uint32_t operations;
        std::cin >> operations;

        std::vector<std::int32_t> candies(array_size);

        for (std::size_t i = 0; i < candies.size(); ++i)
          {
            std::uint32_t sweetness;
            std::cin >> sweetness;

            candies[i] = sweetness;
          }

        std::cout << "candies " << candies<< "\n";
        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_sweetness_score(candies, operations) << "\n";
      }
  }
}
