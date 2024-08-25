#include "timer.hpp"
#include "prettyprint.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

long double find_optimal_tickets(std::vector<std::uint64_t> & sold_tickets,
                                 std::uint64_t const max_integer)
{
  std::sort(std::begin(sold_tickets), std::end(sold_tickets));
  sold_tickets.erase(std::unique(std::begin(sold_tickets),
                                 std::end(sold_tickets)),
                     sold_tickets.end());

  std::vector<std::uint64_t> scores_single_ticket;

  for (std::size_t i = 0; i < sold_tickets.size(); ++i)
    {
      if (i == 0)
        {
          scores_single_ticket.emplace_back(sold_tickets.front() - 1);
        }

      if (i == sold_tickets.size() - 1)
        {
          scores_single_ticket.emplace_back(max_integer - sold_tickets.back());
        }
      else
        {
          scores_single_ticket.emplace_back((sold_tickets[i + 1] -
                                             sold_tickets[i]) / 2);
        }
    }

  std::sort(scores_single_ticket.begin(), scores_single_ticket.end());

  std::vector<std::uint64_t> scores_double_ticket;

  for (std::size_t i = 0; i < sold_tickets.size() - 1; ++i)
    {
      scores_double_ticket.emplace_back(sold_tickets[i + 1] - sold_tickets[i] - 1);
    }

  std::sort(scores_double_ticket.begin(), scores_double_ticket.end());

  long double max_score;

  if (scores_double_ticket.size() > 0)
    {
      max_score = std::max(scores_single_ticket.back() +
                           scores_single_ticket[scores_single_ticket.size() - 2],
                           scores_double_ticket.back());
    }
  else
    {
      max_score = scores_single_ticket.back() +
                  scores_single_ticket[scores_single_ticket.size() - 2];
    }

  return max_score / max_integer;
}

int main()
{

  {
    timer Timer;

    std::size_t test_cases;
    std::cin >> test_cases;

    for (std::size_t t = 0; t < test_cases; ++t)
      {
        std::size_t number_of_sold_tickets;
        std::cin >> number_of_sold_tickets;

        std::uint64_t max_integer;
        std::cin >> max_integer;

        std::vector<std::uint64_t> sold_tickets(number_of_sold_tickets);

        for (std::size_t i = 0; i < sold_tickets.size(); ++i)
          {
            std::cin >> sold_tickets[i];
          }

        std::cout << "Case #" << t + 1 << ": ";
        std::cout << find_optimal_tickets(sold_tickets, max_integer) << '\n';
      }
  }
}
