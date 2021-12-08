#include "Match.h"

Match::Match(std::shared_ptr<Team> first, std::shared_ptr<Team> second)
	  : firstTeam(first), secondTeam(second){}

std::shared_ptr<Team>& Match::playMatchPlayOff(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second)
{
  int home, guest;
  std::cout << "\tToday's match: " << first->name << " - " << second->name << std::endl;
  std::cout << "\tEnter result of match (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;

  //Output of the result to the screen
  if (home > guest)
  {
	std::cout << "\t" << first->name << " goes to the next round!" << std::endl << std::endl;
	return first;
  }
  if (home == guest)
  {
	std::cout << "\t" << "It's draw! The penalty shoot-out will begin now!" << std::endl << std::endl;
	return playPenalty(first, second);
  }
  if (home < guest)
  {
	std::cout << "\t" << second->name << " goes to the next round!" << std::endl << std::endl;
	return second;
  }
}

std::shared_ptr<Team>& Match::playPenalty(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second)
{
  int home, guest;
  std::cout << "\tEnter result of the penalty shootout (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;
  if (home > guest)
  {
	std::cout << "\t" << first->name << " goes to the next round!" << std::endl << std::endl;
	return first;
  }
  if (home < guest)
  {
	std::cout << "\t" << second->name << " goes to the next round!" << std::endl << std::endl;
	return second;
  }
}
