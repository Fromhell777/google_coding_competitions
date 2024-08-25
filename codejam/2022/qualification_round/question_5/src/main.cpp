#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void guess_passages(std::uint32_t const rooms,
                    std::uint32_t const maxOperations) {
  std::uint64_t passageEstimate = 0;

  std::uint64_t room;
  std::uint64_t nbPassages;
  std::cin >> room >> nbPassages;

  passageEstimate += nbPassages;

  std::vector<std::uint64_t> guessRooms;

  std::uint64_t teleports = std::min(rooms, maxOperations);

  for (std::size_t i = 0; i < teleports; i++) {
    if (teleports == rooms) {
      if (i + 1 != room) {
        guessRooms.push_back(i + 1);
      }
    } else {
      guessRooms.push_back(i + 1);
    }
  }

  if (teleports != rooms and room <= guessRooms.size()) {
    guessRooms[room - 1] = guessRooms.size() + 1;
  }

  for (auto const roomNumber : guessRooms) {
    std::cout << "T " << roomNumber << '\n';

    std::cin >> room >> nbPassages;

    passageEstimate += nbPassages;
  }

  // Guess the passages of the other rooms based on the average that we already
  // saw
  double averageRoomPassages = double(passageEstimate) / (guessRooms.size() + 1);
  passageEstimate += (rooms - (guessRooms.size() + 1)) * averageRoomPassages;

  // Every passage is counted twice
  passageEstimate /= 2;

  std::cout << "E " << passageEstimate << '\n';
}

int main()
  {
    //timer Timer;

    std::uint32_t testCases;
    std::cin >> testCases;

    for (std::uint32_t t = 0; t < testCases; t++) {
      std::uint32_t rooms;
      std::cin >> rooms;

      std::uint32_t maxOperations;
      std::cin >> maxOperations;

      guess_passages(rooms, maxOperations);
    }
}
