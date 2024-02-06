#include "Team.h"
using namespace football;
Team::Team(int id, std::string name, float skillLevel) : id(id), name(name),
                                                         skillLevel(skillLevel), wins(0), losses(0), draws(0),
                                                         form(1.0), morale(1.0), injuries(0), points(0),
                                                         goalsScored(0), goalsConceded(0), goalDifference(0) {}
unsigned int Team::getID() const
{
    return id;
}
std::string Team::getName() const
{
    return name;
}
unsigned int Team::getSkillLevel() const
{
    return skillLevel;
}
unsigned int Team::getWins() const
{
    return wins;
}
unsigned int Team::getLosses() const
{
    return losses;
}
unsigned int Team::getDraws() const
{
    return draws;
}
float Team::getForm() const
{
    return form;
}
float Team::getMorale() const
{
    return morale;
}
unsigned int Team::getInjuries() const
{
    return injuries;
}
float Team::getEffectiveSkill() const
{
    return effectiveSkill;
}
unsigned int Team::getPoints() const
{
    return points;
}
unsigned int Team::getGoalsScored() const
{
    return goalsScored;
}
unsigned int Team::getGoalsConceded() const
{
    return goalsConceded;
}
int Team::getGoalDifference() const
{
    return goalDifference;
}
bool Team::isChampion() const
{
    return champion;
}
bool Team::isRunnerUp() const
{
    return runnerUp;
}
bool Team::isThirdPlace() const
{
    return thirdPlace;
}

void Team::setID(unsigned int value)
{
    id = value;
}
void Team::setName(std::string namestring)
{
    name = namestring;
}
void Team::setSkillLevel(unsigned int value)
{
    skillLevel = value;
}
void Team::setWins(unsigned int value)
{
    wins = value;
}
void Team::setLosses(unsigned int value) {
    losses = value;
}
void Team::setDraws(unsigned int value) {
    draws = value;
}
void Team::setForm(float value) {
    form = value;
}
void Team::setMorale(float value) {
    morale = value;
}
void Team::setInjuries(unsigned int value) {
    injuries = value;
}
void Team::setEffectiveSkill(float value) {
    effectiveSkill = value;
}
void Team::setPoints(int value) {
    points = value;
}
void Team::setGoalsScored(unsigned int value) {
    goalsScored =value;
}
void Team::setGoalsConceded(unsigned int value) {
    goalsConceded = value;
}
void Team::setGoalDifference(int value) {
    goalDifference = value;
}
void Team::setChampion(bool newchampion) {
    champion = newchampion;
}
void Team::setRunnerup(bool newrunnerup) {
    runnerUp = newrunnerup;
}
void Team::setThirdPlace(bool newthirdplace) {
    thirdPlace = newthirdplace;
}

void Team::updateForm(bool matchOutcome)
{
    const float maxRecentResults = 5;
    if (recentResults.size() >= maxRecentResults)
    {
        recentResults.pop();
    }
    recentResults.push(matchOutcome);
    // The number of wins (true values) in the recentResults queue is counted.
    int wins = 0;
    std::queue<bool> tempQueue = recentResults;
    while (!tempQueue.empty())
    {
        if (tempQueue.front())
            wins++;
        tempQueue.pop();
    }
    // The form is calculated based on these wins. It starts at a base of 0.8 (representing a baseline form) and increases by 0.1 for each win, proportionate to the maximum number of recent results considered.
    form = 0.8 + 0.1 * (static_cast<float>(wins) / maxRecentResults);
}
void Team::updateMorale(bool matchWon)
{
    if (matchWon)
    {
        morale = std::min(morale + 0.1f, 1.2f);
    }
    else
    {
        morale = std::max(morale - 0.1f, 0.8f);
    }
}
void Team::updateInjuries()
{
    if (rand() % 10 < 2)
    {                                         // 20% chance of new injury
        injuries = std::min(static_cast<int> (injuries + 1), 5); // Max 5 injuries
    }
    else if (rand() % 10 < 3)
    {
        injuries = std::max(static_cast<int> (injuries - 1), 0); // Min 0 injuries
    }
}
float Team::calculateEffectiveSkill()
{
    float formFactor = std::max(0.8f, std::min(form, 1.2f));
    float moraleFactor = std::max(0.8f, std::min(morale, 1.2f));
    int injuryCount = std::max(0, std::min(static_cast<int> (injuries), 5));
    float injuryPenaltyFactor = 1.0f - (injuryCount * 0.05f);
    float effectiveSkill = skillLevel * formFactor * moraleFactor * injuryPenaltyFactor;
    effectiveSkill = std::max(0.0f, std::min(effectiveSkill, 100.0f));
    return effectiveSkill;
}
void Team::calculatePoints()
{
    points = wins * 3 + draws;
}

void Team::calculateGoalDifference()
{
    goalDifference = goalsScored - goalsConceded;
}
void Team::winMatch(){
    wins++;
    updateForm(true);
    updateMorale(true);
    updateInjuries();
}
void Team::lostMatch(){
    losses++;
    updateForm(false);
    updateMorale(false);
    updateInjuries();
}
void Team::drawMatch(){
    draws++;
    updateInjuries();
}
void Team::increaseGoalScored(unsigned int score){
    goalsScored += score;
}
void Team::increaseGoalConceded(unsigned int goalagainst){
    goalsConceded += goalagainst;
}