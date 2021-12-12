#include <iostream>
#include <string>
#include <memory>
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
  enum tournamentType { Euro = 1, World };
 
  int choice;
  do {
	std::cout << "--------Select a tournament--------" << std::endl;
	std::cout << "Press 1 for Euro or 2 for World Cup!" << std::endl;
	std::cin >> choice;
  } while (choice < 1 or choice > 2);

  std::unique_ptr<Tournament> tournament;
  if (choice == Euro)
  {
	Tournament euroCup;
	tournament = euroCup.createEuroCup(euroPath, euroGroupPath);
  }
  if (choice == World)
  {
	Tournament worldCup;
	tournament = worldCup.createWorldCup(worldCupPath, worldCupGroupPath);
  }
  tournament->printParticipants();
  tournament->printGroup();
  tournament->playGroupRound();
  if (choice == Euro)
  {
	
	tournament->createEuroPlayOff();
	cout<<"------" << tournament->playRoundPlayOff()->name << " is the Champion of Europe!!!------" << endl;
	tournament->printParticipants();
  }
  if (choice == tournamentType::World)
  {
	tournament->createWorldCupPlayOff();
	cout << "------" << tournament->playRoundPlayOff()->name << " is the World Champion!!!------" << endl;
	tournament->printParticipants();
  }
	

  return 0;
}