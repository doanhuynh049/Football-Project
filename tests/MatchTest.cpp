#include <gtest/gtest.h>
#include "Match.h"


class MatchTest : public ::testing:: Test{
    protected:
        Team *team1, *team2;
        Match *match;
    void SetUp() override{
        team1 = new Team(1,"VietNam", 60);
        team2 = new Team(2, "Thailand", 50);
        match = new Match(team1, team2);
    }
    void TearDown() override{
        delete team1;
        delete team2;
        delete match;
    }
};
TEST_F(MatchTest, Constructor){
    EXPECT_EQ(match->score1, 0);
    EXPECT_EQ(match->score2, 0);
}
//Normal test case
TEST_F(MatchTest, PlayMatchResult){
    match->score1 = 1;
    match->score2 = 0;
    match->playMatch();
    EXPECT_EQ(team1->wins, 1);
    EXPECT_EQ(team2->wins, 0);
    EXPECT_EQ(team1->losses, 0);
    EXPECT_EQ(team2->losses, 1);
    EXPECT_EQ(team1->draws, 0);
    EXPECT_EQ(team2->draws, 0);
    EXPECT_EQ(team1->goalsScored, match->score1);
    EXPECT_EQ(team2->goalsScored, match->score2);
    EXPECT_EQ(team2->goalsConceded, match->score1);
    EXPECT_EQ(team1->goalsConceded, match->score2);
}
//Normal test case
TEST_F(MatchTest, PlayMatchResult_1){
    match->score1 = 1;
    match->score2 = 2;
    match->playMatch();
    EXPECT_EQ(team1->wins, 0);
    EXPECT_EQ(team2->wins, 1);
    EXPECT_EQ(team1->losses, 1);
    EXPECT_EQ(team2->losses, 0);
    EXPECT_EQ(team1->draws, 0);
    EXPECT_EQ(team2->draws, 0);
    EXPECT_EQ(team1->goalsScored, match->score1);
    EXPECT_EQ(team2->goalsScored, match->score2);
    EXPECT_EQ(team2->goalsConceded, match->score1);
    EXPECT_EQ(team1->goalsConceded, match->score2);
}
//Normal test case
TEST_F(MatchTest, PlayMatchResult_2){
    match->score1 = 2;
    match->score2 = 2;
    match->playMatch();
    EXPECT_EQ(team1->wins, 0);
    EXPECT_EQ(team2->wins, 0);
    EXPECT_EQ(team1->losses, 0);
    EXPECT_EQ(team2->losses, 0);
    EXPECT_EQ(team1->draws, 1);
    EXPECT_EQ(team2->draws, 1);
    EXPECT_EQ(team1->goalsScored, match->score1);
    EXPECT_EQ(team2->goalsScored, match->score2);
    EXPECT_EQ(team2->goalsConceded, match->score1);
    EXPECT_EQ(team1->goalsConceded, match->score2);
}
//Boundary test case
TEST_F(MatchTest, PlayMatchResult_3){
    match->score1 = 0;
    match->score2 = 0;
    match->playMatch();
    EXPECT_EQ(team1->wins, 0);
    EXPECT_EQ(team2->wins, 0);
    EXPECT_EQ(team1->losses, 0);
    EXPECT_EQ(team2->losses, 0);
    EXPECT_EQ(team1->draws, 1);
    EXPECT_EQ(team2->draws, 1);
    EXPECT_EQ(team1->goalsScored, match->score1);
    EXPECT_EQ(team2->goalsScored, match->score2);
    EXPECT_EQ(team2->goalsConceded, match->score1);
    EXPECT_EQ(team1->goalsConceded, match->score2);
}

//Abnormal test case
TEST_F(MatchTest, PlayMatchResult_5){
    match->score1 = -1;
    match->score2 = -1; 
    match->playMatch();
    EXPECT_EQ(team1->wins, 0);
    EXPECT_EQ(team2->wins, 0);
    EXPECT_EQ(team1->losses, 0);
    EXPECT_EQ(team2->losses, 0);
    EXPECT_EQ(team1->draws, 0);
    EXPECT_EQ(team2->draws, 0);
    EXPECT_EQ(team1->goalsScored, match->score1);
    EXPECT_EQ(team2->goalsScored, match->score2);
    EXPECT_EQ(team2->goalsConceded, match->score1);
    EXPECT_EQ(team1->goalsConceded, match->score2);
}
//Abnormal test case (Need to fix segmentation fault)
// TEST_F(MatchTest, PlayMatchResult_6){
//     Team* team3 = nullptr;
//     Team* team4 = nullptr;
//     Match* match1;
//     match1 = new Match(team3, team4);
//     match1->playMatch();
// }

// Normal test case
TEST_F(MatchTest, calculateHalfTimeScore){
    team1->effectiveSkill = 80;
    int score = match->calculateHalfTimeScore(team1->effectiveSkill);
    EXPECT_GE(score, 0);
    EXPECT_LE(score, 3);
}

// Normal test case
TEST_F(MatchTest, calculateHalfTimeScore_1){
    team1->effectiveSkill = 0;
    int score = match->calculateHalfTimeScore(team1->effectiveSkill);
    EXPECT_GE(score, 0);
    EXPECT_LE(score, 1);
}
// Abnormal test case
TEST_F(MatchTest, calculateHalfTimeScore_2){
    team1->effectiveSkill = -50;
    int score = match->calculateHalfTimeScore(team1->effectiveSkill);
    EXPECT_GE(score, 0);
    EXPECT_LE(score, 1);
}