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
                  return a.points > b.points; // Sort in descending order of points
              });

    for (const auto &team : teams)
    {
        std::cout << team.name << " - Points: " << team.points 
                << " +/-: " << team.goalsScored << "/" << team.goalsConceded << ", Wins: " 
                << team.wins << ", Losses: " << team.losses << ", Draws: " << team.draws << std::endl;
    }

    return 0;
}
