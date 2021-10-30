#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
#include "Group.h"
#include "Tournament.h"
using namespace std;


int main()
{
	Team myTeam("team1", 1, 1500);
	Team yourTeam("team2", 2, 1499);
	Group group;
	group.PlayMatch(myTeam, yourTeam);
	cout << myTeam;
	cout << yourTeam;
	Tournament turnament;

	return 0;
}