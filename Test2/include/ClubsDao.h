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

        const unsigned char* id;
        const unsigned char* name;
        const unsigned char* budget;
        const unsigned char* points;
        const unsigned char* position;
        const unsigned char* leagueId;
        const unsigned char* playerClub;

        std::string idString;
        std::string nameString;
        std::string budgetString;
        std::string pointsString;
        std::string positionString;
        std::string leagueIdString;
        std::string playerClubString;


        std::vector<Club> getClubs();
        std::vector<Club> getClubsForLeague(int leagueIdQuery);
        int saveClub(Club clubVar);
        void updateClub(Club clubVar);
        Club getPlayerClub();

    protected:

    private:
};

#endif // CLUBSDAO_H
