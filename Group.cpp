#include "Group.h"


void Group::PlayMatch(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second)
{
  int home, guest;
  std::cout << "\tToday's match: " << first->name << " - " << second->name << std::endl;
  std::cout << "\tEnter result of match (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;
  first->CountingStats(home, guest, importanceOfMatch, second->fifaPoints);
  second->CountingStats(guest, home, importanceOfMatch, first->fifaBefore);
  if (home > guest)
	std::cout <<"\t" << first->name << " - win!" << std::endl << std::endl;
  if (home == guest)
	std::cout << "\t" << "It's draw!" << std::endl << std::endl;
  if (home < guest)
	std::cout << "\t" << second->name << " - win!" << std::endl << std::endl;
}

void Group::SortGroup()
{
  sort(teams.begin(), teams.end(), [](std::shared_ptr<Team>& lhs, std::shared_ptr<Team>& rhs)
  {
	return std::tie(lhs->points, lhs->goalsDifference) > std::tie(rhs->points, rhs->goalsDifference);
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