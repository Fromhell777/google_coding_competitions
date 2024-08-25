#pragma once

#include "Data.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <iterator>

struct Solver {
  Solver (std::vector<Assignee> assignees,
          std::vector<Task> tasks)
    : assignees_(std::move(assignees))
    , tasks_(std::move(tasks))
  { }

  // This is an example of a solver for a pure assignement problem
  std::vector<Allocation> solveAssignment () {

    std::vector<Allocation> executed_tasks;

    // Loop over tasks and check if they can be executed.
    for (auto & task : tasks_) {
      std::vector<std::size_t> selected_assignees;
      auto can_mentor = std::vector<bool>(task.attribute4s.size(), false);

      // Check if we have assignees with correct attribute4 for this.
      std::size_t attribute4_index = 0;

      for (auto const & attribute4 : task.attribute4s) {
        auto assigneeIt = std::find_if(assignees_.begin(), assignees_.end(),
          [&](auto & assignee) {
            auto const & attribute4s = assignee.attribute4s;
            auto attribute4It = std::find_if(attribute4s.begin(), attribute4s.end(),
              [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

            if (attribute4It == attribute4s.end()) {return false;}
            return (attribute4It->attribute1 + can_mentor.at(attribute4_index)) >= attribute4.attribute1;
          });

        if (assigneeIt == assignees_.end()) {
          // No one found, give up.
          break;
        }

        // Found someone, now check if he can mentor for any other attribute4s.
        for (std::size_t i = 0; i < task.attribute4s.size(); ++i) {
          auto const & otherAttribute4 = task.attribute4s[i];

          // Skip attribute4 we just searched for.
          if (i == selected_assignees.size()) {continue;}

          // Check if assignee can mentor otherAttribute4.
          auto attribute4It = std::find_if((*assigneeIt).attribute4s.begin(), (*assigneeIt).attribute4s.end(),
            [&](auto const & e) {
              return (e.attribute0 == otherAttribute4.attribute0) and
                     (e.attribute1 >= otherAttribute4.attribute1);
            });

          // Can mentor!
          if (attribute4It != (*assigneeIt).attribute4s.end()) {
            can_mentor.at(i) = true;
          }
        }

        selected_assignees.push_back(std::distance(assignees_.begin(), assigneeIt));

        attribute4_index += 1;
      }

      if (selected_assignees.size() != task.attribute4s.size()) {
        // Nothing found. Try next task.
        continue;
      }

      // Add task/assignees to list of executed tasks
      executed_tasks.push_back({&task, selected_assignees});
    }

    return executed_tasks;
  }

  // This is an example of a solver for a scheduling problem
  std::vector<Allocation> solveScheduling () {

    std::vector<Allocation> executed_tasks;

    std::vector<Task *> available_tasks;
    for (auto & e : tasks_) {available_tasks.push_back(&e);}

    std::vector<Assignee *> available_assignees;
    for (auto & e : assignees_) {available_assignees.push_back(&e);}

    std::unordered_map<Assignee *, int> busy_assignees;

    // Increase the time jump till the first task is done
    int min_time_jump = 1;

    for (int current_time = 0; ; current_time += min_time_jump) {
      // Sort tasks by attribute2/attribute1.
      // Here you could use different sorting functions
      sort_tasks1(available_tasks, current_time);

      // Get rid of tasks with zero (or less) of attribute2.
      auto attribute2It = std::find_if(available_tasks.begin(), available_tasks.end(),
        [&](auto * task) {return task_score(*task, current_time) <= 0;});
      if (attribute2It != available_tasks.end()) {
        available_tasks.erase(attribute2It, available_tasks.end());
      }

      // Rember tasks to remove
      std::vector<Task *> removeTasks;

      // Loop over tasks and check if they can be executed.
      for (auto * task : available_tasks) {
        std::vector<Assignee *> selected_assignees;
        auto can_mentor = std::vector<bool>(task->attribute4s.size(), false);

        // Check if we have assignees with correct attribute4 for this.
        std::size_t attribute4_index = 0;

        for (auto const & attribute4 : task->attribute4s) {

          // Take the assignee that is of the lowest attribute4
          std::unordered_map<Assignee *, int> possible_assignees;
          for (auto * assignee : available_assignees) {
            auto const & attribute4s = assignee->attribute4s;
            auto attribute4It = std::find_if(attribute4s.begin(), attribute4s.end(),
              [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

            if (attribute4It == attribute4s.end()) {
              if (can_mentor.at(attribute4_index) >= attribute4.attribute1) {
                possible_assignees[assignee] = 0;
              }
            } else {
              if ((attribute4It->attribute1 + can_mentor.at(attribute4_index)) >= attribute4.attribute1) {
                possible_assignees[assignee] = attribute4It->attribute1;
              }
            }
          }

          if (possible_assignees.empty()) {
            // No one found, give up.
            break;
          }

          auto minAssigneeIt = std::min_element(possible_assignees.begin(), possible_assignees.end(),
            [](auto const & lhs, auto const & rhs) {return lhs.second < rhs.second;});

          auto assigneeIt = std::find_if(available_assignees.begin(), available_assignees.end(),
            [&](auto * assignee) {
              return (minAssigneeIt->first == assignee);
            });

          // Take the first assignee that has enough attribute4
          //auto assigneeIt = std::find_if(available_assignees.begin(), available_assignees.end(),
          //  [&](auto * assignee) {
          //    auto const & attribute4s = assignee->attribute4s;
          //    auto attribute4It = std::find_if(attribute4s.begin(), attribute4s.end(),
          //      [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

          //    if (attribute4It == attribute4s.end()) {
          //      return can_mentor.at(attribute4_index) >= attribute4.attribute1;
          //    } else {
          //      return (attribute4It->attribute1 + can_mentor.at(attribute4_index)) >= attribute4.attribute1;
          //    }
          //  });

          //if (assigneeIt == available_assignees.end()) {
          //  // No one found, give up.
          //  break;
          //}

          // Found someone, now check if he can mentor for any other attribute4s.
          for (std::size_t i = 0; i < task->attribute4s.size(); ++i) {
            auto const & otherAttribute4 = task->attribute4s[i];

            // Skip attribute4 we just searched for.
            if (i == selected_assignees.size()) {continue;}

            // Check if assignee can mentor otherAttribute4.
            auto attribute4It = std::find_if((*assigneeIt)->attribute4s.begin(), (*assigneeIt)->attribute4s.end(),
              [&](auto const & e) {
                return (e.attribute0 == otherAttribute4.attribute0) and
                       (e.attribute1 >= otherAttribute4.attribute1);
              });

            // Can mentor!
            if (attribute4It != (*assigneeIt)->attribute4s.end()) {
              can_mentor.at(i) = true;
            }
          }

          selected_assignees.push_back(*assigneeIt);
          available_assignees.erase(assigneeIt);

          attribute4_index += 1;
        }

        if (selected_assignees.size() != task->attribute4s.size()) {
          // Nothing found, put selected_assignees back into
          // available_assignees.
          for (auto * e : selected_assignees) {available_assignees.push_back(e);}

          // Try next task.
          continue;
        }

        // Remember taks to remove
        removeTasks.push_back(task);

        // Add task/assignees to list of executed tasks
        executed_tasks.push_back({task, {}});
        for (auto * e : selected_assignees) {
          executed_tasks.back().assigneeIndices.emplace_back(std::distance(assignees_.data(), e));
        }

        // Add people to map of busy people
        for (auto * e : selected_assignees) {busy_assignees[e] = task->attribute1;}

        // Increase attribute4 for selected assignees who's attribute4 will increase after the task finishes
        for (std::size_t i = 0; i < task->attribute4s.size(); ++i) {
          auto const & attribute4 = task->attribute4s.at(i);
          auto * assignee = selected_assignees.at(i);

          auto it = std::find_if(assignee->attribute4s.begin(), assignee->attribute4s.end(),
            [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

          // The assignee gained a new attribute4
          if (it == assignee->attribute4s.end()) {
            assignee->attribute4s.push_back(attribute4);
          } else if (attribute4.attribute1 >= it->attribute1) {
            it->attribute1 += 1;
          }
        }
      }

      // Remove task from available tasks
      for (auto const * task : removeTasks) {
        available_tasks.erase(
          std::remove(available_tasks.begin(), available_tasks.end(), task),
          available_tasks.end());
      }

      // If no one is busy, then there's no active tasks, so stop searching.
      if (busy_assignees.empty()) {break;}

      // Loop over active assignees and subtract minimum days from remaining time.
      std::vector<Assignee *> assignees_to_make_available;
      min_time_jump = get_min_time_jump(busy_assignees);
      for (auto & kv : busy_assignees) {
        kv.second -= min_time_jump;
        if (kv.second == 0) {
          assignees_to_make_available.push_back(kv.first);
        }
      }

      // If 0 days active remaining, make available again.
      for (auto * e : assignees_to_make_available) {
        available_assignees.push_back(e);
        busy_assignees.erase(e);
      }

    }

    // Return the allocations
    return executed_tasks;
  }

  // This is an example of a solver for a scheduling problem
  std::vector<Allocation> solveScheduling2 () {

    std::vector<Allocation> executed_tasks;

    std::vector<Task *> available_tasks;
    for (auto & e : tasks_) {available_tasks.push_back(&e);}

    std::vector<Assignee *> available_assignees;
    for (auto & e : assignees_) {available_assignees.push_back(&e);}

    std::unordered_map<Assignee *, int> busy_assignees;

    std::size_t nbConcurentTasks = 1;

    // Increase the time jump till all the tasks are done
    int max_time_jump = 1;

    for (int current_time = 0; ; current_time += max_time_jump) {

      // Get rid of tasks with zero (or less) score.
      // Rember tasks to remove
      std::vector<Task *> removeTasks;
      for (auto * task : available_tasks) {
        if (task_score(*task, current_time) <= 0) {removeTasks.push_back(task);}
      }

      // Remove task from available tasks
      for (auto const * task : removeTasks) {
        available_tasks.erase(
          std::remove(available_tasks.begin(), available_tasks.end(), task),
          available_tasks.end());
      }

      if (available_tasks.empty()) {
        // No tasks left
        break;
      }

      for (std::size_t t = 0; t < nbConcurentTasks; t++) {
        // get the task with the largest assignee attribute4 growth
        auto * task = get_best_task(available_tasks, available_assignees,
                                    current_time);

        // Execute the task
        std::vector<Assignee *> selected_assignees;
        auto can_mentor = std::vector<bool>(task->attribute4s.size(), false);

        // Check if we have assignees with correct attribute4 for this.
        std::size_t attribute4_index = 0;

        for (auto const & attribute4 : task->attribute4s) {

          // Take the assignee that is of the lowest attribute4
          std::unordered_map<Assignee *, int> possible_assignees;
          for (auto * assignee : available_assignees) {
            auto const & attribute4s = assignee->attribute4s;
            auto attribute4It = std::find_if(attribute4s.begin(), attribute4s.end(),
              [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

            if (attribute4It == attribute4s.end()) {
              if (can_mentor.at(attribute4_index) >= attribute4.attribute1) {
                possible_assignees[assignee] = 0;
              }
            } else {
              if ((attribute4It->attribute1 + can_mentor.at(attribute4_index)) >= attribute4.attribute1) {
                possible_assignees[assignee] = attribute4It->attribute1;
              }
            }
          }

          if (possible_assignees.empty()) {
            // No one found, give up.
            break;
          }

          auto minAssigneeIt = std::min_element(possible_assignees.begin(), possible_assignees.end(),
            [](auto const & lhs, auto const & rhs) {return lhs.second < rhs.second;});

          auto assigneeIt = std::find_if(available_assignees.begin(), available_assignees.end(),
            [&](auto * assignee) {
              return (minAssigneeIt->first == assignee);
            });

          // Found someone, now check if he can mentor for any other attribute4s.
          for (std::size_t i = 0; i < task->attribute4s.size(); ++i) {
            auto const & otherAttribute4 = task->attribute4s[i];

            // Skip attribute4 we just searched for.
            if (i == selected_assignees.size()) {continue;}

            // Check if assignee can mentor otherAttribute4.
            auto attribute4It = std::find_if((*assigneeIt)->attribute4s.begin(), (*assigneeIt)->attribute4s.end(),
              [&](auto const & e) {
                return (e.attribute0 == otherAttribute4.attribute0) and
                       (e.attribute1 >= otherAttribute4.attribute1);
              });

            // Can mentor!
            if (attribute4It != (*assigneeIt)->attribute4s.end()) {
              can_mentor.at(i) = true;
            }
          }

          selected_assignees.push_back(*assigneeIt);
          available_assignees.erase(assigneeIt);

          attribute4_index += 1;
        }

        if (selected_assignees.size() != task->attribute4s.size()) {
          // Nothing found, put selected_assignees back into
          // available_assignees.
          for (auto * e : selected_assignees) {available_assignees.push_back(e);}

          // Try next task.
          continue;
        }

        // Remove task from available tasks
        available_tasks.erase(
          std::remove(available_tasks.begin(), available_tasks.end(), task),
          available_tasks.end());

        // Add task/assignees to list of executed tasks
        executed_tasks.push_back({task, {}});
        for (auto * e : selected_assignees) {
          executed_tasks.back().assigneeIndices.emplace_back(std::distance(assignees_.data(), e));
        }

        // Add people to map of busy people
        for (auto * e : selected_assignees) {busy_assignees[e] = task->attribute1;}

        // Increase attribute4 for selected assignees who's attribute4 will increase after the task finishes
        for (std::size_t i = 0; i < task->attribute4s.size(); ++i) {
          auto const & attribute4 = task->attribute4s.at(i);
          auto * assignee = selected_assignees.at(i);

          auto it = std::find_if(assignee->attribute4s.begin(), assignee->attribute4s.end(),
            [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

          // The assignee gained a new attribute4
          if (it == assignee->attribute4s.end()) {
            assignee->attribute4s.push_back(attribute4);
          } else if (attribute4.attribute1 >= it->attribute1) {
            it->attribute1 += 1;
          }
        }
      }

      // If no one is busy, then there's no active tasks, so stop searching.
      if (busy_assignees.empty()) {break;}

      // Loop over busy assignees and make them available again. We wait for the
      // longest task to finish
      max_time_jump = get_max_time_jump(busy_assignees);
      for (auto & e : busy_assignees) {
        available_assignees.push_back(e.first);
      }

      busy_assignees.clear();
    }

    // Return the allocations
    return executed_tasks;
  }

  static void sort_tasks1 (std::vector<Task *> & tasks, int current_time) {
    std::sort(tasks.begin(), tasks.end(),
      [&](auto const * lhs, auto const * rhs) {
        // Return > for reverse sorting
        return std::make_pair(task_score(*lhs, current_time), -lhs->attribute3)
          > std::make_pair(task_score(*rhs, current_time), -rhs->attribute3);
      });
  }

  static void sort_tasks2 (std::vector<Task *> & tasks, int current_time) {
    std::sort(tasks.begin(), tasks.end(),
      [&](auto const * lhs, auto const * rhs) {
        // Sort on first ready
        return std::make_pair(lhs->attribute3, -task_score(*lhs, current_time))
          < std::make_pair(rhs->attribute3, -task_score(*rhs, current_time));
      });
  }

  static void sort_tasks3 (std::vector<Task *> & tasks, int current_time) {
    sort_tasks1(tasks, current_time);

    int num_swaps = 0;

    for (auto itA = tasks.rbegin(); (itA != tasks.rend()) and (num_swaps < 100); ++itA) {
      auto const & projA = **itA;

      if (projA.attribute3 > current_time) {
        auto curA = itA;

        for (auto itB = std::next(itA); itB != tasks.rend(); ++itB) {
          auto const & projB = **itB;
          std::int64_t margin = std::max(projB.attribute3 - projB.attribute1 - current_time, 0);

          if (projA.attribute1 < margin) {
            std::swap(*curA, *itB);
            curA = itB;
            num_swaps += 1;
          } else {
            break;
          }
        }
      }
    }
  }

  static void sort_tasks4 (std::vector<Task *> & tasks, int current_time) {
    std::sort(tasks.begin(), tasks.end(),
      [&](auto const * lhs, auto const * rhs) {
        // Return > for reverse sorting
        float const lhs_score = task_score(*lhs, current_time);
        float const rhs_score = task_score(*rhs, current_time);
        float const lhs_spare_days = task_spare_days(*lhs, current_time);
        float const rhs_spare_days = task_spare_days(*rhs, current_time);
        return lhs_score / lhs_spare_days > rhs_score / rhs_spare_days;
      });
  }

  static void sort_tasks5 (std::vector<Task *> & tasks, int current_time) {
    std::sort(tasks.begin(), tasks.end(),
      [&](auto const * lhs, auto const * rhs) {
        int window = 1500;
        bool deadlineSoonLhs = (task_spare_days(*lhs, current_time) < window);
        bool deadlineSoonRhs = (task_spare_days(*rhs, current_time) < window);
        // Return > for reverse sorting
        return std::make_pair(deadlineSoonLhs, task_score(*lhs, current_time))
          > std::make_pair(deadlineSoonRhs, task_score(*rhs, current_time));
      });
  }

  Task * get_best_task (std::vector<Task *> const & tasks,
                        std::vector<Assignee *> const & assignees,
                        int current_time) {

    // Caclulate the amount of assignee attriubte4 growth for every task
    std::unordered_map<Task const *, int> assigneeGrowth;
    for (auto * task : tasks) {

      int taskGrowth = 0;

      std::vector<Assignee *> available_assignees;
      for (auto & e : assignees) {available_assignees.push_back(e);}

      std::vector<Assignee *> selected_assignees;
      auto can_mentor = std::vector<bool>(task->attribute4s.size(), false);

      // Check if we have assignees with correct attribute4 for this.
      std::size_t attribute4_index = 0;

      for (auto const & attribute4 : task->attribute4s) {

        // Take the assignee that is of the lowest attribute4
        std::unordered_map<Assignee *, int> possible_assignees;
        for (auto * assignee : available_assignees) {
          auto const & attribute4s = assignee->attribute4s;
          auto attribute4It = std::find_if(attribute4s.begin(), attribute4s.end(),
            [&](auto const & e) {return e.attribute0 == attribute4.attribute0;});

          if (attribute4It == attribute4s.end()) {
            if (can_mentor.at(attribute4_index) >= attribute4.attribute1) {
              possible_assignees[assignee] = 0;
            }
          } else {
            if ((attribute4It->attribute1 + can_mentor.at(attribute4_index)) >= attribute4.attribute1) {
              possible_assignees[assignee] = attribute4It->attribute1;
            }
          }
        }

        if (possible_assignees.empty()) {
          // No one found, give up.
          break;
        }

        auto minAssigneeIt = std::min_element(possible_assignees.begin(), possible_assignees.end(),
          [](auto const & lhs, auto const & rhs) {return lhs.second < rhs.second;});

        // Check if the assignee will increase its attribute4
        if (minAssigneeIt->second <= attribute4.attribute1) {
          taskGrowth++;
        }

        auto assigneeIt = std::find_if(available_assignees.begin(), available_assignees.end(),
          [&](auto * assignee) {
            return (minAssigneeIt->first == assignee);
          });

        // Found someone, now check if he can mentor for any other attribute4s.
        for (std::size_t i = 0; i < task->attribute4s.size(); ++i) {
          auto const & otherAttribute4 = task->attribute4s[i];

          // Skip attribute4 we just searched for.
          if (i == selected_assignees.size()) {continue;}

          // Check if assignee can mentor otherAttribute4.
          auto attribute4It = std::find_if((*assigneeIt)->attribute4s.begin(), (*assigneeIt)->attribute4s.end(),
            [&](auto const & e) {
              return (e.attribute0 == otherAttribute4.attribute0) and
                     (e.attribute1 >= otherAttribute4.attribute1);
            });

          // Can mentor!
          if (attribute4It != (*assigneeIt)->attribute4s.end()) {
            can_mentor.at(i) = true;
          }
        }

        selected_assignees.push_back(*assigneeIt);
        available_assignees.erase(assigneeIt);

        attribute4_index += 1;
      }

      if (selected_assignees.size() != task->attribute4s.size()) {
        // No growth when the task cannot be executed
        assigneeGrowth[task] = -1000;
      } else {
        assigneeGrowth[task] = taskGrowth - task->attribute4s.size();
      }
    }

    // Find the task with the largest assignee attriubte4 growth. The task score
    // is used a second measure
    auto taskIt = std::max_element(tasks.begin(), tasks.end(),
      [&](auto const * lhs, auto const * rhs) {
        return std::make_pair(assigneeGrowth[lhs], task_score(*lhs, current_time))
          < std::make_pair(assigneeGrowth[rhs], task_score(*rhs, current_time));
      });

    return *taskIt;
  }

  static int task_score (Task const & task, int current_time) {
    int end_date = current_time + task.attribute1;
    int days_too_late = std::max(0, end_date - task.attribute3);
    return task.attribute2 - std::min(task.attribute2, days_too_late);
  }

  static int task_spare_days (Task const & task, int current_time) {
    int end_date = current_time + task.attribute1;
    return std::max(0, task.attribute3 - end_date);
  }

  static int get_min_time_jump (std::unordered_map<Assignee *, int> const & busy_assignees) {
    if (busy_assignees.empty()) {return 1;}

    auto it = std::min_element(busy_assignees.begin(), busy_assignees.end(),
      [](auto const & lhs, auto const & rhs) {return lhs.second < rhs.second;});
    return it->second;
  }

  static int get_max_time_jump (std::unordered_map<Assignee *, int> const & busy_assignees) {
    if (busy_assignees.empty()) {return 1;}

    auto it = std::max_element(busy_assignees.begin(), busy_assignees.end(),
      [](auto const & lhs, auto const & rhs) {return lhs.second > rhs.second;});
    return it->second;
  }

  // Members
  std::vector<Assignee> assignees_;
  std::vector<Task> tasks_;
};
