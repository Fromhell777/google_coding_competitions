#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

std::string find_element_for_wanted_cost(std::size_t const number_of_elements,
                                  std::uint32_t const wanted_cost)
{
  if (wanted_cost < number_of_elements - 1) {return " IMPOSSIBLE";}
  if (wanted_cost > (number_of_elements * (number_of_elements + 1)) / 2 - 1)
    {
      return " IMPOSSIBLE";
    }


  std::uint32_t current_cost = number_of_elements - 1;

  std::vector<std::uint32_t> elements(number_of_elements);
  std::iota(std::begin(elements), std::end(elements), 1);

  for (std::int32_t i = std::size(elements) - 1; i >= 0; --i)
    {
      std::size_t extra_cost = std::min(static_cast<std::uint32_t>(std::size(elements) - i) - 1,
                                        wanted_cost - current_cost);

      current_cost += extra_cost;

      std::reverse(elements.begin() + i,
                   elements.begin() + i + extra_cost + 1);
    }

  std::string elements_to_string = "";
  for (auto const element : elements)
    {
      elements_to_string += ' ' + std::to_string(element);
    }

  return elements_to_string;
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

        std::uint32_t wanted_cost;
        std::cin >> wanted_cost;

        std::cout << "Case #" << t + 1 << ":";
        std::cout << find_element_for_wanted_cost(number_of_elements,
                                                  wanted_cost) << '\n';
      }
  }
}
