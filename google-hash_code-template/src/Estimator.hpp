#pragma once

#include "Data.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Estimator {
  Estimator (std::vector<Assignee> assignees,
             std::vector<Task> tasks)
    : assignees_(std::move(assignees))
    , tasks_(std::move(tasks))
  { }

  // This is an example of a solver for a pure assignement problem
  std::int64_t estimateAssignment (std::vector<Allocation> const & executed_tasks) {

    // Calculate the the total score
    std::int64_t result = 0;

    for (auto const & executed_task : executed_tasks) {
      // Calculate some score metric for every task
      for (auto const assigneeIndex : executed_task.assigneeIndices) {

        for (auto const & attribute4 : assignees_[assigneeIndex].attribute4s) {
          result += attribute4.attribute1;
        }
      }
    }

    return result;
  }

  // This is an example of a Estimating the score for a scheduling problem
  std::int64_t estimateScheduling (std::vector<Allocation> const & executed_tasks) const {

    // Calculate the the total score
    std::int64_t result = 0;

    // Keep track of the time the assignees are available again
    std::vector<std::uint64_t> availableTimeAssignees(assignees_.size(), 0);

    // Keep track of the assignees throughout the simulation
    std::vector<Assignee> simAssignees(assignees_);

    for (auto const & executed_task : executed_tasks) {
      auto * task = executed_task.task;

      // Check if the assignees are unique
      std::vector<std::size_t> copyAssignees(executed_task.assigneeIndices);
      std::sort(copyAssignees.begin(), copyAssignees.end());
      auto const duplicateIt = std::adjacent_find(copyAssignees.begin(),
                                                  copyAssignees.end());
      if (duplicateIt != copyAssignees.end()) {
        std::cerr << "Duplicate assignee found for the task\n";
        return 0;
      }

      // Keep track of the latest starting date for the task
      int taskStartTime = 0;

      std::vector<bool> can_mentor(executed_task.assigneeIndices.size(), false);

      // Check if the assignees can be allocated to the task
      for (std::size_t i = 0; i < executed_task.assigneeIndices.size(); ++i) {
        auto const & assignee = simAssignees[executed_task.assigneeIndices[i]];
        auto const & attribute4 = task->attribute4s[i];

        // Check if the assignee has the required attribute4
        auto attribute4It = std::find_if(assignee.attribute4s.begin(), assignee.attribute4s.end(),
          [&](auto const & e) {
            return (e.attribute0 == attribute4.attribute0);
          });

        if (attribute4It == assignee.attribute4s.end() and
            attribute4.attribute1 != 1) {
          std::cerr << "Error Assignee cannot do the allocated task because it lacks the skill\n";
          return 0;
        }

        // Update the latest starting time for the task
        taskStartTime = std::max<int>(taskStartTime,
                                      availableTimeAssignees[executed_task.assigneeIndices[i]]);

        // Check if the assignee can mentor for any other attribute4s.
        for (std::size_t j = 0; j < task->attribute4s.size(); ++j) {
          auto const & otherAttribute4 = task->attribute4s[j];

          // Skip attribute4 we just searched for.
          if (i == j) {continue;}

          // Check if assignee can mentor otherAttribute4.
          auto attribute4It = std::find_if(assignee.attribute4s.begin(), assignee.attribute4s.end(),
            [&](auto const & e) {
              return (e.attribute0 == otherAttribute4.attribute0) and
                     (e.attribute1 >= otherAttribute4.attribute1);
            });

          // Can mentor!
          if (attribute4It != assignee.attribute4s.end()) {
            can_mentor.at(j) = true;
          }
        }
      }

      // Check if the assignees have enough attribute4s and update that value
      for (std::size_t i = 0; i < executed_task.assigneeIndices.size(); ++i) {
        auto & assignee = simAssignees[executed_task.assigneeIndices[i]];
        auto const & attribute4 = task->attribute4s[i];

        // Check if the assignee has enough attribute1 of attribute4
        auto attribute4It = std::find_if(assignee.attribute4s.begin(), assignee.attribute4s.end(),
          [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

        if (attribute4It == assignee.attribute4s.end() and
            can_mentor.at(i) >= attribute4.attribute1) {
          assignee.attribute4s.push_back(attribute4);
        } else if (attribute4It != assignee.attribute4s.end() and
                   (attribute4It->attribute1 + can_mentor.at(i)) >= attribute4.attribute1) {
            attribute4It->attribute1 += 1;
        } else {
          std::cerr << "Error Assignee has not enough level in the skill for this task\n";
          return 0;
        }
      }

      // Update the time when the assignees will be available again
      for (auto const assigneeIndex : executed_task.assigneeIndices) {
        availableTimeAssignees[assigneeIndex] = taskStartTime + task->attribute1;
      }

      // Calculate task score
      result += task_score(task, taskStartTime);
    }

    return result;
  }

  static int task_score (Task const * task, int current_time) {
    int end_date = current_time + task->attribute1;
    int days_too_late = std::max(0, end_date - task->attribute3);
    return task->attribute2 - std::min(task->attribute2, days_too_late);
  }

  // Members
  std::vector<Assignee> assignees_;
  std::vector<Task> tasks_;
};
