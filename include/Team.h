#ifndef FOOTBALL_TEAM_H
#define FOOTBALL_TEAM_H
#include <iostream>
#include <queue>
// #pragma once
namespace football{
class Team {
	private:
		unsigned int id;
		std::string name;
		unsigned int skillLevel;
		unsigned int wins;
		unsigned int losses;
		unsigned int draws;
		float form;
		float morale;
		unsigned int injuries;
		float effectiveSkill;
		unsigned int points;
		unsigned int goalsScored;
		unsigned int goalsConceded;
		int goalDifference;
		bool champion = false;
		bool runnerUp = false;
		bool thirdPlace = false;
	public:
    	// Accessors (Getters)
		unsigned int getID() const;
		std::string getName() const;
		unsigned int getSkillLevel() const;
		unsigned int getWins() const;
		unsigned int getLosses() const;
		unsigned int getDraws() const;
		float getForm() const;
		float getMorale() const;
		unsigned int getInjuries() const;
		float getEffectiveSkill() const;
		unsigned int getPoints() const;
		unsigned int getGoalsScored() const;
		unsigned int getGoalsConceded() const;
		int getGoalDifference() const;
		bool isChampion() const;
		bool isRunnerUp() const;
		bool isThirdPlace() const;

    	// Mutators (Setters)
		void setID(unsigned int value);
		void setName(std::string namestring);
		void setSkillLevel(unsigned int value );
		void setWins(unsigned int value);
		void setLosses(unsigned int value);
		void setDraws(unsigned int value);
		void setForm(float value);
		void setMorale(float value);
		void setInjuries(unsigned int value);
		void setEffectiveSkill(float value);
		void setPoints(int value);
		void setGoalsScored(unsigned int value);
		void setGoalsConceded(unsigned int value);
		void setGoalDifference(int value);
		void setChampion(bool champion);
		void setRunnerup(bool runnerUp);
		void setThirdPlace(bool thirdPlace);

		explicit Team(int id, std::string name, float skillLevel);
		std::queue<bool> recentResults;
		void updateForm(bool matchOutcome);
		void updateMorale(bool matchWon);
		void updateInjuries();
		float calculateEffectiveSkill();
		void calculatePoints();
		void calculateGoalDifference();
		void winMatch();
		void lostMatch();
		void drawMatch();
		void increaseGoalScored(unsigned int score);
		void increaseGoalConceded(unsigned int goalagainst);
};
}
#endif 


