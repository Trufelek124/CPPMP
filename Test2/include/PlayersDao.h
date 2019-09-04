#ifndef PLAYERSDAO_H
#define PLAYERSDAO_H

#include"Player.h"
#include<vector>
#include <sqlite3.h>
#include <iostream>

class PlayersDao
{
    public:
        PlayersDao();
        virtual ~PlayersDao();

        sqlite3* DB;
        int exit;
        sqlite3_stmt* stmt;
        int row = 0;
        int bytes;
        Player* playerTmp;
        char q[999];

        std::vector<Player> getPlayers();
        Player getPlayer(int playerId);
        std::vector<Player> getPlayersForClub(int clubIdQuery);
        std::vector<Player> getPlayersForPlayersClub();
        std::vector<Player> getPlayersForPosition(std::string positionVar);
        int savePlayer(Player playerVar);
        void updatePlayer(Player playerVar);

    protected:

    private:
        const unsigned char* id;
        const unsigned char* name;
        const unsigned char* position;
        const unsigned char* matchsquad;
        const unsigned char* clubId;
        const unsigned char* age;
        const unsigned char* nettWorth;
        const unsigned char* handling;
        const unsigned char* diving;
        const unsigned char* kicking;
        const unsigned char* reflexes;
        const unsigned char* tackling;
        const unsigned char* heading;
        const unsigned char* marking;
        const unsigned char* intercepting;
        const unsigned char* vision;
        const unsigned char* crossing;
        const unsigned char* shortPasses;
        const unsigned char* longPasses;
        const unsigned char* freeKicks;
        const unsigned char* positioning;
        const unsigned char* finishing;
        const unsigned char* power;
        const unsigned char* volleys;
        const unsigned char* longShots;
        const unsigned char* trainingType;

        std::string idString;
        std::string nameString;
        std::string positionString;
        std::string matchsquadString;
        std::string clubIdString;
        std::string ageString;
        std::string nettWorthString;
        std::string handlingString;
        std::string divingString;
        std::string kickingString;
        std::string reflexesString;
        std::string tacklingString;
        std::string headingString;
        std::string markingString;
        std::string interceptingString;
        std::string visionString;
        std::string crossingString;
        std::string shortPassesString;
        std::string longPassesString;
        std::string freeKicksString;
        std::string positioningString;
        std::string finishingString;
        std::string powerString;
        std::string volleysString;
        std::string longShotsString;
        std::string trainingTypeString;

        void playerFromStatement(sqlite3_stmt* stmt);
};

#endif // PLAYERSDAO_H
