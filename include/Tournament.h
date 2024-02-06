#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include <vector>
#include "Team.h"
#include "Match.h"
#include "Logger.h"

std::vector<football::Team> createTeams();
std::vector<football::Match>scheduleRoundRobin(std::vector<football::Team>& teams);
void playTournamet(std::vector<football::Match>& schedule);
#endif