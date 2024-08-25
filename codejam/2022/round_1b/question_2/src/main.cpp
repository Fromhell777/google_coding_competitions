#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::uint64_t find_minimum_changes(std::vector<std::vector<std::int64_t>> customers) {

  for (std::size_t i = 0; i < customers.size(); ++i) {
    std::sort(customers[i].begin(), customers[i].end());
  }

  std::vector<std::vector<std::int64_t>> customersEnds(customers.size());
  for (std::size_t i = 0; i < customers.size(); ++i) {
    customersEnds[i].push_back(customers[i][0]);
    customersEnds[i].push_back(customers[i][customers[i].size() - 1]);
  }

  std::uint64_t result = customersEnds[0].back();

  std::int64_t previousFrontCost = customersEnds[0].front();
  std::int64_t previousBackCost = customersEnds[0].back();

  for (std::size_t i = 1; i < customersEnds.size(); ++i) {

    // Choose the best option for the next customer
    std::int64_t previousPressure = customersEnds[i - 1].front();
    std::int64_t frontCost = std::min(std::abs(previousPressure - customersEnds[i].front()),
                                      std::abs(previousPressure - customersEnds[i].back()));

    previousPressure = customersEnds[i - 1].back();
    std::int64_t backCost = std::min(std::abs(previousPressure - customersEnds[i].front()),
                                     std::abs(previousPressure - customersEnds[i].back()));


    if (frontCost + previousBackCost < backCost + previousFrontCost) {

      result += previousBackCost - previousFrontCost;

      if (std::abs(customersEnds[i - 1].front() - customersEnds[i].back()) <
          std::abs(customersEnds[i - 1].front() - customersEnds[i].front())) {

        result += std::abs(customersEnds[i - 1].front() - customersEnds[i].back());

        // Flip the current customer
        auto const tmp = customersEnds[i].front();
        customersEnds[i].front() = customersEnds[i].back();
        customersEnds[i].back() = tmp;

      } else {
        result += std::abs(customersEnds[i - 1].front() - customersEnds[i].front());
      }

      // Flip the previous customer
      auto const tmp = customersEnds[i - 1].front();
      customersEnds[i - 1].front() = customersEnds[i - 1].back();
      customersEnds[i - 1].back() = tmp;

    } else {
      if (std::abs(customersEnds[i - 1].back() - customersEnds[i].back()) <
          std::abs(customersEnds[i - 1].back() - customersEnds[i].front())) {

        result += std::abs(customersEnds[i - 1].back() - customersEnds[i].back());

        // Flip the current customer
        auto const tmp = customersEnds[i].front();
        customersEnds[i].front() = customersEnds[i].back();
        customersEnds[i].back() = tmp;

      } else {
        result += std::abs(customersEnds[i - 1].back() - customersEnds[i].front());
      }
    }

    previousFrontCost = std::abs(customersEnds[i - 1].back() - customersEnds[i].front());
    previousBackCost = std::abs(customersEnds[i - 1].back() - customersEnds[i].back());

    result += std::abs(customersEnds[i].back() - customersEnds[i].front());
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t nbCustomers;
      std::cin >> nbCustomers;

      std::size_t nbProducts;
      std::cin >> nbProducts;

      std::vector<std::vector<std::int64_t>> customers(nbCustomers,
                                                       std::vector<std::int64_t>(nbProducts));
      for (std::size_t i = 0; i < customers.size(); ++i) {
        for (std::size_t j = 0; j < customers[i].size(); ++j) {
          std::cin >> customers[i][j];
        }
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_minimum_changes(customers) << '\n';
    }
  }
}
