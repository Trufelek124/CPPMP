#ifndef PLAYERSHELPER_H
#define PLAYERSHELPER_H

#include "Player.h"
#include "Club.h"
#include <vector>
#include "PlayersDao.h"
#include "ClubsDao.h"
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <cstdlib>

class PlayersHelper
{
    public:
        PlayersHelper();
        virtual ~PlayersHelper();

        void randommizeInitialSquads();

    protected:

    private:
        PlayersDao* playersDao;
        ClubsDao* clubsDao;
};

#endif // PLAYERSHELPER_H
