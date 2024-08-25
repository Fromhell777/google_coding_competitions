#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

std::uint32_t find_reversort_cost(std::vector<std::uint32_t> & elemenets)
{
  std::uint32_t cost = 0;

  for (std::size_t i = 0; i < std::size(elemenets) - 1; ++i)
    {
      std::uint32_t minimum_element       = elemenets[i];
      std::size_t   minimum_element_index = i;

      for (std::size_t j = i + 1; j < std::size(elemenets); ++j)
        {
          if (elemenets[j] < minimum_element)
            {
              minimum_element       = elemenets[j];
              minimum_element_index = j;
            }
        }

      cost += minimum_element_index - i + 1;

      std::reverse(elemenets.begin() + i,
                   elemenets.begin() + minimum_element_index + 1);
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
        std::size_t number_of_elements;
        std::cin >> number_of_elements;

        std::vector<std::uint32_t> elemenets;

        for (std::size_t i = 0; i < number_of_elements; ++i)
          {
            std::uint32_t element;
            std::cin >> element;

            elemenets.emplace_back(element);
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_reversort_cost(elemenets) << '\n';

      }
  }
}
