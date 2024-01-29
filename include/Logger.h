#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include "Team.h"
void logMessage(const std::string & message);
void logChampion(std::vector<Team> teams);
void logEachSeason(const std::string& seasonresult);
#endif