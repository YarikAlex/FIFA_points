#pragma once
#include <vector>
#include <queue>
#include "Group.h"
#include "Match.h"

struct TournamentConfig
{
  int participantsNumber;
  int groupNumber;
};

class Tournament
{
private:
  std::vector<std::shared_ptr<Group>> m_groups;
  std::vector<std::shared_ptr<Team>> m_participants;
  static constexpr TournamentConfig m_euroConfig{ 24, 6 };
  static constexpr TournamentConfig m_worldConfig{ 32, 8 };
  std::vector<Match> m_leftSide;
  std::vector<Match> m_rightSide;
  static std::unique_ptr<Tournament> create(const TournamentConfig& config, const std::string& path, const std::string& pathGroup);
  void addParticipants(const std::string& path, int numberParticipants);
  void setGroup(const std::string& path, const int tournamentGroups);
  std::shared_ptr<Team> addTeam(std::string& name);
  Match createMatch(std::shared_ptr<Team> lhs, std::shared_ptr<Team> rhs) const;
  void playRoundPlayOffSide(std::vector<Match>& gridSide, int round);

public:
  Tournament(const TournamentConfig& config, const std::string& path, const std::string& pathGroup);
  Tournament() = default;
  ~Tournament() = default;
  static std::unique_ptr<Tournament> createEuroCup(const std::string& path, const std::string& pathGroup);
  static std::unique_ptr<Tournament> createWorldCup(const std::string& path, const std::string& pathGroup);
  void playGroupRound();
  void createEuroPlayOff();
  void createWorldCupPlayOff();
  void printParticipants();
  void printPlayOffGrid();
  std::shared_ptr<Team> playRoundPlayOff();
  void printGroup();
};