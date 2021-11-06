#include "Tournament.h"
#include <iostream>
#include <fstream>

Tournament::Tournament(std::string euroPath, std::string euroGroupPath, std::string worldCupPath, std::string worldCupGroupPath)
{
  const int EURO = 1;
  const int WORLD = 2;
  switch (ChooseTournament())
  {
  case EURO:
	AddParticipants(euroPath, m_euroParticipants);
	SetGroup(euroGroupPath, m_numberEuroGroup);
	break;
  case WORLD:
	AddParticipants(worldCupPath, m_worldCupParticipants);
	SetGroup(worldCupGroupPath, m_numberWorldCupGroup);
	break;
  default:
	std::cout << "Default case!" << std::endl;
	break;
  }
}
int Tournament::ChooseTournament()
{
  int choice;
  do {
	std::cout << "---Select a tournament---" << std::endl;
	std::cout << "Press 1 for Euro or 2 for World Cup!" << std::endl;
	std::cin >> choice;
  } while (choice < 1 or choice > 2);
  return choice;
}

void Tournament::AddParticipants(std::string& path, int numberParticipants)
{
  std::ifstream participantsList;
  participantsList.open(path);
  if (!participantsList.is_open() and !participantsList.good())
	std::cerr << "File is not open!" << std::endl;
  else
  {
	std::string name;
	int rank = 0;
	double fifa_points = 0;
	for (int i = 0; i < numberParticipants; ++i)
	{
	  participantsList >> name >> rank >> fifa_points;
	  std::shared_ptr<Team> p_new_team(new Team(name, rank, fifa_points));
	  m_participants.push_back(p_new_team);
	}
  }
  participantsList.close();
}
void Tournament::SetGroup(std::string& path, const int tournamentGroups)
{
  std::ifstream groupList;
  groupList.open(path);
  if(!groupList.is_open() and !groupList.good())
	std::cerr << "File is not open!" << std::endl;
  else
  {
	std::string name;
	for (int numberGroups = 0; numberGroups < tournamentGroups; ++numberGroups)
	{
	  std::shared_ptr<Group> p_new_group(new Group);
	  for (int numberTeams = 0; numberTeams < p_new_group->numberTeams; ++numberTeams)
	  {
		groupList >> name;
		for (auto it : m_participants)
		{
		  if (it->name == name)
			p_new_group->teams.push_back(it);
		}
	  }
	  m_groups.push_back(p_new_group);
	}
  }
  groupList.close();
}
void Tournament::PlayGroupRound()
{
  int numberRounds = 3;
  for (int i = 0; i < numberRounds; ++i)
  {
	for (auto it : m_groups)
	{
	  int rank = 0;
	  if (i == 0)
	  {
		std::cout << "----Round #1" << std::endl;
		it->PlayMatch(it->teams[0], it->teams[1]);
		it->PlayMatch(it->teams[2], it->teams[3]);
		std::cout << it<<std::endl;
	  }
	  if (i == 1)
	  {
		std::cout << "----Round #2" << std::endl;
		it->PlayMatch(it->teams[0], it->teams[2]);
		it->PlayMatch(it->teams[1], it->teams[3]);
		std::cout << it;
	  }
	  if (i == 2)
	  {
		std::cout << "----Round #3" << std::endl;
		it->PlayMatch(it->teams[0], it->teams[3]);
		it->PlayMatch(it->teams[1], it->teams[2]);
		it->SortGroup();
		for_each(it->teams.begin(), it->teams.end(), [&](std::shared_ptr<Team>& team) {team->place = ++rank; });
		std::cout << it;
	  }
	}
  }
}
void Tournament::SetEuroPlayOff()
{
  //We split the first, second and third places into three baskets.
  std::queue<std::shared_ptr<Team>> firstTeams; //A1, B1, C1, D1, E1, F1
  std::queue<std::shared_ptr<Team>> secondTeams; //A2, B2, C2, D2, E2, F2
  std::vector<std::shared_ptr<Team>> preparationThirdTeams; //A3, B3, C3, D3, E3, F3
  std::queue<std::shared_ptr<Team>> thirdTeams; //third-1, third-2, third-3, third-4
  for (auto it : m_groups)
  {
	for_each(it->teams.begin(), it->teams.end(), [&](std::shared_ptr<Team>& team)
	{
	  if (team->place == 1)
		  firstTeams.push(team);
	  if (team->place == 2)
		  secondTeams.push(team);
	  if(team->place == 3)
		  preparationThirdTeams.push_back(team);
	});
  }
  //Find four best teams in third places
  sort(preparationThirdTeams.begin(), preparationThirdTeams.end(), [](std::shared_ptr<Team>& lhs, std::shared_ptr<Team>& rhs)
  {
	return std::tie(lhs->points, lhs->goalsDifference) > std::tie(rhs->points, rhs->goalsDifference);
  });
  //Remove fifth and sixth teams
  for (int i = 0; i < 2; ++i)
  {
	preparationThirdTeams.pop_back();
	preparationThirdTeams.shrink_to_fit();
  }
  //put commands in the queue
  for (auto it : preparationThirdTeams)
  {
	thirdTeams.push(it);
  }

  //Create a playoff grid
  for (int i = 0; i < 2; ++i)
  {
	//A2-B2 and D2-F2
	std::shared_ptr<Team> firstTmpTeam = secondTeams.front();
	secondTeams.pop();
	std::shared_ptr<Team> secondTmpTeam = secondTeams.front();
	secondTeams.pop();
	if (i == 0)
	  left_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));
	if (i == 1)
	  right_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));

	//A1-C2 and D1-F2
	firstTmpTeam = firstTeams.front();
	firstTeams.pop();
	secondTmpTeam = secondTeams.front();
	secondTeams.pop();
	if (i == 0)
	  right_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));
	if (i == 1)
	  left_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));

	//B1-third-2 and E1-third-4
	std::shared_ptr<Team> thirdTmpTeam = thirdTeams.front(); //get third-1 and third-4 from the queue
	thirdTeams.pop();
	firstTmpTeam = firstTeams.front();
	firstTeams.pop();
	secondTmpTeam = thirdTeams.front();
	thirdTeams.pop();
	if (i == 0)
	  right_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));
	if (i == 1)
	  left_side.push_back(CreateMatch(firstTmpTeam, secondTmpTeam));

	//C1-third-1 and F1-third-3
	firstTmpTeam = firstTeams.front();
	firstTeams.pop();
	if (i == 0)
	  left_side.push_back(CreateMatch(firstTmpTeam, thirdTmpTeam));
	if (i == 1)
	  right_side.push_back(CreateMatch(firstTmpTeam, thirdTmpTeam));
  }
  int count = 0;
  for (auto it : left_side)
  {
	std::cout << "Match #" << ++count << std::endl;
	std::cout << it.first_team << std::endl << it.second_team << std::endl << std::endl;
  }
  for (auto it : right_side)
  {
	std::cout << "Match #" << ++count << std::endl;
	std::cout << it.first_team << std::endl << it.second_team << std::endl << std::endl;
  }
}
void Tournament::PrintParticipants()
{
  for (auto it : m_participants)
	std::cout <<std::setw(10)<< it->name << "\t" << it->fifaRank << "\t" << it->fifaPoints << std::endl;
}

void Tournament::PrintGroup()
{
  for (auto it : m_groups)
	std::cout << it << std::endl;
}

Match Tournament::CreateMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs)
{
  Match new_match(lhs, rhs);
  return new_match;
}
