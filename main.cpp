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
  Tournament tournament(euroPath, euroGroupPath, worldCupPath, worldCupGroupPath);
  tournament.PrintParticipants();
  tournament.PrintGroup();
  tournament.PlayGroupRound();
  tournament.SetEuroPlayOff();

  return 0;
}