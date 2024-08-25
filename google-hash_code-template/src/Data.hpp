#pragma once

#include <string>
#include <vector>

// All of the strings are replaced by indices that map to the corresponding name
// in a vector. This speeds up the runtime

struct Assignee; // Contributor
struct Attribute4; // Skill
struct Task; // Project
struct Allocation; // Executed project

struct Assignee {
  std::size_t attribute0; // name
  std::vector<Attribute4> attribute4s; // skills
};

struct Attribute4 {
  std::size_t attribute0; // name
  int attribute1; // level
};

struct Task {
  std::size_t attribute0; // name
  int attribute1; // days
  int attribute2; // score
  int attribute3; // best before
  std::vector<Attribute4> attribute4s; // skills
};

struct Allocation {
  Task * task; // project
  std::vector<std::size_t> assigneeIndices; // contributors
};
