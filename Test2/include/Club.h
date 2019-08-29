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

    protected:

    private:
        int clubId;
        std::string name;
        int budget;
        int points;
        int position;
        int leagueId;
        std::vector<Player> players;
        int playerClub;
        int goalsScored;
        int goalsLost;
};

#endif // CLUB_H
