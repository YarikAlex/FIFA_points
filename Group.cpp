#include "Group.h"


void Group::PlayMatch(Team& first, Team& second)
{
	int home, guest;
	std::cout << "Today's match: " << first.m_name << " - " << second.m_name << std::endl;
	std::cout << "Enter result of match (first_team second_team): ";
	std::cin >> home >> guest;
	first.CountingStats(home, guest, ImportanceOfMatch, second.m_fifa_points);
	second.CountingStats(guest, home, ImportanceOfMatch, first.m_fifa_points);
	if (home > guest)
		std::cout << first.m_name << " - win!" << std::endl;
	if (home == guest)
		std::cout << "It's draw!" << std::endl;
	if (home < guest)
		std::cout << second.m_name << " - win!" << std::endl;
}

void Group::SortGroup()
{
	sort(m_teams.begin(), m_teams.end(), [](Team& lhs, Team& rhs)
		{
			return std::tie(lhs.m_points, lhs.m_goal_difference) >
				std::tie(rhs.m_points, rhs.m_goal_difference);
		});
}

std::ostream& operator<< (std::ostream& out, const Group& group)
{
	std::cout<<std::setw(5) <<"Place"<<"\t" << std::setw(10) << "Teams" << "\t" << "Games\tPoints\tGS\tGC\t"<< std::setw(10) <<"FIFA points" <<"\t+/-" << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
	for (auto it : group.m_teams)
	{
		out << it;
	}
	return out;
}