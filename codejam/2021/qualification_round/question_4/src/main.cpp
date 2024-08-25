#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

std::size_t perform_querry(std::size_t const first_index,
                           std::size_t const second_index,
                           std::size_t const third_index)
{
  std::cout << first_index << ' ' << second_index << ' '
            << third_index << '\n';

  std::size_t answer;
  std::cin >> answer;

  return answer;
}


void find_element_order(std::size_t const number_of_elements)
{
  std::vector<std::size_t> order = {1, 2, 3};

  // initialize with first querry
  std::size_t answer = perform_querry(1, 2, 3);

  std::iter_swap(std::begin(order) + 1, std::begin(order) + answer - 1);

  for (std::size_t i = 3; i < number_of_elements; ++i)
    {
      std::size_t left_boundary  = 0;
      std::size_t right_boundary = std::size(order) - 1;

      // Do first ternary search with the middle and boundaries to see if the
      // element is inside the current order vector
      std::size_t mid_boundary = (right_boundary + left_boundary) / 2;

      answer = perform_querry(i + 1, order[left_boundary], order[mid_boundary]);

      if (answer == order[left_boundary])
        {
          order.insert(std::begin(order), i + 1);
          continue;
        }
      else if (answer == order[mid_boundary])
        {
          left_boundary = mid_boundary;

          mid_boundary = (right_boundary + left_boundary) / 2;

          answer = perform_querry(i + 1, order[mid_boundary],
                                  order[right_boundary]);

          if (answer == order[right_boundary])
            {
              order.emplace_back(i + 1);
              continue;
            }
          else if (answer == order[mid_boundary])
            {
              right_boundary = mid_boundary;
            }
          else if (answer == i + 1)
            {
              left_boundary = mid_boundary;
            }
        }
      else if (answer == i + 1)
        {
          right_boundary = mid_boundary;
        }

      // Perform ternary search
      while (left_boundary + 1 != right_boundary)
        {
          std::size_t first_third_boundary  = (right_boundary + 2 * left_boundary) / 3;
          std::size_t second_third_boundary = (2 * right_boundary + left_boundary) / 3;

          answer = perform_querry(i + 1, order[first_third_boundary],
                                  order[second_third_boundary]);

          if (answer == order[first_third_boundary])
            {
              right_boundary = first_third_boundary;
            }
          else if (answer == order[second_third_boundary])
            {
              left_boundary = second_third_boundary;
            }
          else if (answer == i + 1)
            {
              left_boundary  = first_third_boundary;
              right_boundary = second_third_boundary;
            }
        }

      order.insert(std::begin(order) + left_boundary + 1 , i + 1);
    }

  for (auto const element : order)
    {
      std::cout << element;

      if (element != order.back()) {std::cout << ' ';}
      else {std::cout << '\n';}
    }

  std::cin >> answer;
}

int main()
{

  {
    //timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    std::size_t number_of_elements;
    std::cin >> number_of_elements;

    std::uint32_t number_of_querries;
    std::cin >> number_of_querries;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        find_element_order(number_of_elements);
      }
  }
}
