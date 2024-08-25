#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <numeric>
#include <algorithm>

std::size_t find_cheater(std::vector<std::bitset<10000>> const & player_answers)
{
  // Find estimate player skill
  std::vector<long double> estimate_player_skills;

  for (auto const & answers : player_answers)
    {
      long double percentage_correct_answers = answers.count() / 10000.0L;

      long double estimate_player_skill =
        std::log((std::exp(6 * percentage_correct_answers) - 1) /
                 (std::exp(6) - std::exp(6 * percentage_correct_answers))) + 3;

      estimate_player_skill = std::min(std::max(-3.0L, estimate_player_skill), 3.0L);

      estimate_player_skills.emplace_back(estimate_player_skill);
    }

  // Find estimate question difficulty skill
  std::vector<long double> estimate_question_difficulties;

  for (std::size_t i = 0; i < player_answers[0].size(); ++i)
    {
      long double percentage_correct_answers = 0.0L;

      for (auto const & answers : player_answers)
        {
          percentage_correct_answers += answers[i];
        }

      percentage_correct_answers /= 100.0L;

      long double estimate_question_difficulty =
         - std::log((std::exp(6 * percentage_correct_answers) - 1) /
                  (std::exp(6) - std::exp(6 * percentage_correct_answers))) - 3;

      estimate_question_difficulty = std::min(std::max(-3.0L, estimate_question_difficulty), 3.0L);

      estimate_question_difficulties.emplace_back(estimate_question_difficulty);
    }

  // Calculate the likelyhood of the result
  std::size_t cheater       = 0;
  long double largest_error = 0.0L;
  for (std::size_t i = 0; i < std::size(player_answers); ++i)
    {
      long double expected_correct = 0;
      long double real_correct     = 0;

      std::vector<std::size_t> sorted_question_indices(std::size(estimate_question_difficulties));
      std::iota(std::begin(sorted_question_indices),
                std::end(sorted_question_indices), 0);

      std::sort(std::begin(sorted_question_indices),
                std::end(sorted_question_indices),
                [&estimate_question_difficulties](std::size_t lhs, std::size_t rhs)
                  {
                    return estimate_question_difficulties[lhs] < estimate_question_difficulties[rhs];
                  });

      for (std::size_t j = 0; j < std::size(player_answers[i]); ++j)
        {
          if (j < 0.05 * std::size(player_answers[i]) ||
              j > 0.95 * std::size(player_answers[i]))
            {
              expected_correct +=
                1.0L / (1.0L + std::exp(estimate_question_difficulties[sorted_question_indices[j]] -
                                        estimate_player_skills[i]));

              real_correct += player_answers[i][sorted_question_indices[j]];
            }
        }

      if (largest_error < std::abs(expected_correct - real_correct))
        {
          largest_error = std::abs(expected_correct - real_correct);
          cheater = i + 1;
        }
    }

  return cheater;
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    std::size_t percentage_correct;
    std::cin >> percentage_correct;

    std::string dummy;
    std::getline(std::cin, dummy);

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::vector<std::bitset<10000>> player_answers;

        for (std::size_t i = 0; i < 100; ++i)
          {
            std::string answer;
            std::getline(std::cin, answer);

            player_answers.emplace_back(std::bitset<10000>(answer));
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_cheater(player_answers) << '\n';
      }
  }
}
