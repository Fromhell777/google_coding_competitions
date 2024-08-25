#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>

std::int32_t resolve_querry(std::vector<std::unordered_set<std::size_t>> const & connections,
                            std::string const & start_name,
                            std::string const & end_name)
{
  // Initialise the end letters from the end name
  std::bitset<26> end_letters;

  for (auto const letter : end_name)
    {
      end_letters.set(letter - 65);
    }

  // Initialise the reachable letters from the starting name
  std::unordered_set<std::size_t> reachable_letters;
  std::bitset<26> used_letters;

  for (auto const letter : start_name)
    {
      reachable_letters.emplace(letter - 65);
      used_letters.set(letter - 65);
    }

  std::size_t chain_length = 2;

  // Perform Dijkstra
  while (!reachable_letters.empty())
    {
      std::unordered_set<std::size_t> new_reachable_letters;

      for (auto const reachable_letter : reachable_letters)
        {
          if (end_letters[reachable_letter] == 1) {return chain_length;}

          for (auto const new_reachable_letter : connections[reachable_letter])
            {
              if (used_letters[new_reachable_letter] == 0)
                {
                  new_reachable_letters.emplace(new_reachable_letter);
                  used_letters.set(new_reachable_letter);
                }
            }

        }

      reachable_letters = new_reachable_letters;
      ++chain_length;
    }

  return -1;
}

std::string find_minimal_friendship_chain(std::vector<std::string> const & names,
                                          std::size_t const number_of_querries)
{
  // Make a list of all the connections from one letter to another
  std::vector<std::unordered_set<std::size_t>> connections(26);

  for (auto const & name : names)
    {
      std::unordered_set<std::size_t> name_connections;
      for (auto const letter : name)
        {
          for (auto const connection_letter : name)
            {
              connections[connection_letter - 65].emplace(letter - 65);
            }
        }
    }

  std::string result;

  // Perform dijkstra for shortest chain
  for (std::size_t i = 0; i < number_of_querries; ++i)
    {
      std::size_t start_name_index;
      std::cin >> start_name_index;

      std::size_t end_name_index;
      std::cin >> end_name_index;

      result.append(" ");
      result.append(std::to_string(resolve_querry(connections,
                                                  names[start_name_index - 1],
                                                  names[end_name_index - 1])));
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
        std::size_t number_of_names;
        std::cin >> number_of_names;

        std::size_t number_of_querries;
        std::cin >> number_of_querries;

        std::string dummy;
        std::getline(std::cin, dummy);

        std::vector<std::string> names(number_of_names);

        for (std::size_t i = 0; i < number_of_names; ++i)
          {
            char delimiter = ' ';

            if (i == number_of_names - 1) {delimiter = '\n';}

            std::string name;
            std::getline(std::cin, name, delimiter);

            names[i] = name;
          }

        std::cout << "Case #" << t + 1 << ":";
        std::cout << find_minimal_friendship_chain(names,
                                                   number_of_querries) << '\n';
      }
  }
}
