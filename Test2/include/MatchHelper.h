#ifndef MATCHHELPER_H
#define MATCHHELPER_H

#include <vector>
#include "Timetable.h"
#include "TimetableDao.h"
#include "Player.h"
#include "PlayersDao.h"
#include "Club.h"
#include "ClubsDao.h"
#include <random>

class MatchHelper
{
    public:
        MatchHelper();
        virtual ~MatchHelper();

        void match(int homeClubId, int awayClubId, int timetableId, std::vector<Club> clubsVec);

    protected:

    private:
        PlayersDao* playersDao;
        ClubsDao* clubsDao;
        TimetableDao* timetableDao;
};

#endif // MATCHHELPER_H
