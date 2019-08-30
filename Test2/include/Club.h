#ifndef CLUB_H
#define CLUB_H

#include<string>
#include<vector>
#include"Player.h"

class Club
{
    public:
        Club();
        virtual ~Club();

        int points;
        int goalsScored;
        int goalsLost;

        int getClubId() { return clubId; }
        void setClubId(int val) { clubId = val; }
        std::string getName() { return name; }
        void setName(std::string val) { name = val; }
        int getBudget() { return budget; }
        void setBudget(int val) { budget = val; }
        int getPoints() { return points; }
        void setPoints(int val) { points = val; }
        int getPosition() { return position; }
        void setPosition(int val) { position = val; }
        int getLeagueId() { return leagueId; }
        void setLeagueId(int val) { leagueId = val; }
        std::vector<Player> getPlayers() { return players; }
        void setPlayers(std::vector<Player> val) { players = val; }
        int getPlayerClub() { return playerClub; }
        void setPlayerClub(int val) { playerClub = val; }
        int getGoalsScored() { return goalsScored; }
        void setGoalsScored(int val) { goalsScored = val; }
        int getGoalsLost() { return goalsLost; }
        void setGoalsLost(int val) { goalsLost = val; }
        int getWins() { return wins; }
        void setWins(int val) { wins = val; }
        int getDraws() { return draws; }
        void setDraws(int val) { draws = val; }
        int getLoses() { return loses; }
        void setLoses(int val) { loses = val; }

    protected:

    private:
        int clubId;
        std::string name;
        int budget;
        int position;
        int leagueId;
        std::vector<Player> players;
        int playerClub;
        int wins;
        int draws;
        int loses;
};

struct ClubComparator
{
	bool operator ()(const Club & club1, const Club & club2)
	{
		if(club1.points == club2.points)
			return ((club1.goalsScored - club1.goalsLost) > (club2.goalsScored - club2.goalsLost));
		return club1.points > club2.points;

	}
};

#endif // CLUB_H
