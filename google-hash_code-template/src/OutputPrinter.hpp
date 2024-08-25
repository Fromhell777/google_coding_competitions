#pragma once

#include "Data.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct OutputPrinter {
  OutputPrinter (std::string const & outputFileName,
                 std::vector<std::string> const & assigneeAttribute0s,
                 std::vector<std::string> const & attribute4Attribute0s,
                 std::vector<std::string> const & taskAttribute0s)
    : outputFileName_(std::move(outputFileName))
    , assigneeAttribute0s_(std::move(assigneeAttribute0s))
    , attribute4Attribute0s_(std::move(attribute4Attribute0s))
    , taskAttribute0s_(std::move(taskAttribute0s))
  { }

  // This is an example of how to print the output
  void print_output (std::vector<Assignee> const & assignees,
                     std::vector<Allocation> const & allocations) const {

    std::ofstream outputFile(outputFileName_);
    if (not outputFile.is_open()) {
      std::cerr << "Failed to open " << outputFileName_ << '\n';
    } else {

      outputFile << allocations.size() << '\n';

      for (auto const & allocation : allocations) {
        outputFile << taskAttribute0s_[allocation.task->attribute0] << '\n';

        for (auto const assigneeIndex : allocation.assigneeIndices) {
          outputFile << assigneeAttribute0s_[assignees[assigneeIndex].attribute0];

          if (assigneeIndex != allocation.assigneeIndices.back()) {
            outputFile << ' ';
          }
        }
        outputFile << '\n';
      }
    }
  }

  // Members
  std::string const outputFileName_;
  std::vector<std::string> const assigneeAttribute0s_;
  std::vector<std::string> const attribute4Attribute0s_;
  std::vector<std::string> const taskAttribute0s_;
};
