#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::int32_t find_mural_minimum_cost(std::string const & mural,
                                     std::int32_t const x_cost,
                                     std::int32_t const y_cost)
{
  std::int32_t mural_size = std::size(mural);

  std::int32_t cost = 0;

  if (mural_size == 1) {return 0;}

  // find first letter
  std::int32_t first_letter_index = mural_size;
  for (std::int32_t i = 0; i < mural_size; ++i)
    {
      if (mural[i] != '?')
        {
          first_letter_index = i;
          break;
        }
    }

  if (first_letter_index == mural_size)
    {
      cost = 0;

      if (x_cost < cost) {cost = x_cost;}
      if (y_cost < cost) {cost = y_cost;}
      if (x_cost * ((mural_size - 1) / 2) +
          y_cost * ((mural_size - 1) / 2) < cost)
        {
          cost = x_cost * ((mural_size - 1) / 2) +
                 y_cost * ((mural_size - 1) / 2);
        }
      if (x_cost * ((mural_size) / 2) +
          y_cost * ((mural_size - 1) / 2) < cost)
        {
          cost = x_cost * ((mural_size) / 2) +
                 y_cost * ((mural_size - 1) / 2);
        }
      if (x_cost * ((mural_size - 1) / 2) +
          y_cost * ((mural_size) / 2) < cost)
        {
          cost = x_cost * ((mural_size - 1) / 2) +
                 y_cost * ((mural_size) / 2);
        }

      return cost;
    }

  // find last letter
  std::int32_t last_letter_index = mural_size;
  for (std::int32_t i = mural_size - 1; i >= 0; --i)
    {
      if (mural[i] != '?')
        {
          last_letter_index = i;
          break;
        }
    }

  // Calculate minimum cost of prefix question marks
  if (first_letter_index != 0)
    {
      std::int32_t prefix_cost = 0;

      if (x_cost * (first_letter_index / 2) +
          y_cost * (first_letter_index / 2) < prefix_cost)
        {
          prefix_cost = x_cost * (first_letter_index / 2) +
                        y_cost * (first_letter_index / 2);
        }

      if (mural[first_letter_index] == 'J')
        {
          if (x_cost < prefix_cost) {prefix_cost = x_cost;}
          if (x_cost * ((first_letter_index + 1) / 2) +
              y_cost * ((first_letter_index - 1) / 2) < prefix_cost)
            {
              prefix_cost = x_cost * ((first_letter_index + 1) / 2) +
                            y_cost * ((first_letter_index - 1) / 2);
            }
        }
      else
        {
          if (y_cost < prefix_cost) {prefix_cost = y_cost;}
          if (x_cost * ((first_letter_index - 1) / 2) +
              y_cost * ((first_letter_index + 1) / 2) < prefix_cost)
            {
              prefix_cost = x_cost * ((first_letter_index - 1) / 2) +
                            y_cost * ((first_letter_index + 1) / 2);
            }
        }

      cost += prefix_cost;
    }

  // Calculate minimum cost of suffix question marks
  if (last_letter_index != mural_size - 1)
    {
      std::int32_t suffix_cost = 0;

      if (x_cost * ((mural_size - last_letter_index - 1) / 2) +
          y_cost * ((mural_size - last_letter_index - 1) / 2) < suffix_cost)
        {
          suffix_cost = x_cost * ((mural_size - last_letter_index - 1) / 2) +
                        y_cost * ((mural_size - last_letter_index - 1) / 2);
        }

      if (mural[last_letter_index] == 'C')
        {
          if (x_cost < suffix_cost) {suffix_cost = x_cost;}
          if (x_cost * ((mural_size - last_letter_index) / 2) +
              y_cost * ((mural_size - last_letter_index - 2) / 2) < suffix_cost)
            {
              suffix_cost = x_cost * ((mural_size - last_letter_index) / 2) +
                            y_cost * ((mural_size - last_letter_index - 2) / 2);
            }
        }
      else
        {
          if (y_cost < suffix_cost) {suffix_cost = y_cost;}
          if (x_cost * ((mural_size - last_letter_index - 2) / 2) +
              y_cost * ((mural_size - last_letter_index) / 2) < suffix_cost)
            {
              suffix_cost = x_cost * ((mural_size - last_letter_index - 2) / 2) +
                            y_cost * ((mural_size - last_letter_index) / 2);
            }
        }

      cost += suffix_cost;
    }

  // Calculate leftover cost
  char left_letter = mural[first_letter_index];
  for (std::int32_t i = first_letter_index + 1; i <= last_letter_index; ++i)
    {
      if (mural[i] == 'J' and left_letter == 'C')
        {
          cost += x_cost;
        }
      else if (mural[i] == 'C' and left_letter == 'J')
        {
          cost += y_cost;
        }

      std::int32_t number_of_question_marks = 0;
      while (mural[i] == '?')
        {
          ++number_of_question_marks;
          ++i;
        }

      if (number_of_question_marks > 0)
        {
          std::int32_t question_mark_cost;

          if (mural[i] == 'J' and left_letter == 'C')
            {
              question_mark_cost = x_cost;

              if (x_cost * ((number_of_question_marks / 2) + 1) +
                  y_cost * (number_of_question_marks / 2) < question_mark_cost)
                {
                  question_mark_cost = x_cost * ((number_of_question_marks / 2) + 1) +
                                       y_cost * (number_of_question_marks / 2);
                }
            }
          else if (mural[i] == 'C' and left_letter == 'J')
            {
              question_mark_cost = y_cost;

              if (x_cost * (number_of_question_marks / 2) +
                  y_cost * ((number_of_question_marks / 2) + 1) < question_mark_cost)
                {
                  question_mark_cost = x_cost * (number_of_question_marks / 2) +
                                       y_cost * ((number_of_question_marks / 2) + 1);
                }
            }
          else
            {
              question_mark_cost = 0;

              if (x_cost * ((number_of_question_marks + 1) / 2) +
                  y_cost * ((number_of_question_marks + 1) / 2) < question_mark_cost)
                {
                  question_mark_cost = x_cost * ((number_of_question_marks + 1) / 2) +
                                       y_cost * ((number_of_question_marks + 1) / 2);
                }
            }

          cost += question_mark_cost;
        }

      left_letter = mural[i];
    }


  return cost;
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t x_cost;
        std::cin >> x_cost;

        std::size_t y_cost;
        std::cin >> y_cost;

        std::string mural;
        std::cin >> mural;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_mural_minimum_cost(mural, x_cost, y_cost) << '\n';
      }
  }
}
