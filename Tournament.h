#pragma once
#include <vector>
#include <queue>
#include "Group.h"
#include "Match.h"

class Tournament
{
private:
  std::vector<std::shared_ptr<Group>> m_groups;
  std::vector<Match> m_leftSide;
  std::vector<Match> m_rightSide;
  std::vector<std::shared_ptr<Team>> m_participants;
  static constexpr int m_euroParticipants = 24;
  static constexpr int m_numberEuroGroup = 6;
  static constexpr int m_worldCupParticipants = 32;
  static constexpr int m_numberWorldCupGroup = 8;
  Match createMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs) const;
  void addParticipants(std::string& path, int numberParticipants);
  void setGroup(std::string& path, const int tournamentGroups);
  std::shared_ptr<Team> addTeam(std::string& name);
public:
  Tournament(int choice, std::string& path, std::string& pathGroup);
  ~Tournament() = default;
  void playGroupRound();
  void setEuroPlayOff();
  void printParticipants();
  void printGroup();
};