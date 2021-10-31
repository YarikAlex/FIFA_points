#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
#include "Group.h"
#include "Tournament.h"
using namespace std;


int main()
{
	Tournament tournament;
	tournament.PrintParticipants();
	tournament.PrintGroup();

	return 0;
}