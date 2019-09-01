#ifndef TRANSFERLISTHELPER_H
#define TRANSFERLISTHELPER_H

#include "Player.h"
#include "PlayersDao.h"
#include "PlayerView.h"
#include "Club.h"
#include "ClubsDao.h"
#include "ClubView.h"
#include <vector>

class TransferListHelper
{
    public:
        TransferListHelper();
        virtual ~TransferListHelper();
        void getTransferList();
        void transferPlayerToTheTeam();

    protected:

    private:
        PlayersDao* playersDao;
        PlayerView* playerView;
};

#endif // TRANSFERLISTHELPER_H
