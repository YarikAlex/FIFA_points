#include "Group.h"


void Group::playMatch(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second, double importanceOfMatch)
{
  int home, guest;
  std::cout << "\tToday's match: " << first->name << " - " << second->name << std::endl;
  std::cout << "\tEnter result of match (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;

  //Calculate the statistics for the first team.
  teamStats firstTeamStats = first->evaluateStats(home, guest, importanceOfMatch, second->fifaPoints);
  first->goalsScored = firstTeamStats.scored;
  first->goalsConceded = firstTeamStats.conceded;
  first->goalsDifference =firstTeamStats.difference;
  first->fifaPoints = firstTeamStats.pointsFifa;

  //Calculate the statistics for the second team.
  teamStats secondTeamStats = second->evaluateStats(guest, home, importanceOfMatch, first->fifaBefore);
  second->goalsScored = secondTeamStats.scored;
  second->goalsConceded = secondTeamStats.conceded;
  second->goalsDifference = secondTeamStats.difference;
  second->fifaPoints = secondTeamStats.pointsFifa;

  //Output of the result to the screen
  if (home > guest)
	std::cout << "\t" << first->name << " - win!" << std::endl << std::endl;
  if (home == guest)
	std::cout << "\t" << "It's draw!" << std::endl << std::endl;
  if (home < guest)
	std::cout << "\t" << second->name << " - win!" << std::endl << std::endl;
}

void Group::sortGroup()
{
  sort(teams.begin(), teams.end(), [](std::shared_ptr<Team>& lhs, std::shared_ptr<Team>& rhs)
  {
	return std::tie(lhs->points, lhs->goalsDifference, lhs->goalsScored) 
		 > std::tie(rhs->points, rhs->goalsDifference, rhs->goalsScored);
  });
}

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Group>& group)
{
  std::cout<<std::setw(5) <<"Place"<<"\t" << std::setw(10) << "Teams" << "\t" << "Games\tPoints\tGS\tGC\t"<< std::setw(10) <<"FIFA points" <<"\t+/-" << std::endl;
  std::cout << "-----------------------------------------------------------------------" << std::endl;
  for (auto it : group->teams)
  {
	out << it;
  }
  return out;
}