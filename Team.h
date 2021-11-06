#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Team
{
public:
  std::string name;
  double fifaPoints, fifaBefore;
  int fifaRank, place, games, points, goalsScored, goalsConceded, goalsDifference;
  Team(std::string nameNew, int fifaRankNew, double fifaPointsNew);
  ~Team() = default;
  void CountingStats(int scored, int conceded, double importanceOfMatch, double anotherTeamPoints);
  //friend std::ostream& operator<< (std::ostream& out, const Team& team);
};

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team);