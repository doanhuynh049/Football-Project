#include "Match.h"
#include "Team.h"
void Match::playMatch(){
    srand(time(0));
    float randomFactor = static_cast<float>(rand()) / RAND_MAX;
    score1 = static_cast<int>(randomFactor * team1->skillLevel);
    score2 = static_cast<int>(randomFactor * team2->skillLevel);
    if(score1 > score2){
        result="Win for " + team1->name;
        team1->wins++;
        team2->losses++;
    }
    else if(score1<score2){
        result="Win for "+team2->name;
        team1->losses--;
        team2->wins++;
    }
    else{
        result="Draw";
        team1->draws++;
        team2->draws++;
    }
}
