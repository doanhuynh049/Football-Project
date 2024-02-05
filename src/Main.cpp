#include <iostream>
#include <vector>
#include "Tournament.h"
#include <algorithm>
#include "DatabaseManagement.h"
const std::string SEASON_START_MESSAGE = "The season start: \n";
const std::string SEASON_END_MESSAGE = "The season terminated. \n";

void SortTeam(std::vector<Team> &teams)
{
    std::sort(teams.begin(), teams.end(), [](const Team &a, const Team &b)
              {
                  if (a.points == b.points)
                  {
                      if (a.goalDifference == b.goalDifference)
                      {
                          return a.goalsScored > b.goalsScored;
                      }
                      return a.goalDifference > b.goalDifference;
                  }
                  return a.points > b.points; // Sort in descending order of points
              });
    teams[0].champion = true;
    teams[1].runnerup = true;
    teams[2].thirdplace = true;
}
void displayAndLogResult(std::vector<Team> &teams)
{
    for (const auto &team : teams)
    {
        std::string seasonResult = team.name + " - Points: " + std::to_string(team.points) +
                                   " +/-: \t" + std::to_string(team.goalsScored) + "/" + std::to_string(team.goalsConceded) +
                                   ",\tWins: " + std::to_string(team.wins) + ",\tLosses: " + std::to_string(team.losses) +
                                   ",\tDraws: " + std::to_string(team.draws);
        std::cout << seasonResult << std::endl;
        logEachSeason(seasonResult);
    }
}
void displayTop3Stand(std::vector<Team> teams)
{
    if (teams.size() > 3)
    {
        Team &champion = teams[0];
        Team &runnerUp = teams[1];
        Team &thirdPlace = teams[2];
        std::cout << "Champion: " << champion.name << " - Points: " << champion.points << std::endl;
        std::cout << "Runner-Up: " << runnerUp.name << " - Points: " << runnerUp.points << std::endl;
        std::cout << "Third Place: " << thirdPlace.name << " - Points: " << thirdPlace.points << std::endl;
    }
}
int main()
{
    std::cout << SEASON_START_MESSAGE;
    logEachSeason(SEASON_START_MESSAGE);
    std::vector<Team> teams = createTeams();
    std::vector<Match> schedule = scheduleRoundRobin(teams);
    createTeamTable(teams);
    // SQLite::Database db("TeamStatisticsDatabase.db", SQLite::OPEN_READWRITE);
    // Team vietnam = Team(1, "VietNam", 80);
    // vietnam.wins=44;
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
