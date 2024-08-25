#if defined(USE_SPDLOG)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#else
#define SPDLOG_TRACE(...)
#define SPDLOG_DEBUG(...)
#define SPDLOG_INFO(...)
#define SPDLOG_WARN(...)
#define SPDLOG_ERROR(...)
#endif

#include "Data.hpp"
#include "Solver.hpp"
#include "Estimator.hpp"
#include "OutputPrinter.hpp"
#include "randomize.tpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>

void simple_solve(std::vector<Assignee> const & assignees,
                  std::vector<Task> const & tasks,
                  OutputPrinter const & outputPrinter) {
  // Solve the problem
  Solver solver(assignees, tasks);
  auto const result = solver.solveScheduling();

  // Print the output
  outputPrinter.print_output(assignees, result);

  Estimator estimator(assignees, tasks);
  std::int64_t result_score = estimator.estimateScheduling(result);

  // Estimate the output score
  std::cerr << "Estimator result score: " << result_score << '\n';
}

void random_solve(std::vector<Assignee> assignees,
                  std::vector<Task> tasks,
                  OutputPrinter const & outputPrinter,
                  std::uint32_t const iterations) {

  // Loop with randomized data
  std::int64_t  best_score = 0;
  for (std::size_t i = 0; i < iterations; ++i) {

    // Randomize some of the data
    randomize(assignees.begin(), assignees.end());
    for (auto & assignee : assignees) {
      randomize(assignee.attribute4s.begin(), assignee.attribute4s.end());
    }

    // Solve the problem
    Solver randomized_solver(assignees, tasks);
    auto const random_result = randomized_solver.solveScheduling();

    Estimator estimator(assignees, tasks);
    std::int64_t current_score = estimator.estimateScheduling(random_result);

    if (current_score > best_score) {
      // Print the output
      outputPrinter.print_output(assignees, random_result);
      best_score = current_score;
    }

    // Estimate the output score
    std::cerr << "Estimator current score: " << current_score << '\n';
    std::cerr << "Estimator best score: " << best_score << '\n';
  }
}

int main (int argc, char * argv[]) {
#if defined(USE_SPDLOG)
  spdlog::set_default_logger(spdlog::stderr_color_st("cerr"));
  spdlog::set_level(spdlog::level::debug);
#endif

  // Parse the input arguments
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << "OUTPUT_DIR" << std::endl;
    return 1;
  }

  std::string outputFileName = argv[1];

  // Get the assignees
  // These will be assigned to tasks
  int nbAssignees;
  std::cin >> nbAssignees;

  // Get the tasks
  // Assignees will be allocated to these tasks
  int nbTasks;
  std::cin >> nbTasks;

  // Define maps that map the strings to integers for faster execution
  std::unordered_map<std::string, std::uint32_t> assigneeAttribute0Map;
  std::unordered_map<std::string, std::uint32_t> attribute4Attribute0Map;

  // Extract all the info of the assignees
  std::vector<Assignee> assignees(nbAssignees);
  for (auto & assignee : assignees)
    {
      // Extract an attribute
      std::string attribute0;
      std::cin >> attribute0;
      // Build the map for the string attribute for faster execution
      if (not assigneeAttribute0Map.contains(attribute0))
        {
          assigneeAttribute0Map[attribute0] = assigneeAttribute0Map.size();
        }

      assignee.attribute0 = assigneeAttribute0Map[attribute0];

      // Extract a list of attributes
      int attributeListSize;
      std::cin >> attributeListSize;

      assignee.attribute4s.resize(attributeListSize);

      for (auto & elem : assignee.attribute4s)
        {
          std::string attribute1;
          int attribute2;
          std::cin >> attribute1 >> attribute2;

          // Build the map for the string attribute for faster execution
          if (not attribute4Attribute0Map.contains(attribute1))
            {
              attribute4Attribute0Map[attribute1] = attribute4Attribute0Map.size();
            }

          elem.attribute0 = attribute4Attribute0Map[attribute1];
          elem.attribute1 =  attribute2;
        }
    }

  // Define maps that map the strings to integers for faster execution
  std::unordered_map<std::string, std::uint32_t> taskAttribute0Map;

  std::vector<Task> tasks(nbTasks);
  for (auto & task : tasks)
    {
      // Extract some attributes
      std::string attribute0;
      int attribute1;
      int attribute2;
      int attribute3;

      std::cin >> attribute0 >> attribute1 >> attribute2 >> attribute3;

      // Build the map for the string attribute for faster execution
      if (not taskAttribute0Map.contains(attribute0))
        {
          taskAttribute0Map[attribute0] = taskAttribute0Map.size();
        }

      task.attribute0 = taskAttribute0Map[attribute0];
      task.attribute1 = attribute1;
      task.attribute2 = attribute2;
      task.attribute3 = attribute3;

      // Extract a list of attributes
      int attributeListSize;
      std::cin >> attributeListSize;

      task.attribute4s.resize(attributeListSize);

      for (auto & elem : task.attribute4s)
        {
          std::string attribute4;
          int attribute5;

          std::cin >> attribute4 >> attribute5;

          // Build the map for the string attribute for faster execution
          if (not attribute4Attribute0Map.contains(attribute4))
            {
              attribute4Attribute0Map[attribute4] = attribute4Attribute0Map.size();
            }

          elem.attribute0 = attribute4Attribute0Map[attribute4];
          elem.attribute1 = attribute5;
        }
    }

  // Create vector of the strings where the index corresonds to the map number.
  // This is mostly needed for printing the result afterwards
  std::vector<std::string> assigneeAttribute0s(assigneeAttribute0Map.size());
  for (auto const & attribute0Map : assigneeAttribute0Map)
    {
      assigneeAttribute0s[attribute0Map.second] = attribute0Map.first;
    }

  std::vector<std::string> attribute4Attribute0s(attribute4Attribute0Map.size());
  for (auto const & attribute0Map : attribute4Attribute0Map)
    {
      attribute4Attribute0s[attribute0Map.second] = attribute0Map.first;
    }

  std::vector<std::string> taskAttribute0s(taskAttribute0Map.size());
  for (auto const & attribute0Map : taskAttribute0Map)
    {
      taskAttribute0s[attribute0Map.second] = attribute0Map.first;
    }

  // Initiate the Output Printer
  OutputPrinter outputPrinter(outputFileName, assigneeAttribute0s,
                              attribute4Attribute0s, taskAttribute0s);

  //////////////////
  // Simple solve //
  //////////////////

  simple_solve(assignees, tasks, outputPrinter);

  //////////////////////
  // Randomized solve //
  //////////////////////

  std::uint32_t iterations = 100;
  random_solve(assignees, tasks, outputPrinter, iterations);
}
