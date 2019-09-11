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
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

class MatchHelper
{
    public:
        MatchHelper();
        virtual ~MatchHelper();

        void match(int homeClubId, int awayClubId, Timetable timetable, std::vector<Club> clubsVec);
        void getPlayerStats(Player tmpPlayer, std::string homeAway);
    protected:

    private:
        PlayersDao* playersDao;
        ClubsDao* clubsDao;
        TimetableDao* timetableDao;
        TimetableView* timetableView;
        PlayerView* playerView;
        MainView* mainView;
        PlayersHelper* playersHelper;
        boost::mutex mutex;
        boost::thread_group tgroup;
        boost::thread_group tgroup2;
        double homeTeamGKStrength = 0.0;
        double awayTeamGKStrength = 0.0;
        double homeTeamCBStrength = 0.0;
        double awayTeamCBStrength = 0.0;
        double homeTeamMFStrength = 0.0;
        double awayTeamMFStrength = 0.0;
        double homeTeamSTStrength = 0.0;
        double awayTeamSTStrength = 0.0;
};

#endif // MATCHHELPER_H
