#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Event
{
  Event(std::uint32_t start_time, std::uint32_t end_time,
        std::size_t input_index)
    : start_time(start_time)
    , end_time(end_time)
    , input_index(input_index)
  {
  }

  std::uint32_t start_time;
  std::uint32_t end_time;
  std::size_t input_index;
};

struct Task
{
  Task(std::uint32_t end_time, char resource)
    : end_time(end_time)
    , resource(resource)
  {
  }

  std::uint32_t end_time;
  char resource;
};

std::string find_schedule(std::vector<Event> const & events)
{
  std::string result(events.size(), '*');
  std::vector<char> resources = {'J', 'C'};

  std::vector<Task> tasks;

  for (auto const & event : events)
    {
      // Clear all events that should be finished
      while (tasks.size() > 0 and tasks.begin()->end_time <= event.start_time)
        {
          resources.emplace_back(tasks.begin()->resource);

          tasks.erase(tasks.begin());
        }

      // Report error if no resources are available anymore
      if (resources.size() == 0)
        {
          return "IMPOSSIBLE";
        }

      // Schedule new Task
      tasks.emplace_back(event.end_time, resources.back());

      std::sort(tasks.begin(), tasks.end(),
                [](Task const & lhs, Task const & rhs)
                {
                  return lhs.end_time < rhs.end_time;
                });

      result[event.input_index] = resources.back();

      resources.pop_back();
    }

  return result;
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t numeber_events;
        std::cin >> numeber_events;

        std::vector<Event> events;

        for (std::size_t i = 0; i < numeber_events; ++i)
          {
            std::uint32_t start_time;
            std::uint32_t end_time;
            std::cin >> start_time;
            std::cin >> end_time;

            events.emplace_back(start_time, end_time, i);
          }

        std::sort(events.begin(), events.end(),
                  [](Event const & lhs, Event const & rhs)
                  {
                    return lhs.start_time < rhs.start_time;
                  });

        std::cout << "Case #" << t + 1 << ": " << find_schedule(events) << '\n';
      }
  }
}
