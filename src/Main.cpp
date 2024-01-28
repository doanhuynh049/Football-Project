#include <iostream>
#include <vector>
#include "Tournament.h"

int main(){
    std::vector <Team> teams = createTeams();
    std::vector<Match> schedule = scheduleRoundRobin(teams);
    playTournamet(schedule);
    for (const auto& team: teams){
        std::cout << team.name << " - Wins: " << team.wins << ", Losses: " << team.losses << ", Draws: " << team.draws << std::endl;
    }
    return 0;
}
