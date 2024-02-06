#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Team.h"
namespace football{
class Match {
    public: 
        Team* team1;
        Team* team2;
        int score1;
        int score2;
        std::string result;
        Match(Team* t1, Team* t2):
            team1(t1), team2(t2), score1(0), score2(0), result(""){}
        void playMatch();
        int calculateHalfTimeScore(float effectiveSkill);
};
}
