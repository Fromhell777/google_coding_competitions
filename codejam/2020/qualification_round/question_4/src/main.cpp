#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool get_bit(std::size_t position)
{
  std::cout << position << '\n';

  bool recieved_bit;
  std::cin >> recieved_bit;

  return recieved_bit;
}

void transform(std::vector<bool> & bits, bool do_inverse, bool do_flip)
{
  if (do_inverse)
    {
      for (std::size_t i = 0; i < bits.size(); ++i)
        {
          bits[i] = not bits[i];
        }
    }

  if (do_flip)
    {
      std::reverse(bits.begin(), bits.end());
    }
}

void resolve_fluctuation(std::vector<bool> & bits,
                                std::int32_t equal_position,
                                bool & expected_equal,
                                std::int32_t inverse_position,
                                bool & expected_inverse)
{
  bool do_inverse = false;
  bool do_flip    = false;

  if (equal_position != -1)
    {
      bool recieved_bit = get_bit(equal_position + 1);

      if (recieved_bit != expected_equal)
        {
          expected_equal = recieved_bit;
          do_inverse = true;
        }
    }
  else
    {
      // Even when no querry is needed a querry is done. This is to align the amount
      // of querries to an even number
      (void) get_bit(1);
    }

  if (inverse_position != -1)
    {

      bool recieved_bit = get_bit(inverse_position + 1);

      if (recieved_bit != expected_inverse)
        {
          expected_inverse = recieved_bit;
          do_flip = not do_inverse;
        }
      else
        {
          do_flip = do_inverse;
        }
    }
  else
    {
      // Even when no querry is needed a querry is done. This is to align the amount
      // of querries to an even number
      (void) get_bit(1);
    }

  transform(bits, do_inverse, do_flip);
}

std::string find_bits(std::size_t number_bits)
{
  std::int32_t equal_position = -1;
  bool expected_equal = 0;

  std::int32_t inverse_position = -1;
  bool expected_inverse = 0;

  std::vector<bool> bits(number_bits);

  std::size_t querry_number = 0;

  for (std::size_t i = 0; i < number_bits / 2; ++i)
    {
      if (querry_number == 10)
        {
          resolve_fluctuation(bits, equal_position, expected_equal,
                              inverse_position, expected_inverse);
          querry_number = 2;
        }

      bool recieved_bit = get_bit(i + 1);
      bits[i] = recieved_bit;
      ++querry_number;

      recieved_bit = get_bit(number_bits - i);
      bits[number_bits - i - 1] = recieved_bit;
      ++querry_number;

      if (equal_position == -1 and bits[i] == bits[number_bits - i - 1])
        {
          equal_position = i;
          expected_equal = bits[i];
        }

      if (inverse_position == -1 and bits[i] != bits[number_bits - i - 1])
        {
          inverse_position = i;
          expected_inverse = bits[i];
        }

    }

  // Get the center bit for when the number of bits is uneven
  if ((number_bits % 2) == 1)
    {
      if (querry_number == 10)
        {
          resolve_fluctuation(bits, equal_position, expected_equal,
                              inverse_position, expected_inverse);
        }

      bool recieved_bit = get_bit(number_bits / 2 + 1);
      bits[number_bits / 2] = recieved_bit;
    }

  std::string result;
  for (auto const bit : bits)
    {
      if (bit) {result += '1';}
      else {result += '0';}
    }

  return result;
}

int main()
{

  {
    std::size_t test_cases;
    std::cin >> test_cases;

    std::size_t number_bits;
    std::cin >> number_bits;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::string bits = find_bits(number_bits);
        std::cout << bits << '\n';

        char result;
        std::cin >> result;

        std::cerr << "result: " << result << '\n';
        if (result != 'Y')
          {
            break;
          }
      }
  }
}
