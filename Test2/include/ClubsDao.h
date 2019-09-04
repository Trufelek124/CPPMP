#ifndef CLUBSDAO_H
#define CLUBSDAO_H

#include"Club.h"
#include<vector>
#include <sqlite3.h>
#include <iostream>
#include <string>

class ClubsDao
{
    public:
        ClubsDao();
        virtual ~ClubsDao();

        sqlite3* DB;
        int exit;
        sqlite3_stmt* stmt;
        int row = 0;
        int bytes;
        Club* clubTmp;
        char q[999];

        std::vector<Club> getClubs();
        std::vector<Club> getClubsForLeague(int leagueIdQuery);
        int saveClub(Club clubVar);
        void updateClub(Club clubVar);
        Club getPlayerClub();
        Club getClub(int clubIdVar);

    protected:

    private:
        const unsigned char* id;
        const unsigned char* name;
        const unsigned char* budget;
        const unsigned char* points;
        const unsigned char* position;
        const unsigned char* leagueId;
        const unsigned char* playerClub;
        const unsigned char* goalsScored;
        const unsigned char* goalsLost;
        const unsigned char* wins;
        const unsigned char* draws;
        const unsigned char* loses;
        const unsigned char* tactics;

        std::string idString;
        std::string nameString;
        std::string budgetString;
        std::string pointsString;
        std::string positionString;
        std::string leagueIdString;
        std::string playerClubString;
        std::string goalsScoredString;
        std::string goalsLostString;
        std::string winsString;
        std::string drawsString;
        std::string losesString;
        std::string tacticsString;

        void getClubFromStatement(sqlite3_stmt* stmt);
};

#endif // CLUBSDAO_H
