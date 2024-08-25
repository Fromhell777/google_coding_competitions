#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

class timer {
 public:
   inline timer () : start_(get_time()) { }

   inline ~timer () {
     auto const stop = get_time();
     auto const duration = stop - start_;

     std::cout << "[timer] " << format_duration(duration) << '\n';
   }

   template <class T>
   std::string format_duration (T const & duration) {
     auto const round = [](auto & value) {
       // Round to max 3 digits behind decimal point.
       return std::round(value * 1000) / 1000;
     };

     auto const generate_string = [&](double value, std::string const & abbrev) {
       std::string result = std::to_string(round(value));

       // Remove extraneous fractional digits
       auto const dotPos = result.find('.');
       constexpr static std::size_t c_FracLength = 3;
       if ((dotPos != std::string::npos)
           and (dotPos + c_FracLength + 1 < result.size())) {
         result.erase(dotPos + c_FracLength + 1);
       }

       return result + " " + abbrev;
     };

     std::array<std::string, 5> const abbrevs = {{ "ns", "us", "ms", "s", "m" }};
     std::array<double, 5> const divisors = {{ 1'000, 1'000, 1'000, 60, 1 }};

     double count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

     for (std::size_t index = 0; index < abbrevs.size(); ++index) {
       if (count < divisors[index]) { return generate_string(count, abbrevs[index]); }
       count /= divisors[index];
     }

     return generate_string(count, abbrevs.back());
   }

 private:
   using time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
   using print_t = std::chrono::nanoseconds;

   time_t const start_;

   inline static time_t get_time () {
     return std::chrono::high_resolution_clock::now();
   }
};
