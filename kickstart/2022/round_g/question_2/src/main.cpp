#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Stone {
  std::int32_t x;
  std::int32_t y;
  bool redNotYellow;
};

std::string find_score(std::vector<Stone> & stones,
                       std::uint32_t const stoneRadius,
                       std::uint32_t const houseRadius) {

  std::sort(stones.begin(), stones.end(),
    [](Stone const & lhs, Stone const & rhs) -> bool {
      return (lhs.x * lhs.x) + (lhs.y * lhs.y) < (rhs.x * rhs.x) + (rhs.y * rhs.y);
    });

  if (stones.size() == 0) {return "0 0";}

  std::size_t score = 0;
  bool winningTeam = stones[0].redNotYellow;
  for (auto const & stone : stones) {
    if ((houseRadius + stoneRadius) * (houseRadius + stoneRadius) <
        static_cast<std::uint32_t>(stone.x * stone.x + stone.y * stone.y)) {
      break;
    }

    if (stone.redNotYellow == winningTeam) {
      ++score;
    } else {break;}
  }

  if (winningTeam) {return std::to_string(score) + " 0";}
  else {return "0 " + std::to_string(score);}
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::uint32_t stoneRadius;
      std::cin >> stoneRadius;

      std::uint32_t houseRadius;
      std::cin >> houseRadius;

      std::size_t numRedStones;
      std::cin >> numRedStones;

      std::vector<Stone> stones;

      for (std::size_t i = 0; i < numRedStones; ++i) {
        std::int32_t x;
        std::cin >> x;

        std::int32_t y;
        std::cin >> y;

        stones.push_back({x, y , true});
      }

      std::size_t numYellowStones;
      std::cin >> numYellowStones;

      for (std::size_t i = 0; i < numYellowStones; ++i) {
        std::int32_t x;
        std::cin >> x;

        std::int32_t y;
        std::cin >> y;

        stones.push_back({x, y , false});
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_score(stones, stoneRadius, houseRadius) << '\n';
    }
  }
}
