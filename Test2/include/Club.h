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
        int getTactics() { return tactics; }
        std::string getTacticsString() {
            if(tactics == 1)
                return "ultradeffensive";
            else if(tactics == 2)
                return "deffensive";
            else if(tactics == 3)
                return "balanced";
            else if(tactics == 4)
                return "offensive";
            else
                return "ultraoffensive";
        }
        void setTactics(int val) { tactics = val; }

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
        int tactics; //1 - 5: 1 - ultra deffensive, 5 - ultra offensive
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
