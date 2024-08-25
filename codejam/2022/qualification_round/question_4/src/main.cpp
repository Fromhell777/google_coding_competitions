#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

struct Module {
  std::uint64_t funFactor; // Module fun factor
  std::uint64_t maxFun; // Maximum fun for this path
  std::vector<Module *> parents; // Pointer to the parent modules
};

std::uint64_t fill_in_max_fun(std::vector<Module> & modules, Module * endPoint) {
  Module * currentModule = endPoint;
  std::uint64_t currentMaxFunFactor = currentModule->funFactor;

  // Get the maximum of the current branch
  while (currentModule->parents.size() == 1) {
    currentMaxFunFactor = std::max(currentMaxFunFactor,
                                   currentModule->parents[0]->funFactor);
    currentModule = currentModule->parents[0];
  }

  if (currentModule->parents.size() == 0) {
    endPoint->maxFun = currentMaxFunFactor;
    return currentMaxFunFactor;
  }

  // If a crossroad is encoutered we return the lowest number. This ensures the
  // highest score
  std::uint64_t minFunFactor = ULLONG_MAX;
  for (auto * module : currentModule->parents) {
    std::uint64_t branchMax = fill_in_max_fun(modules, module);
    minFunFactor = std::min(branchMax, minFunFactor);
  }

  endPoint->maxFun = std::max(minFunFactor, currentMaxFunFactor);
  return std::max(minFunFactor, currentMaxFunFactor);
}

void get_total_score(std::vector<Module> const & modules, Module * endPoint,
                     std::uint64_t & score) {
  Module * currentModule = endPoint;

  // Traverse the parents of the current branch untill we come have a crossroad
  while (currentModule->parents.size() == 1) {
    currentModule = currentModule->parents[0];
  }

  if (currentModule->parents.size() == 0) {
    return;
  }

  // If a crossroad is encoutered we add the score of all the branched except
  // the lowest scoring since this one is already taken into account by the main
  // branch
  auto minParentIt = std::min_element(currentModule->parents.begin(),
                                      currentModule->parents.end(),
    [&](auto const * lhs, auto const * rhs) {return lhs->maxFun < rhs->maxFun;});

  for (auto * module : currentModule->parents) {
    if (module != *minParentIt) {
      score += module->maxFun;
    }

    get_total_score(modules, module, score);
  }
}

int main() {
  {
    timer Timer;

    std::uint32_t testCases;
    std::cin >> testCases;

    for (std::uint32_t t = 0; t < testCases; t++) {
      std::uint32_t nbModules;
      std::cin >> nbModules;

      std::vector<Module> modules(nbModules);
      for (std::size_t j = 0; j < modules.size(); j++) {
        std::cin >> modules[j].funFactor;
      }

      std::vector<Module *> endPoints;

      for (std::size_t j = 0; j < modules.size(); j++) {
        std::size_t childIndex;
        std::cin >> childIndex;

        if (childIndex != 0) {
          modules[childIndex - 1].parents.push_back(&modules[j]);
        } else {
          endPoints.push_back(&modules[j]);
        }
      }

      for (auto * endPoint : endPoints) {
        fill_in_max_fun(modules, endPoint);
      }

      std::uint64_t result = 0;
      for (auto * endPoint : endPoints) {
        // This is the score for the path to the endpoint
        result += endPoint->maxFun;

        // This the score of all the other branches
        get_total_score(modules, endPoint, result);
      }

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << result << '\n';
    }
  }
}
