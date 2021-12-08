#include "Group.h"


void Group::playMatch(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second)
{
  int home, guest;
  std::cout << "\tToday's match: " << first->name << " - " << second->name << std::endl;
  std::cout << "\tEnter result of match (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;

  //Calculate the statistics for the first team.
  std::tuple<int, int, int, double> firstTeamStats = first->evaluateStats(home, guest, importanceOfMatch, second->fifaPoints);
  first->goalsScored = std::get<0>(firstTeamStats);
  first->goalsConceded = std::get<1>(firstTeamStats);
  first->goalsDifference = std::get<2>(firstTeamStats);
  first->fifaPoints = std::get<3>(firstTeamStats);

  //Calculate the statistics for the second team.
  std::tuple<int, int, int, double> secondTeamStats = second->evaluateStats(guest, home, importanceOfMatch, first->fifaBefore);
  second->goalsScored = std::get<0>(secondTeamStats);
  second->goalsConceded = std::get<1>(secondTeamStats);
  second->goalsDifference = std::get<2>(secondTeamStats);
  second->fifaPoints = std::get<3>(secondTeamStats);

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