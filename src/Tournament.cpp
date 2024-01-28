#include "Tournament.h"
#include <iostream>

std::vector<Team> createTeams()
{
    std::vector<Team> teams = {
        Team("VietNam", 80),
        Team("ThaiLand", 60),
        Team("Malaisia", 65),
        Team("Indonesia", 64),
        Team("Singapore", 40),
        Team("Myanmar", 45),
        Team("Philipin", 42),
        Team("Campuchia", 20),
        Team("Australia", 100),
};
        
    return teams;
}
std::vector<Match> scheduleRoundRobin(std::vector<Team> &teams)
{
    std::vector<Match> schedule;
    for (size_t i = 0; i < teams.size(); i++)
    {
        for (size_t j = i + 1; j < teams.size(); j++)
        {
            schedule.push_back(Match(&teams[i], &teams[j]));
        }
    }
    return schedule;
}
void playTournamet(std::vector<Match> &schedule)
{
    for (Match &match : schedule)
    {
        match.playMatch();
    }
}