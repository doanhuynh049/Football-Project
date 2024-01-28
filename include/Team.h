#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <queue>
class Team {
	private:
		
	public:
		std::string name;
		float skillLevel;
		int wins;
		int losses;
		int draws;
		float form;
		float morale;
		int injuries;
		float effectiveSkill;

		Team(std::string name, int skill);
		std::queue<bool> recentResults;
		void updateForm(bool matchOutcome);
		void updateMorale(bool matchWon);
		void updateInjuries();
		
};
#endif 


