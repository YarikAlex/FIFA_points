#include "Team.h"

Team::Team(std::string name, int fifa_rang, double fifa_points) :
	m_name(name), m_fifa_rang(fifa_rang), m_fifa_points(fifa_points)
{
	m_place = 0;
	m_games = 0;
	m_points = 0;
	m_goal_scored = 0;
	m_goal_conceded = 0;
	m_goal_difference = 0;
}
Team::~Team() {}

void Team::CountingStats(int scored, int conceded, double ImportanceOfMatch, const double another_team_points)
{
	m_goal_scored += scored;
	m_goal_conceded += conceded;
	m_goal_difference = m_goal_scored - m_goal_conceded;
	m_games++;
	double difference = this->m_fifa_points - another_team_points;
	double ExpectedResultOfTheMatch = 1 / (pow(10, -difference / 600) + 1);
	//New_fifa_points = Fifa_points + ImportanceOfMatches * (ResultOfMatch - ExpectedResultOfTheMatch)
	if (scored > conceded) {
		m_points += 3;
		m_fifa_points = m_fifa_points + ImportanceOfMatch * (1 - ExpectedResultOfTheMatch);
	}
	if (scored == conceded) {
		m_points++;
		m_fifa_points = m_fifa_points + ImportanceOfMatch * (0.5 - ExpectedResultOfTheMatch);
	}
	if(scored<conceded)
		m_fifa_points = m_fifa_points + ImportanceOfMatch * (0 - ExpectedResultOfTheMatch);
}

std::ostream& operator<< (std::ostream& out, const Team& team)
{
	out << team.m_name << "\t" << team.m_games << "\t" << team.m_points << std::endl;
	return out;
}