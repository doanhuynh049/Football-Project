#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <queue>
class Team {
	private:
		
	public:
		int id;
		std::string name;
		float skillLevel;
		int wins;
		int losses;
		int draws;
		float form;
		float morale;
		int injuries;
		float effectiveSkill;
		int points;
		int goalsScored;
		int goalsConceded;
		int goalDifference;
		bool champion = false;
		bool runnerup = false;
		bool thirdplace = false;
		Team(int id, std::string name, float skillLevel);
		std::queue<bool> recentResults;
		void updateForm(bool matchOutcome);
		void updateMorale(bool matchWon);
		void updateInjuries();
		float calculateEffectiveSkill();
		void calculatePoints();
		void calculateGoalDifference();
};
#endif 


