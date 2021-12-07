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
  static constexpr double importanceOfMatch = 35.0; //FIFA sets different coefficients for different stages of the tournament. For a group round it's 35.
  static constexpr int numberTeams = 4; //the number of teams in the group.
  void playMatch(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second);
  void sortGroup();
  friend std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Group>& group);
};