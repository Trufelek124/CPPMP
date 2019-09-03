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
#include <math.h>
#include <random>

class PlayersHelper
{
    public:
        PlayersHelper();
        virtual ~PlayersHelper();

        void randommizeInitialSquads();
        int getPlayerWorth(Player player);
        double getGkStrength(Player tmpPlayer);
        double getCbStrength(Player tmpPlayer);
        double getMfStrength(Player tmpPlayer);
        double getStStrength(Player tmpPlayer);
        void trainPlayer(Player tmpPlayer);

    protected:

    private:
        PlayersDao* playersDao;
        ClubsDao* clubsDao;
};

#endif // PLAYERSHELPER_H
