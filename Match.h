#pragma once
#include "Group.h"
class Match : public Group
{
public:
  std::shared_ptr<Team> firstTeam, secondTeam;
  Match(std::shared_ptr<Team> first, std::shared_ptr<Team> second);
  std::shared_ptr<Team>& playMatchPlayOff(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second);
  std::shared_ptr<Team>& playPenalty(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second);
};

