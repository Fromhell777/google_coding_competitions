#pragma once

#include <cassert>
#include <cstdint>
#include <random>
#include <algorithm>
#include <iterator>

// The function randomizes the contents of a container
template <class InputIt>
void randomize(InputIt startIt, InputIt endIt) {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::shuffle(startIt, endIt, gen);
}
