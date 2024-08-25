#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

std::string find_mega_tower(std::vector<std::string> & towers) {
  std::string result = "";

  std::vector<std::pair<char, char>> edgeLetters(towers.size());
  for (std::size_t i = 0; i < towers.size(); ++i) {
    edgeLetters[i] = std::make_pair(towers[i].front(), towers[i].back());
  }

  std::vector<std::vector<char>> lettersInside(towers.size());
  for (std::size_t i = 0; i < towers.size(); ++i) {
    auto uniqueTower = towers[i];
    auto last = std::unique(uniqueTower.begin(), uniqueTower.end());
    uniqueTower.erase(last,uniqueTower.end());

    for (std::size_t j = 1; j < uniqueTower.size() - 1; ++j) {
      if (std::find(lettersInside[i].begin(), lettersInside[i].end(),
                    uniqueTower[j]) == lettersInside[i].end()) {
        if (uniqueTower[j] == edgeLetters[i].first or
            uniqueTower[j] == edgeLetters[i].second) {
          return "IMPOSSIBLE";
        }

        lettersInside[i].emplace_back(uniqueTower[j]);
      } else {
        return "IMPOSSIBLE";
      }
    }
  }

  for (std::size_t i = 0; i < towers.size(); ++i) {
    if (edgeLetters[i].first == edgeLetters[i].second and
        lettersInside[i].size() != 0) {
      return "IMPOSSIBLE";
    }

    for (std::size_t j = i + 1; j < towers.size(); ++j) {
      if (edgeLetters[i] == edgeLetters[j] or
          (edgeLetters[i].first == edgeLetters[j].second and
           edgeLetters[i].second == edgeLetters[j].first)) {
        if (edgeLetters[i].first != edgeLetters[i].second) {
          return "IMPOSSIBLE";
        }
      }
    }
  }

  while (not towers.empty()) {
    std::string currentTower = towers[0];
    auto currentEdgeLetters = edgeLetters.front();
    auto currentLettersInside = lettersInside.front();
    towers.erase(towers.begin());
    edgeLetters.erase(edgeLetters.begin());
    lettersInside.erase(lettersInside.begin());

    for (auto const letter : currentTower) {
      for (std::size_t i = 0; i < lettersInside.size(); ++i) {
        for (std::size_t j = 0; j < lettersInside[i].size(); ++j) {
          if (lettersInside[i][j] == letter) {return "IMPOSSIBLE";}
        }
      }
    }

    for (auto const letter : currentLettersInside) {
      for (std::size_t i = 0; i < edgeLetters.size(); ++i) {
        if (edgeLetters[i].first == letter or edgeLetters[i].second == letter) {
          return "IMPOSSIBLE";
        }
      }
    }

    bool appending = true;
    while (appending) {
      appending = false;

      // Check addition at the back
      std::size_t i = 0;
      while (i < edgeLetters.size()) {
        if (currentTower.back() == edgeLetters[i].first and
            edgeLetters[i].first == edgeLetters[i].second) {
          appending = true;
          currentTower += towers[i];
          towers.erase(towers.begin() + i);
          edgeLetters.erase(edgeLetters.begin() + i);
          lettersInside.erase(lettersInside.begin() + i);
        } else {
          ++i;
        }
      }

      i = 0;
      while (i < edgeLetters.size()) {
        if (currentTower.back() == edgeLetters[i].first) {
          if (currentTower.front() == edgeLetters[i].second) {return "IMPOSSIBLE";}

          appending = true;
          currentTower += towers[i];
          auto tmpTower = towers[i];

          currentEdgeLetters = edgeLetters[i];
          currentLettersInside = lettersInside[i];
          currentLettersInside.emplace_back(towers[i].front());

          towers.erase(towers.begin() + i);
          edgeLetters.erase(edgeLetters.begin() + i);
          lettersInside.erase(lettersInside.begin() + i);

          for (auto const letter : tmpTower) {
            for (std::size_t j = 0; j < lettersInside.size(); ++j) {
              for (std::size_t k = 0; k < lettersInside[j].size(); ++k) {
                if (lettersInside[j][k] == letter) {return "IMPOSSIBLE";}
              }
            }
          }

          for (auto const letter : currentLettersInside) {
            for (std::size_t j = 0; j < edgeLetters.size(); ++j) {
              if (edgeLetters[j].first == letter or
                  edgeLetters[j].second == letter) {
                return "IMPOSSIBLE";
              }
            }
          }

          break;

        } else {
          ++i;
        }
      }

      // Check addition at the front
      i = 0;
      while (i < edgeLetters.size()) {
        if (currentTower.front() == edgeLetters[i].first and
            edgeLetters[i].first == edgeLetters[i].second) {
          appending = true;
          currentTower = towers[i] + currentTower;
          towers.erase(towers.begin() + i);
          edgeLetters.erase(edgeLetters.begin() + i);
          lettersInside.erase(lettersInside.begin() + i);
        } else {
          ++i;
        }
      }

      i = 0;
      while (i < edgeLetters.size()) {
        if (currentTower.front() == edgeLetters[i].second) {
          if (currentTower.back() == edgeLetters[i].first) {return "IMPOSSIBLE";}

          appending = true;
          currentTower = towers[i] + currentTower;
          auto tmpTower = towers[i];

          currentEdgeLetters = edgeLetters[i];
          currentLettersInside = lettersInside[i];
          currentLettersInside.emplace_back(towers[i].back());

          towers.erase(towers.begin() + i);
          edgeLetters.erase(edgeLetters.begin() + i);
          lettersInside.erase(lettersInside.begin() + i);

          for (auto const letter : tmpTower) {
            for (std::size_t j = 0; j < lettersInside.size(); ++j) {
              for (std::size_t k = 0; k < lettersInside[j].size(); ++k) {
                if (lettersInside[j][k] == letter) {return "IMPOSSIBLE";}
              }
            }
          }

          for (auto const letter : currentLettersInside) {
            for (std::size_t j = 0; j < edgeLetters.size(); ++j) {
              if (edgeLetters[j].first == letter or
                  edgeLetters[j].second == letter) {
                return "IMPOSSIBLE";
              }
            }
          }

          break;

        } else {
          ++i;
        }
      }
    }

    result += currentTower;

  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t nbTowers;
      std::cin >> nbTowers;

      std::vector<std::string> towers(nbTowers);
      for (auto & tower : towers) {
        std::cin >> tower;
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_mega_tower(towers) << '\n';
    }
  }
}
