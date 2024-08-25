#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

void print_with_nesting_parentheses(std::string const & number)
{
  std::size_t current_depth = 0;
  for (auto const & character : number)
    {
      std::size_t digit = character - '0';

      for (; current_depth < digit; ++current_depth)
        {
          std::cout << '(';
        }

      for (; current_depth > digit; --current_depth)
        {
          std::cout << ')';
        }

      std::cout << character;
    }

  // Closing parentheses
  for (; current_depth > 0; --current_depth)
    {
      std::cout << ')';
    }
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    std::string number;
    std::getline(std::cin, number); // removes the left over new line character

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::getline(std::cin, number);

        std::cout << "Case #" << t + 1 << ": ";
        print_with_nesting_parentheses(number);
        std::cout << '\n';
      }
  }
}
