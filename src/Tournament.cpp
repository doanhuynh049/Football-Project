#include "Tournament.h"
#include <iostream>

std::vector<football::Team> createTeams()
{
    std::vector<football::Team> teams = {
        football::Team(1, "VietNam  ", 80),
        football::Team(2, "ThaiLand ", 80),
        football::Team(3, "Malaisia ", 80),
        football::Team(4, "Indonesia", 80),
        football::Team(5, "Singapore", 80),
        football::Team(6, "Myanmar  ", 80),
        football::Team(7, "Philipin ", 80),
        football::Team(8, "Campuchia", 80),
        football::Team(9, "Australia", 80),
};
        
    return teams;
}
std::vector<football::Match> scheduleRoundRobin(std::vector<football::Team> &teams)
{
    std::vector<football::Match> schedule;
    for (size_t i = 0; i < teams.size(); i++)
    {
        for (size_t j = i + 1; j < teams.size(); j++)
        {
            schedule.push_back(football::Match(&teams[i], &teams[j]));
        }
    }
    return schedule;
}
void playTournamet(std::vector<football::Match> &schedule)
{
    for (football::Match &match : schedule)
    {
        match.playMatch();
    }
}