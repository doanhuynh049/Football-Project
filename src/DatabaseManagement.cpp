#include "DatabaseManagement.h"


static int selectCallback(void *data, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\t";
    }
    std::cout << std::endl;
    return 0;
}
void displayAllTeamStatistic(std::vector<Team> &teams)
{
    sqlite3 *db;
    int rc = sqlite3_open("TeamStatisticsDatabase.db", &db);
    if (rc)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Exiting createTeamTable (database error)" << std::endl;
        return;
    }
    for (auto &team : teams)
    {
        const std::string SELECT_DATA_SQL = "SELECT * FROM TEAM WHERE ID = " + std::to_string(team.id) + ";";
        rc = sqlite3_exec(db, SELECT_DATA_SQL.c_str(), selectCallback, 0, 0);
        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    }
}
void createTeamTable(std::vector<Team> &teams)
{
    std::cout << "Entering createTeamTable" << std::endl;
    std::ifstream dbFile("TeamStatisticsDatabase.db");
    if (dbFile.good())
    {
        std::cout << "Database file already exists, skipping table creation." << std::endl;
        return;
    }
    sqlite3 *db;
    int rc = sqlite3_open("TeamStatisticsDatabase.db", &db);
    if (rc)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Exiting createTeamTable (database error)" << std::endl;
        return;
    }

    std::cout << "Database opened successfully" << std::endl;

    char *messageError;
    rc = sqlite3_exec(db, CREATE_TABLE_SQL.c_str(), NULL, 0, &messageError);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error creating table: " << messageError << std::endl;
        sqlite3_free(messageError);
        std::cout << "Exiting createTeamTable (table creation error)" << std::endl;
    }
    else
    {
        std::cout << "Table created successfully" << std::endl;
    }
    for (auto &team : teams)
    {
        int champions = 0, runnerUp = 0, thirPlace = 0;
        const std::string INSERT_DATA_SQL = "INSERT INTO TEAM (ID, NAME, CHAMPION, RUNNERUP, THIRDPLACE, WINS, DRAWS, LOSSES, GOALSCORE, GOALCONCEDED)"
                                            "VALUES (" +
                                            std::to_string(team.id) + ",'" + team.name + "'," + std::to_string(champions) + ", " + std::to_string(runnerUp) + ", " +
                                            std::to_string(thirPlace) + ", " + std::to_string(team.wins) + ", " + std::to_string(team.wins) + ", " +
                                            std::to_string(team.draws) + ", " + std::to_string(team.losses) + ", " + std::to_string(team.goalsScored) +
                                            std::to_string(team.goalsConceded) + ");";
        rc = sqlite3_exec(db, INSERT_DATA_SQL.c_str(), 0, 0, 0);
        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        const std::string SELECT_DATA_SQL = "SELECT * FROM TEAM WHERE ID = " + std::to_string(team.id) + ";";
        rc = sqlite3_exec(db, SELECT_DATA_SQL.c_str(), selectCallback, 0, 0);
        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
    }
    std::cout << "Exiting createTeamTable" << std::endl;
    sqlite3_close(db);
}


void updateSeasonResultInDB(std::vector<Team> teams){
    std::cout << "Entering updateTeamInDatabase" << std::endl;

    try
    {
        sqlite3 *db;
        int rc = sqlite3_open("TeamStatisticsDatabase.db", &db);
        if (rc)
        {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        for (auto &team : teams)
        {
            const std::string SELECT_DATA_SQL = "SELECT CHAMPION, RUNNERUP, THIRDPLACE, WINS, DRAWS, LOSSES, GOALSCORE, GOALCONCEDED FROM TEAM WHERE ID = " + std::to_string(team.id) + ";";
            std::map<std::string, int> currentValues;
            rc = sqlite3_exec(
                db, SELECT_DATA_SQL.c_str(), [](void *data, int argc, char **argv, char **azColName) -> int
                {
                auto& currentValues = *reinterpret_cast<std::map<std::string, int>*>(data);
                for(int i =0; i <argc; i++){
                    currentValues[azColName[i]] = std::stoi(argv[i]);
                }
                return 0; },
                &currentValues, 0);
            if (rc != SQLITE_OK)
            {
                std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
                return;
            }
            currentValues["CHAMPION"] += team.champion ? 1 : 0;
            currentValues["RUNNERUP"] += team.runnerup ? 1 : 0;
            currentValues["THIRDPLACE"] += team.thirdplace ? 1 : 0;
            currentValues["WINS"] += team.wins;
            currentValues["DRAWS"] += team.draws;
            currentValues["LOSSES"] += team.losses;
            currentValues["GOALSCORE"] += team.goalsScored;
            currentValues["GOALCONCEDED"] += team.goalsConceded;
            // Construct the INSERT statement with the updated values
            const std::string INSERT_DATA_SQL = "REPLACE INTO TEAM (ID, NAME, CHAMPION, RUNNERUP, THIRDPLACE, WINS, DRAWS, LOSSES, GOALSCORE, GOALCONCEDED) "
                                                "VALUES (" +
                                                std::to_string(team.id) + ", '" + team.name + "', " + std::to_string(currentValues["CHAMPION"]) + ", " + std::to_string(currentValues["RUNNERUP"]) + ", " + std::to_string(currentValues["THIRDPLACE"]) + ", " + std::to_string(currentValues["WINS"]) + ", " + std::to_string(currentValues["DRAWS"]) + ", " + std::to_string(currentValues["LOSSES"]) + ", " + std::to_string(currentValues["GOALSCORE"]) + ", " + std::to_string(currentValues["GOALCONCEDED"]) + ");";
            rc = sqlite3_exec(db, INSERT_DATA_SQL.c_str(), 0, 0, 0);

            if (rc != SQLITE_OK)
            {
                std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
                return;
            }
        }
        // const std::string SELECT_DATA_SQL_1 = "SELECT * FROM TEAM WHERE ID = " + std::to_string(team.id) + ";";
        // rc = sqlite3_exec(db, SELECT_DATA_SQL_1.c_str(), selectCallback, 0, 0);
        // if (rc != SQLITE_OK)
        // {
        //     std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        //     return;
        // }
    }
    catch (const std::exception &e)
    {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
    std::cout << "Exiting updateTeamInDatabase" << std::endl;
    return;
}
void saveDatabaseToFile(const std::string &dbPath, const std::string &outputPath)
{
    sqlite3 *db;
    if (sqlite3_open(dbPath.c_str(), &db))
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, "SELECT * FROM TEAM", -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Error preparing SELECT statement" << std::endl;
        sqlite3_close(db);
        return;
    }

    std::ofstream file(outputPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for writing" << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        for (int i = 0; i < sqlite3_column_count(stmt); ++i)
        {
            file << reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)) << (i == sqlite3_column_count(stmt) - 1 ? "\n" : ", ");
        }
    }

    file.close();
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout << "Data saved to " << outputPath << std::endl;
}
