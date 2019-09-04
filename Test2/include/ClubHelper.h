#ifndef CLUBHELPER_H
#define CLUBHELPER_H

#include "Club.h"
#include "ClubsDao.h"
#include "ClubView.h"
#include "MainView.h"
#include "Player.h"
#include "PlayersDao.h"
#include <vector>
#include <algorithm>
#include <iostream>


class ClubHelper
{
    public:
        ClubHelper();
        virtual ~ClubHelper();

        int setUserClub(std::vector<Club> clubsVec);
        void updateClubsPosition(std::vector<Club> clubsVec);
        std::vector<Club> chooseTacticsForClub(int playerClubId, std::vector<Club> clubsVec);

    protected:

    private:
        Club clubVarTmp;
        ClubsDao* clubsDao;
        std::vector<Club> clubsVec;
        ClubView* clubView;
        MainView* mainView;
        PlayersDao* playersDao;
};

#endif // CLUBHELPER_H
