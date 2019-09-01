#ifndef MATCHHELPER_H
#define MATCHHELPER_H

#include <vector>
#include "Timetable.h"
#include "TimetableDao.h"
#include "TimetableView.h"
#include "Player.h"
#include "PlayersDao.h"
#include "PlayerView.h"
#include "PlayersHelper.h"
#include "Club.h"
#include "ClubsDao.h"
#include "MainView.h"
#include <random>
#include <iostream>

class MatchHelper
{
    public:
        MatchHelper();
        virtual ~MatchHelper();

        void match(int homeClubId, int awayClubId, Timetable timetable, std::vector<Club> clubsVec);

    protected:

    private:
        PlayersDao* playersDao;
        ClubsDao* clubsDao;
        TimetableDao* timetableDao;
        TimetableView* timetableView;
        PlayerView* playerView;
        MainView* mainView;
        PlayersHelper* playersHelper;
};

#endif // MATCHHELPER_H
