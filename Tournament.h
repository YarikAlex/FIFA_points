#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Group.h"

class Tournament
{
public:
	std::vector<Group> m_groups;
	std::vector<Team> m_participants;
	const int m_euroParticipants = 24;
	const int m_numberEuroGroup = 6;
	const int m_worldCupParticipants = 32;
	const int m_numberWorldCupGroup = 8;
	Tournament();
	~Tournament();
	int ChooseTournament();
	void AddParticipants(std::string path, int numberParticipants);
	void SetGroup(std::string path, const int tournamentGroups);
	void GroupRound();
	void PrintParticipants();
	void PrintGroup();
};