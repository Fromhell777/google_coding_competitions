#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <cctype>

std::string find_new_password(std::string const & password) {
  bool uppercase = false;
  bool lowercase = false;
  bool digit     = false;
  bool special   = false;

  for (auto const letter : password) {
    if (std::isupper(letter)) {
      uppercase = true;
    }
    if (std::islower(letter)) {
      lowercase = true;
    }
    if (std::isdigit(letter)) {
      digit = true;
    }

    if (letter == '&' or letter == '#' or letter == '*' or letter == '@') {
      special = true;
    }
  }

  std::string result = password;

  if (not uppercase) {
    result += 'A';
  }
  if (not lowercase) {
    result += 'a';
  }
  if (not digit) {
    result += '1';
  }

  if (not special) {
    result += '@';
  }

  if (result.size() < 7) {
    result += std::string(7 - result.size(), '0');
  }

  return result;
}

int main() {
  {
    timer Timer;

    std::size_t testCases;
    std::cin >> testCases;

    for (std::size_t t = 0; t < testCases; ++t) {
      std::size_t string_size;
      std::cin >> string_size;

      std::string password;
      std::cin >> password;

      std::cout << "Case #" << t + 1 << ": ";
      std::cout << find_new_password(password) << "\n";
    }
  }
}
