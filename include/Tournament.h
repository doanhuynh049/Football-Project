#ifndef TOURNAMENT_H
#define TOURNAMENT_H
#include <vector>
#include "Team.h"
#include "Match.h"
#include "Logger.h"

std::vector<Team> createTeams();
std::vector<Match>scheduleRoundRobin(std::vector<Team>& teams);
void playTournamet(std::vector<Match>& schedule);
#endif