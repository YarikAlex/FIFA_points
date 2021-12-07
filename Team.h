#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Team
{
public:
  std::string name;
  double fifaPoints, fifaBefore, startingFifaPoints;
  int fifaRank, place, games, points, goalsScored, goalsConceded, goalsDifference;
  Team(std::string nameNew, int fifaRankNew, double fifaPointsNew);
  ~Team() = default;
  const std::tuple<int, int, int, double> evaluateStats(int scored, int conceded, double importanceOfMatch, double anotherTeamPoints);
};

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team);