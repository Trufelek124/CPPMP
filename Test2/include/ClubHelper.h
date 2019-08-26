#ifndef CLUBHELPER_H
#define CLUBHELPER_H

#include "Club.h"
#include "ClubsDao.h"
#include "ClubView.h"
#include "MainView.h"
#include <vector>


class ClubHelper
{
    public:
        ClubHelper();
        virtual ~ClubHelper();

        int setUserClub();

    protected:

    private:
        Club clubVarTmp;
        ClubsDao* clubsDao;
        std::vector<Club> clubsVec;
        ClubView* clubView;
        MainView* mainView;
};

#endif // CLUBHELPER_H
