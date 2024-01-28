#include "Match.h"
#include "Team.h"
#include <random>
void Match::playMatch(){
    int maxGoalsPerHalf = 3;
    for (int half = 0; half < 2; half ++){
        score1 += std::min(calculateHalfTimeScore(team1->calculateEffectiveSkill()), maxGoalsPerHalf);
        score2 += std::min(calculateHalfTimeScore(team2->calculateEffectiveSkill()), maxGoalsPerHalf);
    }
    if(score1 > score2){
        team1->wins++;
        team2->losses++;
        team1->updateForm(true);
        team1->updateMorale(true);
        team2->updateForm(false);
        team2->updateMorale(false);
    }
    else if(score1<score2){
        team1->losses++;
        team2->wins++;
        team2->updateForm(true);
        team2->updateMorale(true);
        team1->updateForm(false);
        team1->updateMorale(false);
    }
    else{
        team1->draws++;
        team2->draws++;
    }
    team1->updateInjuries();
    team2->updateInjuries();
    std::cout << "Match Result: " << team1->name << " " << score1 << " - " << score2 << " " << team2->name << std::endl;

}
int Match::calculateHalfTimeScore(float effectiveSkill){
    std::random_device rd;
    std::mt19937 gen(rd());
    float mean = std::min(effectiveSkill/50.0f, 2.0f);
    float stddev = 0.5f;
    std::normal_distribution<float>distr(mean,stddev);

    float noiseFactor = static_cast<float> (rand()% 5 ) - 2.0f;
    int score = std::max(0, static_cast<int>(distr(gen))) + static_cast<int> (noiseFactor / 10.0f);;

    // float randomFactor = static_cast<float>(rand()%10)/10.0f;
    // std::cout << randomFactor <<std::endl;
    // return static_cast<int>(randomFactor*effectiveSkill / 100.f * 4);/
    
    return std::max(0, score);
}
