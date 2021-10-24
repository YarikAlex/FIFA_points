#pragma once
#include <iostream>
#include <vector>
#include "Team.h"

class Group
{
public:
	std::vector<Team> m_teams;
	const double ImportanceOfMatch = 35.0;
	Group() = default;
	~Group() = default;
	void PlayMatch(Team& first, Team& second);
};