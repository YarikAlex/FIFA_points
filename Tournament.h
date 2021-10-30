#pragma once
#include <iostream>
#include <vector>
#include "Group.h"

class Tournament
{
public:
	std::vector<Group> m_groups;
	const int euroParticipants = 24;
	const int worldCupParticipants = 32;
	Tournament();
	~Tournament();
	int ChooseTournament();
};