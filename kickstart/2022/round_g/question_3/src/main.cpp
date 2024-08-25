#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

std::uint64_t find_happy_arrays(std::vector<std::int64_t> & data) {
  std::uint64_t result = 0;

  std::vector<std::size_t> maxHappySizes(data.size(), 1);
  std::vector<std::int64_t> happySums = data;

  // Override happy end values in the data vector

  for (std::int32_t i = data.size() - 1; i >= 0; --i) {
    if (data[i] < 0) {continue;}

    std::int64_t currentSum = data[i];

    std::size_t j = i + 1;
    while (j < data.size() and
           currentSum + data[j] >= 0) {
      happySums[i] += currentSum * maxHappySizes[j] + happySums[j];
      currentSum += data[j];
      j += maxHappySizes[j];
    }

    maxHappySizes[i] = j - i;
    data[i] = currentSum;
    result += happySums[i];
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t arraySize;
      std::cin >> arraySize;

      std::vector<std::int64_t> data(arraySize);

      for (std::size_t i = 0; i < data.size(); ++i) {
        std::cin >> data[i];
      }

      std::cout << "Case #" << t + 1 << ": "
                << find_happy_arrays(data) << "\n";
    }
  }
}
