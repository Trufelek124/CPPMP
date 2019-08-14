#ifndef LEAGUESDAO_H
#define LEAGUESDAO_H

#include"League.h"
#include<vector>
#include <sqlite3.h>
#include <iostream>
#include <string>

class LeaguesDao
{
    public:
        LeaguesDao();
        virtual ~LeaguesDao();

        sqlite3* DB;
        int exit;
        sqlite3_stmt* stmt;
        int row = 0;
        int bytes;
        League* leagueTmp;
        char q[999];

        const unsigned char* id;
        const unsigned char* seasonId;
        const unsigned char* matchweek;

        std::string idString;
        std::string seasonIdString;
        std::string matchweekString;

        std::vector<League> getLeagues();
        League getLeagueForClub(int leagueIdQuery);
        int saveLeague(League leagueVar);
        void updateLeague(League leagueVar);

    protected:

    private:
};

#endif // LEAGUESDAO_H