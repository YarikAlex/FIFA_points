#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Team
{
public:
	std::string m_name;
	double m_fifa_points, m_fifa_before;
	int m_fifa_rang, m_place, m_games, m_points, m_goal_scored, m_goal_conceded, m_goal_difference;
	Team(std::string name, int fifa_rang, double fifa_points);
	~Team();
	void CountingStats(int scored, int conceded, double ImportanceOfMatch, const double another_team_points);
	friend std::ostream& operator<< (std::ostream& out, const Team& team);
};

std::ostream& operator<< (std::ostream& out, const Team& team);