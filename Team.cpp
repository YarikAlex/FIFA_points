#include "Team.h"

Team::Team(std::string_view nameNew, int fifaRangNew, double fifaPointsNew) :
  name(nameNew), fifaRank(fifaRangNew), fifaPoints(fifaPointsNew), fifaBefore(fifaPointsNew)
{
  place = 0;
  games = 0;
  points = 0;
  goalsScored = 0;
  goalsConceded = 0;
  goalsDifference = 0;
  startingFifaPoints = fifaPoints;
}

teamStats Team::evaluateStats(int scored, int conceded, double importanceOfMatch, const double anotherTeamPoints)
{
  games++;
  fifaBefore = fifaPoints;
  teamStats team;
  /*
  New_fifa_points = Fifa_points + ImportanceOfMatches * (ResultOfMatch - ExpectedResultOfTheMatch)
  ExpectedResultOfTheMatch = 1/(10^-(FIFA points of this team - FIFA points of another team)/600) + 1
  ResultOfMatch = 1 if this team win, 0.5 if draw and 0 if lose
  */
  double ExpectedResultOfTheMatch = 1 / (pow(10, -(this->fifaPoints - anotherTeamPoints) / 600) + 1);
  team.scored = goalsScored + scored;
  team.conceded = goalsConceded + conceded;
  team.difference = (goalsScored + scored) - (goalsConceded + conceded);
  if (scored > conceded) {
	points += 3;
	team.pointsFifa = fifaPoints + importanceOfMatch * (1 - ExpectedResultOfTheMatch);
  }
  if (scored == conceded) {
	points++;
	team.pointsFifa = fifaPoints + importanceOfMatch * (0.5 - ExpectedResultOfTheMatch);
  }
  if (scored < conceded)
	team.pointsFifa = fifaPoints + importanceOfMatch * (0 - ExpectedResultOfTheMatch);
  return team;
}

teamStats Team::evaluateStatsPlayOff(int scored, int conceded, double importanceOfMatch, double anotherTeamPoints)
{
  games++;
  fifaBefore = fifaPoints;
  teamStats team;
  double ExpectedResultOfTheMatch = 1 / (pow(10, -(this->fifaPoints - anotherTeamPoints) / 600) + 1);
  team.scored = goalsScored + scored;
  team.conceded = goalsConceded + conceded;
  team.difference = (goalsScored + scored) - (goalsConceded + conceded);
  if (scored > conceded) {
	team.pointsFifa = fifaPoints + importanceOfMatch * (0.75 - ExpectedResultOfTheMatch);
  }
  if (scored < conceded) {
	points++;
	team.pointsFifa = fifaPoints + importanceOfMatch * (0.5 - ExpectedResultOfTheMatch);
  }
  return team;
  
}

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team)
{
  out << std::setw(5) << team->place<<"\t" <<std::setw(10) << team->name << "\t" << team->games << "\t" << team->points
	  << "\t" << team->goalsScored << "\t" << team->goalsConceded << "\t" << std::setw(10) << team->fifaPoints<< "\t"<< std::setprecision(4) << team->fifaPoints - team->fifaBefore
	  <<  std::endl;
  return out;
}