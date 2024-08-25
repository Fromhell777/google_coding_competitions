#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

std::string find_building_heights(std::size_t const number_of_buildings,
                                  std::size_t const views_a,
                                  std::size_t const views_b,
                                  std::size_t const views_both)
{
  if (views_a - views_both + views_b > number_of_buildings)
    {
      return " IMPOSSIBLE";
    }

  std::string result;

  if ((views_a == views_both) && (views_b == views_both))
    {
      if (views_both == 1 && views_both != number_of_buildings)
        {
          return " IMPOSSIBLE";
        }

      for (std::size_t i = 0; i < views_both - 1; ++i)
        {
          result += ' ' + std::to_string(number_of_buildings);
        }

      for (std::size_t i = 0; i < number_of_buildings - views_both; ++i)
        {
          result += " 1";
        }

      result += ' ' + std::to_string(number_of_buildings);
    }
  else
    {
      // Extra buildings that A sees
      for (std::size_t i = 0; i < views_a - views_both; ++i)
        {
          result += ' ' + std::to_string(number_of_buildings - 1);
        }

      std::string filling_buildings;
      for (std::size_t i = 0; i < number_of_buildings - views_a - views_b + views_both; ++i)
        {
          filling_buildings += " 1";
        }

      // Buildings viewed by both
      std::string both_buildings;
      for (std::size_t i = 0; i < views_both; ++i)
        {
          both_buildings += ' ' + std::to_string(number_of_buildings);
        }

      if (views_b == views_both)
        {
          // Filling building at the A side
          result += filling_buildings + both_buildings;
        }
      else
        {
          // Filling building at the B side
          result += both_buildings + filling_buildings;
        }

      // Extra buildings that B sees
      for (std::size_t i = 0; i < views_b - views_both; ++i)
        {
          result += ' ' + std::to_string(number_of_buildings - 1);
        }
    }

  return result;
}

int main()
{
  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_of_buildings;
        std::cin >> number_of_buildings;

        std::size_t views_a;
        std::cin >> views_a;

        std::size_t views_b;
        std::cin >> views_b;

        std::size_t views_both;
        std::cin >> views_both;

        std::cout << "Case #" << t + 1 << ":";
        std::cout << find_building_heights(number_of_buildings, views_a,
                                           views_b, views_both) << "\n";
      }
  }
}
