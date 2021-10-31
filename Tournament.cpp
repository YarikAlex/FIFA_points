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
			std::cout << "Add Euro!" << std::endl;
			AddParticipants(EuroPath, m_euroParticipants);
			SetGroup(EuroGroupPath, m_numberEuroGroup);
			break;
		case 2:
			std::cout << "Add World Cup!" << std::endl;
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
				Team new_team(name, rank, fifa_points);
				m_participants.push_back(new_team);
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
				Group new_group;
				for (int numberTeams = 0; numberTeams < new_group.numberTeams; ++numberTeams)
				{
					GroupList >> name;
					for (auto it : m_participants)
					{
						if (it.m_name == name)
							new_group.m_teams.push_back(it);
					}
				}
				m_groups.push_back(new_group);
			}
		}
	}
	void Tournament::PrintParticipants()
	{
		for (auto it : m_participants)
			std::cout << it.m_name << "\t" << it.m_fifa_rang << "\t" << it.m_fifa_points << std::endl;
	}

	void Tournament::PrintGroup()
	{
		for (auto it : m_groups)
			std::cout << it << std::endl;
	}
