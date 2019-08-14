#ifndef SEASONSDAO_H
#define SEASONSDAO_H

#include"Season.h"
#include<vector>
#include <sqlite3.h>
#include <iostream>

class SeasonsDao
{
    public:
        SeasonsDao();
        virtual ~SeasonsDao();

        sqlite3* DB;
        int exit;
        sqlite3_stmt* stmt;
        int row = 0;
        int bytes;
        Season* seasonTmp;
        char q[999];

        const unsigned char* id;
        const unsigned char* number;
        std::string idString;
        std::string numberString;

        std::vector<Season> getSeasons();
        int saveSeason(Season seasonVar);
        void updateSeason(Season seasonVar);

    protected:

    private:
};

#endif // SEASONSDAO_H
