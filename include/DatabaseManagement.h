
#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include "Team.h"
#ifndef DATABASE_MANAGEMENT_H
#define DATABASE_MANAGEMENT_H
const std::string CREATE_TABLE_SQL = "CREATE TABLE IF NOT EXISTS TEAM("
                                     "ID INT PRIMARY KEY NOT NULL, "
                                     "NAME TEXT NOT NULL , "
                                     "CHAMPION INTEGER, "
                                     "RUNNERUP INTEGER, "
                                     "THIRDPLACE INTEGER, "
                                     "WINS INTEGER, "
                                     "DRAWS INTEGER, "
                                     "LOSSES INTEGER, "
                                     "GOALSCORE INTEGER, "
                                     "GOALCONCEDED INTEGER );";
// static int selectCallback(void *data, int argc, char **argv, char **azColName);
void displayAllTeamStatistic(std::vector<football::Team> &teams);
void displayAllTeamStatistic(std::vector<football::Team> &teams);
void createTeamTable(std::vector<football::Team> &teams);
void saveDatabaseToFile(const std::string &dbPath, const std::string &outputPath);
void updateSeasonResultInDB(std::vector<football::Team> teams);

#endif