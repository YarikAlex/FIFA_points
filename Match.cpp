#include "Match.h"

Match::Match(std::shared_ptr<Team> first, std::shared_ptr<Team> second)
	  : firstTeam(first), secondTeam(second){}

std::shared_ptr<Team>& Match::playMatchPlayOff(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second, double importanceOfMatch)
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

	//Calculate the statistics for the first team.
	teamStats firstTeamStats = first->evaluateStatsPlayOff(home, guest, importanceOfMatch, second->fifaPoints);
	setStats(first, firstTeamStats);

	// Calculate the statistics for the second team.
	teamStats secondTeamStats = second->evaluateStatsPlayOff(guest, home, importanceOfMatch, first->fifaBefore);
	setStats(second, secondTeamStats);
	return first;
  }
  if (home == guest)
  {
	std::cout << "\t" << "It's draw! The penalty shoot-out will begin now!" << std::endl << std::endl;
	return playPenalty(first, second, importanceOfMatch);
  }
  if (home < guest)
  {
	std::cout << "\t" << second->name << " goes to the next round!" << std::endl << std::endl;
	teamStats firstTeamStats = first->evaluateStatsPlayOff(home, guest, importanceOfMatch, second->fifaPoints);
	setStats(first, firstTeamStats);
	teamStats secondTeamStats = second->evaluateStatsPlayOff(guest, home, importanceOfMatch, first->fifaBefore);
	setStats(second, secondTeamStats);
	return second;
  }
}

std::shared_ptr<Team>& Match::playPenalty(std::shared_ptr<Team>& first, std::shared_ptr<Team>& second, double importanceOfMatch)
{
  int home, guest;
  std::cout << "\tEnter result of the penalty shootout (first_team second_team): ";
  std::cin >> home >> guest;
  std::cout << "\t-------------------------------------------------------" << std::endl;

  teamStats firstTeamStats = first->evaluateStatsPlayOff(home, guest, importanceOfMatch, second->fifaPoints);
  setStats(first, firstTeamStats);
  teamStats secondTeamStats = second->evaluateStatsPlayOff(guest, home, importanceOfMatch, first->fifaBefore);
  setStats(second, secondTeamStats);

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

void Match::setStats(std::shared_ptr<Team>& team, teamStats teamStats)
{
  team->goalsScored = teamStats.scored;
  team->goalsConceded = teamStats.conceded;
  team->goalsDifference = teamStats.difference;
  team->fifaPoints = teamStats.pointsFifa;
}
