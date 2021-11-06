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
}

void Team::CountingStats(int scored, int conceded, double importanceOfMatch, const double anotherTeamPoints)
{
  goalsScored += scored;
  goalsConceded += conceded;
  goalsDifference = goalsScored - goalsConceded;
  games++;
  fifaBefore = fifaPoints;
  double difference = this->fifaPoints - anotherTeamPoints;
  double ExpectedResultOfTheMatch = 1 / (pow(10, -difference / 600) + 1);
  //New_fifa_points = Fifa_points + ImportanceOfMatches * (ResultOfMatch - ExpectedResultOfTheMatch)
  if (scored > conceded) {
	points += 3;
	fifaPoints = fifaPoints + importanceOfMatch * (1 - ExpectedResultOfTheMatch);
  }
  if (scored == conceded) {
	points++;
	fifaPoints = fifaPoints + importanceOfMatch * (0.5 - ExpectedResultOfTheMatch);
  }
  if(scored<conceded)
	fifaPoints = fifaPoints + importanceOfMatch * (0 - ExpectedResultOfTheMatch);
}

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team)
{
	
  out << std::setw(5) << team->place<<"\t" <<std::setw(10) << team->name << "\t" << team->games << "\t" << team->points
	  << "\t" << team->goalsScored << "\t" << team->goalsConceded <<"\t" << std::setw(10) << team->fifaPoints<< "\t"<< std::setprecision(4) << team->fifaPoints - team->fifaBefore
	  <<  std::endl;
  return out;
}