#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

std::uint32_t find_minimum_append(std::vector<std::string> const & elements)
{
  std::uint32_t cost = 0;
  std::string last_string = elements.front();

  for (std::size_t i = 1; i < elements.size(); ++i)
    {

      std::string remember_string = last_string;

      std::uint32_t new_size = std::max<std::uint32_t>(last_string.size(),
                                                       elements[i].size());

      if (new_size == elements[i].size())
        {
          if (new_size == last_string.size())
            {
              if (elements[i] > last_string)
                {
                  last_string = elements[i];
                }
              else
                {
                  last_string = elements[i] + '0';
                }
            }
          else
            {
              last_string = elements[i];
            }
        }
      else
        {
          if (elements[i] > last_string.substr(0, elements[i].size()))
            {
              last_string = elements[i] + std::string(last_string.size() -
                                                       elements[i].size(), '0');
            }
          else
            {
              std::string suffix_string = last_string.substr(elements[i].size());
              std::string incremented_suffix_string = suffix_string;

              // increment
              std::string::reverse_iterator iter = incremented_suffix_string.rbegin();
              std::string::reverse_iterator end = incremented_suffix_string.rend();
              std::uint32_t carry = 1;
              while (carry && iter != end)
                {
                  std::uint32_t value = (*iter - '0') + carry;
                  carry = (value / 10);
                  *iter = '0' + (value % 10);
                  ++iter;
                }
              if (carry)
                {
                  incremented_suffix_string.insert(0, 1, '1');
                }

              if (suffix_string.size() < incremented_suffix_string.size())
                {
                  last_string = elements[i] +
                    std::string(incremented_suffix_string.size(), '0');
                }
              else
                {
                  if (elements[i] + suffix_string > last_string)
                    {
                      last_string = elements[i] + suffix_string;
                    }
                  else if (elements[i] + incremented_suffix_string > last_string)
                    {
                      last_string = elements[i] + incremented_suffix_string;
                    }
                  else
                    {
                      last_string = elements[i] +
                        std::string(suffix_string.size() + 1, '0');
                    }
                }
            }
        }

      cost += last_string.size() - elements[i].size();
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

        std::vector<std::string> elements;

        for (std::size_t i = 0; i < number_of_elements; ++i)
          {
            std::uint32_t element;
            std::cin >> element;

            elements.emplace_back(std::to_string(element));
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_minimum_append(elements) << '\n';

      }
  }
}
