#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
using namespace std;

class Group
{
public:
	vector<Team> m_teams;
	const double ImportanceOfMatch = 35.0;
	Group() {}
	~Group() {}
	void PlayMatch(Team& first, Team& second)
	{
		int home, guest;
		cout << "Today's match: " << first.m_name << " - " << second.m_name << endl;
		cout << "Enter result of match (first_team second_team): ";
		cin >> home >> guest;
		first.CountingStats(home, guest, ImportanceOfMatch, second.m_fifa_points);
		second.CountingStats(guest, home, ImportanceOfMatch, first.m_fifa_points);
		if (home > guest)
			cout << first.m_name << " - win!" << endl;
		if (home == guest)
			cout << "It's draw!" << endl;
		if (home < guest)
			cout << second.m_name << " - win!" << endl;
	}
};


int main()
{
	Team myTeam("My team", 1, 100500);
	Team yourTeam("Your team", 2, 100499);
	Group group;
	group.PlayMatch(myTeam, yourTeam);
	cout << myTeam;
	cout << yourTeam;

	return 0;
}