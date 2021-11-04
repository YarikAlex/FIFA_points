#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include "Group.h"
#include "Match.h"

class Tournament
{
public:
	std::vector<std::shared_ptr<Group>> m_groups;
	std::vector<Match> left_side;
	std::vector<Match> right_side;
	std::vector<std::shared_ptr<Team>> m_participants;
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
	void SetEuroPlayOff();
	void PrintParticipants();
	void PrintGroup();
private:
	Match SetMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs);
};