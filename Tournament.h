#pragma once
#include <vector>
#include <queue>
#include "Group.h"
#include "Match.h"

class Tournament
{
private:
  std::vector<std::shared_ptr<Group>> m_groups;
  std::vector<Match> left_side;
  std::vector<Match> right_side;
  std::vector<std::shared_ptr<Team>> m_participants;
  static constexpr int m_euroParticipants = 24;
  static constexpr int m_numberEuroGroup = 6;
  static constexpr int m_worldCupParticipants = 32;
  static constexpr int m_numberWorldCupGroup = 8;
  Match CreateMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs);
public:
  Tournament(std::string euroPath, std::string euroGroupPath, std::string worldCupPath, std::string worldCupGroupPath);
  ~Tournament() = default;
  int ChooseTournament();
  void AddParticipants(std::string& path, int numberParticipants);
  void SetGroup(std::string& path, const int tournamentGroups);
  void PlayGroupRound();
  void SetEuroPlayOff();
  void PrintParticipants();
  void PrintGroup();

};