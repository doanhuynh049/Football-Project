#include <iostream>
#include <vector>
#include "Tournament.h"
#include <algorithm>
#include "DatabaseManagement.h"

int main()
{
    std::string message = "The season start: \n";
    std::cout << message;
    logEachSeason(message);
    std::vector<Team> teams = createTeams();
    std::vector<Match> schedule = scheduleRoundRobin(teams);
    playTournamet(schedule);
    for (auto &team : teams)
    {
        team.calculatePoints();
        team.calculateGoalDifference();
    }
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
    
    for (const auto &team : teams)
    {
        std::string seasonResult = team.name + " - Points: " + std::to_string(team.points) +
                              " +/-: " + std::to_string(team.goalsScored) + "/" + std::to_string(team.goalsConceded) +
                              ", Wins: " + std::to_string(team.wins) + ", Losses: " + std::to_string(team.losses) +
                              ", Draws: " + std::to_string(team.draws);
        std::cout << seasonResult << std::endl;
        logEachSeason(seasonResult);

    }
    if (teams.size()>3 ){
        Team &champion = teams[0];
        Team &runnerUp = teams[1];
        Team &thirdPlace = teams[2];
        std::cout << "Champion: " << champion.name << " - Points: " << champion.points << std::endl;
        std::cout << "Runner-Up: " << runnerUp.name << " - Points: " << runnerUp.points << std::endl;
        std::cout << "Third Place: " << thirdPlace.name << " - Points: " << thirdPlace.points << std::endl;
    }
    logChampion(teams);
    message = "The season terminated. \n";
    std::cout << message << std::endl;
    logEachSeason(message);
    return 0;
}
