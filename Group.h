#pragma once
#include <iostream>
#include <vector>
#include "Team.h"

class Group
{
public:
	std::vector<Team> m_teams;
	const double ImportanceOfMatch = 35.0;
	const int numberTeams = 4; //the number of teams in the group.
	Group() = default;
	~Group() = default;
	void PlayMatch(Team& first, Team& second);
	friend std::ostream& operator<< (std::ostream& out, const Group& group);
};