#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>
#include "Team.h"

class Group
{
public:
  std::vector<std::shared_ptr<Team>> teams;
  static constexpr int numberTeams = 4; //the number of teams in the group.
  Group() = default;
  void playMatch(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second, double importanceOfMatch);
  void sortGroup();
};

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Group>& group);

