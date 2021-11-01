#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "Team.h"

class Group
{
public:
	std::vector<Team> m_teams;
	const double ImportanceOfMatch = 35.0; //FIFA sets different coefficients for different stages of the tournament. For a group round it's 35.
	const int numberTeams = 4; //the number of teams in the group.
	Group() = default;
	~Group() = default;
	void PlayMatch(Team& first, Team& second);
	void SortGroup();
	friend std::ostream& operator<< (std::ostream& out, const Group& group);
};