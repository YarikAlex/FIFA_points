#include "Tournament.h"

	Tournament::Tournament()
	{
		switch (ChooseTournament())
		{
		case 1:
			std::cout << "Add Euro!" << std::endl;
			break;
		case 2:
			std::cout << "Add World Cup!" << std::endl;
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