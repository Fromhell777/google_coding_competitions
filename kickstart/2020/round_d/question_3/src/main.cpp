#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

void depth_first_scan(std::vector<std::vector<std::size_t>> const & tree,
                      std::size_t const current_node,
                      std::size_t const step_size_a,
                      std::size_t const step_size_b,
                      std::vector<std::size_t> & parents,
                      std::vector<std::size_t> & visits_a,
                      std::vector<std::size_t> & visits_b)
{
  parents.emplace_back(current_node);

  for (auto const child : tree[current_node])
    {
      depth_first_scan(tree, child, step_size_a, step_size_b, parents, visits_a,
                       visits_b);
    }

  parents.pop_back();

  ++visits_a[current_node];
  ++visits_b[current_node];

  if (parents.size() >= step_size_a)
    {
      visits_a[parents[parents.size() - step_size_a]] += visits_a[current_node];
    }

  if (parents.size() >= step_size_b)
    {
      visits_b[parents[parents.size() - step_size_b]] += visits_b[current_node];
    }
}

double find_tree_beauty(std::vector<std::vector<std::size_t>> const & tree,
                        std::size_t const step_size_a,
                        std::size_t const step_size_b)
{
  std::vector<std::size_t> visits_a(tree.size(), 0);
  std::vector<std::size_t> visits_b(tree.size(), 0);
  std::vector<std::size_t> parents;

  depth_first_scan(tree, 0, step_size_a, step_size_b, parents, visits_a,
                   visits_b);

  double sum_chance_a = 0;
  double sum_chance_b = 0;
  double product_chance = 0;

  for (std::size_t i = 0; i < visits_a.size(); ++i)
    {
      sum_chance_a += visits_a[i];
      sum_chance_b += visits_b[i];
      product_chance += visits_a[i] * visits_b[i];
    }

  double result = sum_chance_a / tree.size() +
                  sum_chance_b / tree.size() -
                  product_chance / (tree.size() * tree.size());

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
        std::size_t number_of_nodes;
        std::cin >> number_of_nodes;

        std::size_t step_size_a;
        std::cin >> step_size_a;

        std::size_t step_size_b;
        std::cin >> step_size_b;

        std::vector<std::vector<std::size_t>> tree(number_of_nodes);
        tree[0] = {};

        for (std::size_t i = 1; i < number_of_nodes; ++i)
          {
            std::size_t parent_node;
            std::cin >> parent_node;

            tree[parent_node - 1].emplace_back(i);
          }

        std::cout << std::fixed;

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_tree_beauty(tree, step_size_a, step_size_b) << "\n";
      }
  }
}
