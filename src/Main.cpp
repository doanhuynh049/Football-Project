#include <iostream>
#include <vector>
#include "Tournament.h"
#include <algorithm>
#include "DatabaseManagement.h"
const std::string SEASON_START_MESSAGE = "The season start: \n";
const std::string SEASON_END_MESSAGE = "The season terminated. \n";

void SortTeam(std::vector<football::Team> &teams)
{
    std::sort(teams.begin(), teams.end(), [](const football::Team &a, const football::Team &b)
              {
                  if (a.getPoints() == b.getPoints())
                  {
                      if (a.getGoalDifference() == b.getGoalDifference())
                      {
                          return a.getGoalsScored() > b.getGoalsScored();
                      }
                      return a.getGoalDifference() > b.getGoalDifference();
                  }
                  return a.getPoints() > b.getPoints(); // Sort in descending order of getPoints()
              });
    teams[0].setChampion(true);
    teams[1].setRunnerup(true);
    teams[2].setThirdPlace(true);
}
void displayAndLogResult(std::vector<football::Team> &teams)
{
    for (const auto &team : teams)
    {
        std::string seasonResult = team.getName() + " - Points: " + std::to_string(team.getPoints()) +
                                   " +/-: \t" + std::to_string(team.getGoalsScored()) + "/" + std::to_string(team.getGoalsConceded()) +
                                   ",\tWins: " + std::to_string(team.getWins()) + ",\tLosses: " + std::to_string(team.getLosses()) +
                                   ",\tDraws: " + std::to_string(team.getDraws());
        std::cout << seasonResult << std::endl;
        logEachSeason(seasonResult);
    }
}
void displayTop3Stand(std::vector<football::Team> teams)
{
    if (teams.size() > 3)
    {
        football::Team &champion = teams[0];
        football::Team &runnerUp = teams[1];
        football::Team &thirdPlace = teams[2];
        std::cout << "Champion: " << champion.getName() << " - Points: " << champion.getPoints() << std::endl;
        std::cout << "Runner-Up: " << runnerUp.getName() << " - Points: " << runnerUp.getPoints() << std::endl;
        std::cout << "Third Place: " << thirdPlace.getName() << " - Points: " << thirdPlace.getPoints() << std::endl;
    }
}
int main()
{
    std::cout << SEASON_START_MESSAGE;
    logEachSeason(SEASON_START_MESSAGE);
    std::vector<football::Team> teams = createTeams();
    std::vector<football::Match> schedule = scheduleRoundRobin(teams);
    createTeamTable(teams);
    // SQLite::Database db("TeamStatisticsDatabase.db", SQLite::OPEN_READWRITE);
    // Team vietnam = Team(1, "VietNam", 80);
    // vietnam.getWins()=44;
    // updateTeamInDatabase(vietnam);
    // displayAllTeamStatistic(teams);

    playTournamet(schedule);

    for (auto &team : teams)
    {
        team.calculatePoints();
        team.calculateGoalDifference();
        // updateTeamInDatabase(team);
    }
    SortTeam(teams);
    updateSeasonResultInDB(teams);
    displayAndLogResult(teams);
    logChampion(teams);
    displayAllTeamStatistic(teams);

    // saveDatabaseToFile("TeamStatisticsDatabase.db", "TeamStats.txt");

    // std::cout << SEASON_END_MESSAGE;
    logEachSeason(SEASON_END_MESSAGE);
    return 0;
}
