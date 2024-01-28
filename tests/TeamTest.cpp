#include <gtest/gtest.h>
#include "Team.h"

class TeamTest : public ::testing::Test
{
protected:
    Team *team;

    void SetUp() override
    {
        team = new Team("Viet Nam", 50);
    }
    void TearDown() override
    {
        delete team;
    }
};
TEST_F(TeamTest, Constructor)
{
    EXPECT_EQ(team->name, "Viet Nam");
    EXPECT_EQ(team->skillLevel, 50);
    EXPECT_EQ(team->wins, 0);
    EXPECT_EQ(team->losses, 0);
    EXPECT_EQ(team->draws, 0);
}
TEST_F(TeamTest, updateForm)
{
    team->updateForm(true);
    team->updateForm(true);
    team->updateForm(false);
    team->updateForm(true);
    team->updateForm(false);
    EXPECT_GE(team->form, 0.86);
}
TEST_F(TeamTest, updateMorale)
{
    team->updateMorale(true);
    EXPECT_GT(team->morale, 1);
}
TEST_F(TeamTest, updateMorale_1)
{
    team->updateMorale(false);
    EXPECT_LT(team->morale, 1);
}
TEST_F(TeamTest, updateMorale_2)
{
    team->updateMorale(true);
    team->updateMorale(true);
    team->updateMorale(true);
    EXPECT_NEAR(team->morale, 1.2, 0.1);
}
TEST_F(TeamTest, updateInjuries)
{
    for (int i = 0; i < 100; i++)
    {
        team->updateInjuries();
        // std::cout << team->injuries;
    }
    EXPECT_LE(team->injuries, 5);
    EXPECT_GE(team->injuries, 0);
}
TEST_F(TeamTest, calculateEffectiveSkill_HighFormAndMorale)
{
    team->form = 1.2;
    team->morale = 1.2;
    float expectedSkill = 50.0f * 1.2f * 1.2f;
    EXPECT_EQ(team->calculateEffectiveSkill(), expectedSkill);
}
TEST_F(TeamTest, CalculateEffectiveSkill_LowFormAndMorale)
{
    team->form = 0.8f;
    team->morale = 0.8f;
    float expectedSkill = 50.0f * 0.8f * 0.8f;
    EXPECT_EQ(team->calculateEffectiveSkill(), expectedSkill);
}
TEST_F(TeamTest, CalculateEffectiveSkill_WithInjuries) {
    team->injuries = 3;   // 3 injuries
    float injuryPenaltyFactor = 1.0f - (3 * 0.05f);
    float expectedSkill = 50.0f * 1.0f * 1.0f * injuryPenaltyFactor;  // Decreased due to injuries
    EXPECT_FLOAT_EQ(team->calculateEffectiveSkill(), expectedSkill);
}
TEST_F(TeamTest, CalculateEffectiveSkill_MaxSkillCap) {
    team->skillLevel = 120.0f;  // Over the usual max cap
    float expectedSkill = 100.0f;  // Should be capped at 100
    EXPECT_FLOAT_EQ(team->calculateEffectiveSkill(), expectedSkill);
}
// g++ -o team_test TeamTest.cpp Team.cpp -lgtest -lgtest_main -pthread