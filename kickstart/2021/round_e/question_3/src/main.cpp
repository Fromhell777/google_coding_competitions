#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

struct crossword_cell_t
{
  char character;
  std::vector<std::pair<std::size_t, std::size_t>> mirror_positions;
};

using crossword_t = std::vector<std::vector<crossword_cell_t>>;

void complete_crossword(crossword_t & crossword)
{
  std::size_t filled_cells = 0;

  std::vector<std::pair<std::size_t, std::size_t>> check_positions;

  for (std::size_t i = 0; i < crossword.size(); ++i)
    {

      for (std::size_t j = 0; j < crossword[0].size(); ++j)
        {
          if (crossword[i][j].character != '#' and
              crossword[i][j].character != '.')
            {
              check_positions.emplace_back(i, j);
            }

        }
    }

  while (not check_positions.empty())
    {
      std::vector<std::pair<std::size_t, std::size_t>> new_positions;

      for (auto const & position : check_positions)
        {
          for (auto const & mirror_position :
               crossword[position.first][position.second].mirror_positions)
            {
              if (crossword[mirror_position.first][mirror_position.second].character == '.')
                {
                  ++filled_cells;

                  new_positions.emplace_back(mirror_position.first,
                                             mirror_position.second);

                  crossword[mirror_position.first][mirror_position.second].character =
                    crossword[position.first][position.second].character;
                }
            }
        }
      check_positions = new_positions;
    }


  std::cout << filled_cells << '\n';

  for (std::size_t i = 0; i < crossword.size(); ++i)
    {

      for (std::size_t j = 0; j < crossword[0].size(); ++j)
        {
          std::cout << crossword[i][j].character;

        }
      std::cout << '\n';
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
        std::uint32_t rows;
        std::cin >> rows;

        std::uint32_t columns;
        std::cin >> columns;

        crossword_t crossword(rows, std::vector<crossword_cell_t>(columns));

        std::vector<bool> veritcal_word_started(columns, false);
        std::vector<std::size_t> veritcal_start_postition(columns, 0);

        for (std::size_t i = 0; i < rows; ++i)
          {
            bool horizontal_word_started = false;
            std::size_t horizontal_start_postition = 0;

            for (std::size_t j = 0; j < columns; ++j)
              {
                std::cin >> crossword[i][j].character;

                if (crossword[i][j].character != '#')
                  {
                    if (not horizontal_word_started) {horizontal_start_postition = j;}
                    horizontal_word_started = true;

                    if (not veritcal_word_started[j]) {veritcal_start_postition[j] = i;}
                    veritcal_word_started[j] = true;
                  }

                if (horizontal_word_started and
                    (crossword[i][j].character == '#' or j == columns - 1))
                  {
                    horizontal_word_started = false;

                    std::size_t end_position = j;
                    if (crossword[i][j].character != '#') {++end_position;}

                    for (std::size_t k = 0;
                         k < (end_position - horizontal_start_postition) / 2; ++k)
                      {
                        crossword[i][horizontal_start_postition + k].mirror_positions.emplace_back(i, end_position - k - 1);
                        crossword[i][end_position - k - 1].mirror_positions.emplace_back(i, horizontal_start_postition + k);
                      }
                  }

                if (veritcal_word_started[j] and
                    (crossword[i][j].character == '#' or i == rows - 1))
                  {
                    veritcal_word_started[j] = false;

                    std::size_t end_position = i;
                    if (crossword[i][j].character != '#') {++end_position;}

                    for (std::size_t k = 0;
                         k < (end_position - veritcal_start_postition[j]) / 2; ++k)
                      {
                        crossword[veritcal_start_postition[j] + k][j].mirror_positions.emplace_back(end_position - k - 1, j);
                        crossword[end_position - k - 1][j].mirror_positions.emplace_back(veritcal_start_postition[j] + k, j);
                      }
                  }
              }
          }

        std::cout << "Case #" << t + 1 << ": ";
        complete_crossword(crossword);
      }
  }
}
