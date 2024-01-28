#include <iostream>
#include <vector>
#include "Tournament.h"
#include <algorithm>
int main()
{
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
        std::cout << team.name << " - Points: " << team.points
                  << " +/-: " << team.goalsScored << "/" << team.goalsConceded << ", Wins: "
                  << team.wins << ", Losses: " << team.losses << ", Draws: " << team.draws << std::endl;
    }
    if (teams.size()>3 ){
        Team &champion = teams[0];
        Team &runnerUp = teams[1];
        Team &thirdPlace = teams[2];
        std::cout << "Champion: " << champion.name << " - Points: " << champion.points << std::endl;
        std::cout << "Runner-Up: " << runnerUp.name << " - Points: " << runnerUp.points << std::endl;
        std::cout << "Third Place: " << thirdPlace.name << " - Points: " << thirdPlace.points << std::endl;
    }
    return 0;
}
