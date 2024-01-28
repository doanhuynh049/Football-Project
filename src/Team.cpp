#include "Team.h"

Team::Team(std::string name, float skill) : name(name),
                                          skillLevel(skill), wins(0), losses(0), draws(0),
                                          form(1.0), morale(1.0), injuries(0) {}

void Team::updateForm(bool matchOutcome)
{
    const size_t maxRecentResults = 5;
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
        injuries = std::min(injuries + 1, 5); // Max 5 injuries
    }
    else if (rand() % 10 < 3)
    {
        injuries = std::max(injuries - 1, 0); // Min 0 injuries
    }
}
