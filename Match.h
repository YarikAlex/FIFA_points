#pragma once
#include "Group.h"
class Match : public Group
{
public:
  std::shared_ptr<Team> first_team, second_team;
  Match(std::shared_ptr<Team> first, std::shared_ptr<Team> second);
  ~Match()=default;
};

