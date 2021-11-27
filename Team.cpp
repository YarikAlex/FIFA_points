#include "Team.h"

Team::Team(std::string nameNew, int fifaRangNew, double fifaPointsNew) :
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

const std::tuple<int, int, int, double> Team::evaluatingStats(int scored, int conceded, double importanceOfMatch, const double anotherTeamPoints)
{
  games++;
  fifaBefore = fifaPoints;
  /*
  New_fifa_points = Fifa_points + ImportanceOfMatches * (ResultOfMatch - ExpectedResultOfTheMatch)
  ExpectedResultOfTheMatch = 1/(10^-(FIFA points of this team - FIFA points of another team)/600) + 1
  ResultOfMatch = 1 if this team win, 0.5 if draw and 0 if lose
  */
  double ExpectedResultOfTheMatch = 1 / (pow(10, -(this->fifaPoints - anotherTeamPoints) / 600) + 1);
  if (scored > conceded) {
	points += 3;
	return std::make_tuple(goalsScored + scored, goalsConceded + conceded, scored - conceded,
	  fifaPoints + importanceOfMatch * (1 - ExpectedResultOfTheMatch));
  }
  if (scored == conceded) {
	points++;
	return std::make_tuple(goalsScored + scored, goalsConceded + conceded, scored - conceded,
	  fifaPoints + importanceOfMatch * (0.5 - ExpectedResultOfTheMatch));
  }
  if (scored < conceded)
	return std::make_tuple(goalsScored + scored, goalsConceded + conceded, scored - conceded,
	  fifaPoints + importanceOfMatch * (0 - ExpectedResultOfTheMatch));
}

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team)
{
	
  out << std::setw(5) << team->place<<"\t" <<std::setw(10) << team->name << "\t" << team->games << "\t" << team->points
	  << "\t" << team->goalsScored << "\t" << team->goalsConceded <<"\t" << std::setw(10) << team->fifaPoints<< "\t"<< std::setprecision(4) << team->fifaPoints - team->fifaBefore
	  <<  std::endl;
  return out;
}