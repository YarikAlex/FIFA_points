#include <iostream>
#include <string>
#include <vector>
#include "Team.h"
#include "Group.h"
#include "Tournament.h"
using namespace std;


int main()
{
  const string euroPath = "../FIFApoints/EuroCupParticipants.txt";
  const string euroGroupPath = "../FIFApoints/EuroCupGroups.txt";
  const string worldCupPath = "../FIFApoints/WorldCupParticipants.txt";
  const string worldCupGroupPath = "../FIFApoints/WorldCupGroups.txt";
  const int EURO = 1;
  const int WORLD = 2;

  int choice;
  do {
	std::cout << "---Select a tournament---" << std::endl;
	std::cout << "Press 1 for Euro or 2 for World Cup!" << std::endl;
	std::cin >> choice;
  } while (choice < 1 or choice > 2);

  string pathParticipants, pathGroup;
  if (choice == EURO)
  {
	pathParticipants = euroPath;
	pathGroup = euroGroupPath;
  }
  if (choice == WORLD)
  {
	pathParticipants = worldCupPath;
	pathGroup = worldCupGroupPath;
  }
  Tournament tournament(choice, pathParticipants, pathGroup);
  tournament.printParticipants();
  tournament.printGroup();
  tournament.playGroupRound();
  tournament.setEuroPlayOff();

  return 0;
}