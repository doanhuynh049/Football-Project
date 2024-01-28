#include <gtest/gtest.h>
#include "Match.h"


class MatchTest : public ::testing:: Test{
    protected:
        Team *team1, *team2;
        Match *match;
    void SetUp() override{
        team1 = new Team("VietNam", 60);
        team2 = new Team("Thailand", 50);
        match = new Match(team1, team2);
    }
    void TearDown() override{
        delete team1;
        delete team2;
        delete match;
    }
};

TEST_F(MatchTest, PlayMatchResult){
    match->playMatch();
}