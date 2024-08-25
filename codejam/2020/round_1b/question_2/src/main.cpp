#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Point
{
  std::int64_t x;
  std::int64_t y;
};

// Return the point just outside the circle in the result_point argument
// Returns true if the center was found
bool search_edge(Point const & miss_point, Point const & hit_point,
                 bool x_not_y_axes, Point & result_point)
{
  std::int64_t miss_boundary;
  if (x_not_y_axes) {miss_boundary = miss_point.x;}
  else {miss_boundary = miss_point.y;}

  std::int64_t hit_boundary;
  if (x_not_y_axes) {hit_boundary = hit_point.x;}
  else {hit_boundary = hit_point.y;}

  while (std::abs(miss_boundary - hit_boundary) > 1)
    {
      std::int64_t new_boundary = (hit_boundary + miss_boundary) / 2;

      if (x_not_y_axes)
        {
          std::cout << new_boundary << ' ' << hit_point.y << '\n';
        }
      else
        {
          std::cout << hit_point.x << ' ' << new_boundary << '\n';
        }

      std::string response;
      std::getline(std::cin, response);

      if (response == "CENTER") {return true;}
      else if (response == "HIT") {hit_boundary = new_boundary;}
      else {miss_boundary = new_boundary;}
    }

  if (x_not_y_axes)
    {
      result_point.x = miss_boundary;
      result_point.y = hit_point.y;
    }
  else
    {
      result_point.x = hit_point.x;
      result_point.y = miss_boundary;
    }

  return false;
}

bool find_center()
{
  // The radius is always larger than 10e9 / 2.
  // One of these 5 points must be a hit on the Dart Board
  std::vector<Point> starting_points = {{-1000000000 / 2,  1000000000 / 2},
                                        { 1000000000 / 2,  1000000000 / 2},
                                        {              0,               0},
                                        {-1000000000 / 2, -1000000000 / 2},
                                        { 1000000000 / 2, -1000000000 / 2}};

  // Find a point that hits
  Point starting_point;
  bool found_starting_point = false;
  for (auto const & point : starting_points)
    {
      std::cout << point.x << ' ' << point.y << '\n';

      std::string response;
      std::getline(std::cin, response);

      if (response == "CENTER") {return true;}
      else if (response == "HIT")
        {
          found_starting_point = true;
          starting_point = point;
          break;
        }
    }

  if (not found_starting_point) {return false;}

  // Find left edge
  Point left_point = {-1000000000, starting_point.y};

  std::cout << left_point.x << ' ' << left_point.y << '\n';

  std::string response;
  std::getline(std::cin, response);

  if (response == "CENTER") {return true;}
  else if (response == "MISS")
    {
      bool found_center = search_edge(left_point, starting_point, true,
                                      left_point);

      if (found_center) {return true;}
    }

  // Find right edge
  Point right_point = {1000000000, starting_point.y};

  std::cout << right_point.x << ' ' << right_point.y << '\n';

  std::getline(std::cin, response);

  if (response == "CENTER") {return true;}
  else if (response == "MISS")
    {
      bool found_center = search_edge(right_point, starting_point, true,
                                      right_point);

      if (found_center) {return true;}
    }

  // Find up edge
  Point up_point = {starting_point.x, 1000000000};

  std::cout << up_point.x << ' ' << up_point.y << '\n';

  std::getline(std::cin, response);

  if (response == "CENTER") {return true;}
  else if (response == "MISS")
    {
      bool found_center = search_edge(up_point, starting_point, false,
                                      up_point);

      if (found_center) {return true;}
    }

  // Find down edge
  Point down_point = {starting_point.x, -1000000000};

  std::cout << down_point.x << ' ' << down_point.y << '\n';

  std::getline(std::cin, response);

  if (response == "CENTER") {return true;}
  else if (response == "MISS")
    {
      bool found_center = search_edge(down_point, starting_point, false,
                                      down_point);

      if (found_center) {return true;}
    }

  // Response the center
  Point center;
  center.x = (left_point.x + right_point.x) / 2;
  center.y = (up_point.y + down_point.y) / 2;

  std::cout << center.x << ' ' << center.y << '\n';

  std::getline(std::cin, response);

  if (response == "CENTER") {return true;}

  return false;
}

int main()
{

  {
    std::uint64_t test_cases;
    std::cin >> test_cases;

    std::uint64_t min_radius;
    std::cin >> min_radius;

    std::uint64_t max_radius;
    std::cin >> max_radius;

    std::string dummy;
    std::getline(std::cin, dummy); // Dummy read to get rid of the left over '\n'

    for (std::uint64_t t = 0; t < test_cases; ++t)
      {
        bool passed = find_center();

        if (not passed) {break;}
      }
  }
}
