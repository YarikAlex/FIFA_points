#include "Tournament.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Tournament::Tournament(int choice, std::string& path, std::string& pathGroup)
{
  const int EURO = 1;
  const int WORLD = 2;
  if (choice == EURO)
  {
	try
	{
	  addParticipants(path, m_euroParticipants);
	  setGroup(pathGroup, m_numberEuroGroup);
	}
	catch (const std::exception& ex)
	{
	  std::cout << "Error! "<< ex.what() << std::endl;
	}
	
  }
  if (choice == WORLD)
  {
	try
	{
	  addParticipants(path, m_worldCupParticipants);
	  setGroup(pathGroup, m_numberWorldCupGroup);
	}
	catch (const std::exception& ex)
	{
	  std::cout << "Error!" << ex.what() << std::endl;
	}
  }
}

void Tournament::addParticipants(std::string& path, int numberParticipants) //The function reads participants from a file.
{
  std::ifstream participantsList;
  participantsList.open(path);
  if (!participantsList.is_open() and !participantsList.good())
	throw std::exception("Unable to add participants. File not found");
  else
  {
	std::string name;
	int rank = 0;
	double fifa_points = 0;
	for (int i = 0; i < numberParticipants; ++i)
	{
	  participantsList >> name >> rank >> fifa_points;
	  auto newTeam = std::make_shared<Team>(name, rank, fifa_points);
	  m_participants.push_back(newTeam);
	}
  }
}
void Tournament::setGroup(std::string& path, const int tournamentGroups) //The function distributes the participants into groups.
{
  std::ifstream groupList;
  groupList.open(path);
  if(!groupList.is_open() and !groupList.good())
	throw std::exception("Unable to set groups. File not found!");
  else
  {
	for (int numberGroups = 0; numberGroups < tournamentGroups; ++numberGroups)
	{
	  auto newGroup = std::make_shared<Group>();
	  newGroup->teams.resize(newGroup->numberTeams);
	  std::generate(newGroup->teams.begin(), newGroup->teams.end(), [&]()
	  {
		std::string name;
		groupList >> name;
		return addTeam(name);
	  });
	  m_groups.push_back(newGroup);
	}
  }
}
std::shared_ptr<Team> Tournament::addTeam(std::string& name)
{
  for (auto it : m_participants)
  {
	if (it->name == name)
	  return it;
  }
}
void Tournament::playGroupRound()
{
  int numberRounds = 3;
  for (int i = 0; i < numberRounds; ++i)
  {
	for (auto it : m_groups)
	{
	  int rank = 0;
	  if (i == 0)
	  {
		std::cout << "----Round #1----" << std::endl;
		it->playMatch(it->teams[0], it->teams[1]);
		it->playMatch(it->teams[2], it->teams[3]);
		std::cout << it<<std::endl;
	  }
	  if (i == 1)
	  {
		std::cout << "----Round #2----" << std::endl;
		it->playMatch(it->teams[0], it->teams[2]);
		it->playMatch(it->teams[1], it->teams[3]);
		std::cout << it;
	  }
	  if (i == 2)
	  {
		std::cout << "----Round #3----" << std::endl;
		it->playMatch(it->teams[0], it->teams[3]);
		it->playMatch(it->teams[1], it->teams[2]);
		it->sortGroup();
		for_each(it->teams.begin(), it->teams.end(), [&](std::shared_ptr<Team>& team) {team->place = ++rank; });
		std::cout << it;
	  }
	}
  }
}
void Tournament::setEuroPlayOff()
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
	try
	{
	  if(preparationThirdTeams.empty())
		throw std::exception("Vector preparationThirdTeams is empty");
	  else
	  {
		preparationThirdTeams.pop_back();
		preparationThirdTeams.shrink_to_fit();
	  }
	}
	catch (const std::exception& ex)
	{
	  std::cout << "Error! " << ex.what() << std::endl;
	}
	
  }
  //put commands in the queue
  for (auto it : preparationThirdTeams)
  {
	thirdTeams.push(it);
  }

  //Create a playoff grid
  for (int i = 0; i < 2; ++i)
  {
	try
	{
	  if (firstTeams.empty())
		throw std::exception("Queue firstTeams is empty");
	  if (secondTeams.empty())
		throw std::exception("Queue secondTeams is empty");
	  if (thirdTeams.empty())
		throw std::exception("Queue thirdTeamss is empty");
	  else
	  {
		//A2-B2 and D2-F2
		std::shared_ptr<Team> firstTmpTeam = secondTeams.front();
		secondTeams.pop();
		std::shared_ptr<Team> secondTmpTeam = secondTeams.front();
		secondTeams.pop();
		if (i == 0)
		  m_leftSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));
		if (i == 1)
		  m_rightSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));

		//A1-C2 and D1-F2
		firstTmpTeam = firstTeams.front();
		firstTeams.pop();
		secondTmpTeam = secondTeams.front();
		secondTeams.pop();
		if (i == 0)
		  m_rightSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));
		if (i == 1)
		  m_leftSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));

		//B1-third-2 and E1-third-4
		std::shared_ptr<Team> thirdTmpTeam = thirdTeams.front(); //get third-1 and third-4 from the queue
		thirdTeams.pop();
		firstTmpTeam = firstTeams.front();
		firstTeams.pop();
		secondTmpTeam = thirdTeams.front();
		thirdTeams.pop();
		if (i == 0)
		  m_rightSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));
		if (i == 1)
		  m_leftSide.push_back(createMatch(firstTmpTeam, secondTmpTeam));

		//C1-third-1 and F1-third-3
		firstTmpTeam = firstTeams.front();
		firstTeams.pop();
		if (i == 0)
		  m_leftSide.push_back(createMatch(firstTmpTeam, thirdTmpTeam));
		if (i == 1)
		  m_rightSide.push_back(createMatch(firstTmpTeam, thirdTmpTeam));
	  }
	}
	catch (const std::exception& ex)
	{
	  std::cout << "Error! " << ex.what() << std::endl;
	}
  }
}
void Tournament::setWorldCupPlayOff()
{
  std::queue<std::shared_ptr<Team>> firstTeams; //A1, B1, C1, D1, E1, F1, G1, H1
  std::queue<std::shared_ptr<Team>> secondTeams; //A2, B2, C2, D2, E2, F2, G2, H2
  //We split the first and second places into two baskets.
  for (auto it : m_groups)
  {
	for_each(it->teams.begin(), it->teams.end(), [&](std::shared_ptr<Team> &team)
	{
	  if(team->place == 1)
		firstTeams.push(team);
	  if(team->place == 2)
		secondTeams.push(team);
	});
  }
  //Create a playoff grid
  for(int i=0; i<4; ++i)
  {
	std::shared_ptr<Team> tmpTeam = secondTeams.front();
	secondTeams.pop();
	m_leftSide.push_back(createMatch(firstTeams.front(), secondTeams.front()));
	firstTeams.pop();
	secondTeams.pop();
	m_rightSide.push_back(createMatch(firstTeams.front(), tmpTeam));
	firstTeams.pop();
  }
}
void Tournament::printParticipants()
{
  sort(m_participants.begin(), m_participants.end(), [](std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs)
	{
	  return lhs->fifaPoints > rhs->fifaPoints;
	});
  for (auto itTeam : m_participants)
	std::cout << std::setw(10) << itTeam->name << "\t" << itTeam->startingFifaPoints << "\t" << itTeam->fifaPoints << "\t"
	<< itTeam->fifaPoints - itTeam->startingFifaPoints << std::endl;
}

void Tournament::printGroup()
{
  for (auto it : m_groups)
	std::cout << it << std::endl;
}

void Tournament::printPlayOffGrid()
{
  int count = 0;
  for (auto it : m_leftSide)
  {
	std::cout << "Match #" << ++count << std::endl;
	std::cout << it.first_team << std::endl << it.second_team << std::endl << std::endl;
  }
  for (auto it : m_rightSide)
  {
	std::cout << "Match #" << ++count << std::endl;
	std::cout << it.first_team << std::endl << it.second_team << std::endl << std::endl;
  }
}

Match Tournament::createMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs) const
{
  Match new_match(lhs, rhs);
  return new_match;
}
