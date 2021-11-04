#include "Team.h"

Team::Team(std::string name, int fifa_rang, double fifa_points) :
	m_name(name), m_fifa_rang(fifa_rang), m_fifa_points(fifa_points), m_fifa_before(fifa_points)
{
	m_place = 0;
	m_games = 0;
	m_points = 0;
	m_goal_scored = 0;
	m_goal_conceded = 0;
	m_goal_difference = 0;
}

void Team::CountingStats(int scored, int conceded, double ImportanceOfMatch, const double another_team_points)
{
	m_goal_scored += scored;
	m_goal_conceded += conceded;
	m_goal_difference = m_goal_scored - m_goal_conceded;
	m_games++;
	m_fifa_before = m_fifa_points;
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

std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Team>& team)
{
	
	out << std::setw(5) << team->m_place<<"\t" <<std::setw(10) << team->m_name << "\t" << team->m_games << "\t" << team->m_points
		<< "\t" << team->m_goal_scored << "\t" << team->m_goal_conceded <<"\t" << std::setw(10) << team->m_fifa_points<< "\t"<< std::setprecision(4) << team->m_fifa_points - team->m_fifa_before
		<<  std::endl;
	return out;
}