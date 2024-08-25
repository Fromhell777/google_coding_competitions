#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

void print_punch_card(std::uint32_t const rows, std::uint32_t columns) {
  for (std::uint32_t i = 0; i < 2 * rows + 1; i++) {
    for (std::uint32_t j = 0; j < 2 * columns + 1; j++) {
      if (i < 2 && j < 2) {
        std::cout << '.';
        continue;
      }

      if (i % 2 == 0) {
        if (j % 2 == 0) {
          std::cout << '+';
        } else {
          std::cout << '-';
        }
      } else {
        if (j % 2 == 0) {
          std::cout << '|';
        } else {
          std::cout << '.';
        }
      }
    }
    std::cout << '\n';
  }
}

int main() {
  {
    timer Timer;

    std::uint32_t testCases;
    std::cin >> testCases;

    for (std::uint32_t t = 0; t < testCases; t++) {
      std::uint32_t rows;
      std::cin >> rows;

      std::uint32_t columns;
      std::cin >> columns;

      std::cout << "Case #" << t + 1 << ":\n";
      print_punch_card(rows, columns);
    }
  }
}
