#include "Match.h"
#include "Team.h"
#include <random>

using namespace football;

void Match::playMatch()
{
#ifndef UNIT_TEST
    int maxGoalsPerHalf = 3;
    for (int half = 0; half < 2; half++)
    {
        score1 += std::min(calculateHalfTimeScore(team1->calculateEffectiveSkill()), maxGoalsPerHalf);
        score2 += std::min(calculateHalfTimeScore(team2->calculateEffectiveSkill()), maxGoalsPerHalf);
    }
#endif
    if (score1 > score2)
    {
        team1->winMatch();
        team2->lostMatch();
    }
    else if (score1 < score2)
    {
        team1->lostMatch();
        team2->winMatch();    
    }
    else
    {
        team1->drawMatch();
        team2->drawMatch();
    }
    team1->increaseGoalScored(score1);
    team2->increaseGoalConceded(score2);
    team2->increaseGoalScored(score2);
    team1->increaseGoalConceded(score1);
    
    // team1->goalsScored += score1;
    // team1->goalsConceded += score2;
    // team2->goalsScored += score2;
    // team2->goalsConceded += score1;
    // team1->updateInjuries();
    // team2->updateInjuries();
    std::cout << "Match Result: " << team1->getName() << " " << score1 << " - " << score2 << " " << team2->getName() << std::endl;
}
int Match::calculateHalfTimeScore(float effectiveSkill)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    float mean = std::min(effectiveSkill / 50.0f, 2.0f); // range: 0 - 2
    float stddev = 0.5f;
    std::normal_distribution<float> distr(mean, stddev);

    float noiseFactor = static_cast<float>(rand() % 5) - 2.0f; // range -2 - 2
    float fdistributedResult = static_cast<float>(distr(gen));
    float fcustimizedNoiseFactor = static_cast<float>(noiseFactor / 5.0f);
    float fscore = fdistributedResult + fcustimizedNoiseFactor;
    // int iscore = std::max(0, static_cast<int>(distr(gen))) + static_cast<int>(noiseFactor / 5.0f); // original =10.of
    int iscore = std::max(0, static_cast<int>(fscore + 0.5));
// float randomFactor = static_cast<float>(rand()%10)/10.0f;
// std::cout << randomFactor <<std::endl;
// return static_cast<int>(randomFactor*effectiveSkill / 100.f * 4);/
    #ifndef UNIT_TEST
    std::cout << "mean: " << mean << "\tnoiseFactor: " << noiseFactor  << std::endl;
    std::cout << "fdistributedResult: " << fdistributedResult << "\tfloat_noiseFactor: " << fcustimizedNoiseFactor << std::endl;
    std::cout << "fscore: " << fscore << "\tscore: " << iscore <<std::endl;
    #endif
    return iscore;
}
