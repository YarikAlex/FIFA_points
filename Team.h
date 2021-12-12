#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>

struct teamStats
{
  int scored, conceded, difference;
  double pointsFifa;
};

class Team
{
public:
  std::string name;
  double fifaPoints, fifaBefore, startingFifaPoints;
  int fifaRank, place, games, points, goalsScored, goalsConceded, goalsDifference;
  Team(std::string_view nameNew, int fifaRankNew, double fifaPointsNew);
  teamStats evaluateStats(int scored, int conceded, double importanceOfMatch, double anotherTeamPoints);
  teamStats evaluateStatsPlayOff(int scored, int conceded, double importanceOfMatch, double anotherTeamPoints);
};

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team);