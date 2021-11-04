#include "Tournament.h"

	Tournament::Tournament()
	{
		std::string EuroPath = "../FIFApoints/EuroCupParticipants.txt";
		std::string EuroGroupPath = "../FIFApoints/EuroCupGroups.txt";
		std::string WorldCupPath = "../FIFApoints/WorldCupParticipants.txt";
		std::string WorldCupGroupPath = "../FIFApoints/WorldCupGroups.txt";
		switch (ChooseTournament())
		{
		case 1:
			AddParticipants(EuroPath, m_euroParticipants);
			SetGroup(EuroGroupPath, m_numberEuroGroup);
			break;
		case 2:
			AddParticipants(WorldCupPath, m_worldCupParticipants);
			SetGroup(WorldCupGroupPath, m_numberWorldCupGroup);
			break;
		default:
			std::cout << "Default case!" << std::endl;
			break;
		}
	}
	Tournament::~Tournament() {}
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

	void Tournament::AddParticipants(std::string path, int numberParticipants)
	{
		std::ifstream ParticipantsList;
		ParticipantsList.open(path);
		if (!ParticipantsList.is_open() and !ParticipantsList.good())
			std::cout << "File is not open!" << std::endl;
		else
		{
			std::string name;
			int rank;
			double fifa_points;
			for (int i = 0; i < numberParticipants; ++i)
			{
				ParticipantsList >> name >> rank >> fifa_points;
				std::shared_ptr<Team> p_new_team(new Team(name, rank, fifa_points));
				m_participants.push_back(p_new_team);
			}
		}
		ParticipantsList.close();
	}
	void Tournament::SetGroup(std::string path, const int tournamentGroups)
	{
		std::ifstream GroupList;
		GroupList.open(path);
		if(!GroupList.is_open() and !GroupList.good())
			std::cout << "File is not open!" << std::endl;
		else
		{
			std::string name;
			for (int numberGroups = 0; numberGroups < tournamentGroups; ++numberGroups)
			{
				std::shared_ptr<Group> p_new_group(new Group);
				for (int numberTeams = 0; numberTeams < p_new_group->numberTeams; ++numberTeams)
				{
					GroupList >> name;
					for (auto it : m_participants)
					{
						if (it->m_name == name)
							p_new_group->m_teams.push_back(it);
					}
				}
				m_groups.push_back(p_new_group);
			}
		}
		GroupList.close();
	}
	void Tournament::GroupRound()
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
					it->PlayMatch(it->m_teams[0], it->m_teams[1]);
					it->PlayMatch(it->m_teams[2], it->m_teams[3]);
					std::cout << it;
				}
				if (i == 1)
				{
					std::cout << "----Round #2" << std::endl;
					it->PlayMatch(it->m_teams[0], it->m_teams[2]);
					it->PlayMatch(it->m_teams[1], it->m_teams[3]);
					std::cout << it;
				}
				if (i == 2)
				{
					std::cout << "----Round #3" << std::endl;
					it->PlayMatch(it->m_teams[0], it->m_teams[3]);
					it->PlayMatch(it->m_teams[1], it->m_teams[2]);
					it->SortGroup();
					for_each(it->m_teams.begin(), it->m_teams.end(), [&](std::shared_ptr<Team>& team) {team->m_place = ++rank; });
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
			for_each(it->m_teams.begin(), it->m_teams.end(), [&](std::shared_ptr<Team>& team)
				{
					if (team->m_place == 1)
						firstTeams.push(team);
					if (team->m_place == 2)
						secondTeams.push(team);
					if(team->m_place == 3)
						preparationThirdTeams.push_back(team);
				});
		}
		//Find four best teams in third places
		sort(preparationThirdTeams.begin(), preparationThirdTeams.end(), [](std::shared_ptr<Team>& lhs, std::shared_ptr<Team>& rhs)
			{
				return std::tie(lhs->m_points, lhs->m_goal_difference) >
					std::tie(rhs->m_points, rhs->m_goal_difference);
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
				left_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			if (i == 1)
				right_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			//A1-C2 and D1-F2
			firstTmpTeam = firstTeams.front();
			firstTeams.pop();
			secondTmpTeam = secondTeams.front();
			secondTeams.pop();
			if (i == 0)
				right_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			if (i == 1)
				left_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			//B1-third-2 and E1-third-4
			std::shared_ptr<Team> thirdTmpTeam = thirdTeams.front(); //get third-1 and third-4 from the queue
			thirdTeams.pop();
			firstTmpTeam = firstTeams.front();
			firstTeams.pop();
			secondTmpTeam = thirdTeams.front();
			thirdTeams.pop();
			if (i == 0)
				right_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			if (i == 1)
				left_side.push_back(SetMatch(firstTmpTeam, secondTmpTeam));
			//C1-third-1 and F1-third-3
			firstTmpTeam = firstTeams.front();
			firstTeams.pop();
			if (i == 0)
				left_side.push_back(SetMatch(firstTmpTeam, thirdTmpTeam));
			if (i == 1)
				right_side.push_back(SetMatch(firstTmpTeam, thirdTmpTeam));
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
			std::cout <<std::setw(10)<< it->m_name << "\t" << it->m_fifa_rang << "\t" << it->m_fifa_points << std::endl;
	}

	void Tournament::PrintGroup()
	{
		for (auto it : m_groups)
			std::cout << it << std::endl;
	}

	Match Tournament::SetMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs)
	{
		Match new_match(lhs, rhs);
		return new_match;
	}
