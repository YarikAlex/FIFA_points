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