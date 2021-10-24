#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
#include "Group.h"
using namespace std;


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