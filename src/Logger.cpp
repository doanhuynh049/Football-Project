#include "Logger.h"
#include <fstream>
#include <iostream>
#include "Team.h"
#include <sys/stat.h>

bool ensureDirectoryExists(const std::string& dirPath){
    struct stat info;       // how information about the file at the given path
    if(stat(dirPath.c_str(),&info)!=0){
        return mkdir(dirPath.c_str(), 0777) == 0;
    }
    return (info.st_mode & S_IFDIR) != 0;   //It returns true if it's a directory, and false otherwise.
}
void logMessage(const std::string& message){
    std::ofstream logFile("tournament_log.txt", std::ios::app);
    if(!logFile.is_open()){
        std::cerr << "Unable to open logile/" <<std::endl;
        return ;
    }
    logFile << message << std::endl;
}
// Function to log the champion of a season
void logChampion(std::vector<football::Team> teams){
    const std::string logDir = "logs";
    const std::string logFilePath = logDir + "/champion_log.txt";
    ensureDirectoryExists(logDir);
    std::ofstream logFile(logFilePath, std::ios::app);
    if(logFile.is_open()){
        logFile << "Champion: " << teams[0].getName() << " - Points: " << teams[0].getPoints() 
                << " +/-: " << teams[0].getGoalsScored() - teams[0].getGoalsConceded() << ", Wins: " 
                << teams[0].getWins() << ", Losses: " << teams[0].getLosses() << ", Draws: " << teams[0].getDraws() << std::endl;
    }
    else {
        std::cerr << "Unable to open logile/" <<std::endl;
        return ;
    }
}
void logEachSeason(const std::string& seasonresult){
    const std::string logDir = "logs";
    const std::string logFilePath = logDir + "/Season_log.txt";
    ensureDirectoryExists(logDir);
    std::ofstream logFile(logFilePath, std::ios::app);
    if(logFile.is_open()){
        logFile << seasonresult <<std::endl;
    }
    else {
        std::cerr << "Unable to open logile/" <<std::endl;
        return ;
    }
}