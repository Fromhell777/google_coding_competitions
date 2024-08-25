#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

std::string find_minimum_lights(std::size_t const length,
                                std::size_t const radius,
                                std::vector<std::uint32_t> lightPositions) {
  std::size_t result = 0;

  if (lightPositions[0] > radius) {return "IMPOSSIBLE";}

  std::size_t currentPosition = 0;
  std::size_t currentLight    = -1;

  while (currentPosition < length) {

    std::size_t nextLight = currentLight + 1;
    bool foundNextLight = false;

    while ((nextLight < lightPositions.size()) and
           (lightPositions[nextLight] <= currentPosition + radius)) {
      ++nextLight;
      foundNextLight = true;
    }

    if (not foundNextLight) {return "IMPOSSIBLE";}

    currentLight = nextLight - 1;
    currentPosition = lightPositions[currentLight] + radius;
    ++result;
  }


  return std::to_string(result);
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t length;
      std::cin >> length;

      std::size_t radius;
      std::cin >> radius;

      std::size_t nbLights;
      std::cin >> nbLights;

      std::vector<std::uint32_t> lightPositions(nbLights);
      for (std::size_t i = 0; i < lightPositions.size(); ++i) {
        std::cin >> lightPositions[i];
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_minimum_lights(length, radius, lightPositions) << '\n';
    }
  }
}
