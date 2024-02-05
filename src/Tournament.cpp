#include "Tournament.h"
#include <iostream>

std::vector<Team> createTeams()
{
    std::vector<Team> teams = {
        Team(1, "VietNam  ", 80),
        Team(2, "ThaiLand ", 80),
        Team(3, "Malaisia ", 80),
        Team(4, "Indonesia", 80),
        Team(5, "Singapore", 80),
        Team(6, "Myanmar  ", 80),
        Team(7, "Philipin ", 80),
        Team(8, "Campuchia", 80),
        Team(9, "Australia", 80),
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