#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include "Team.h"
bool ensureDirectoryExists(const std::string& dirPath);
void logMessage(const std::string & message);
void logChampion(std::vector<football::Team> teams);
void logEachSeason(const std::string& seasonresult);
#endif