#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Club.h"
#include "League.h"
#include "DatabaseHelper.h"
#include "PlayersDao.h"
#include "LeaguesDao.h"
#include "ClubsDao.h"
#include "SeasonsDao.h"
#include "TimetableDao.h"
#include "PlayerView.h"
#include "MainView.h"
#include <vector>
#include "PlayerView.h"
#include "ClubView.h"
#include "Timetable.h"
#include "TimetableHelper.h"
#include "TimetableView.h"
#include "PlayersHelper.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void setup();
        void clubSetup();
        int play();
        int handleMenu(int menuOption);

        std::vector<Player> playersVec;
        std::vector<Club> clubsVec;
        std::vector<League> leaguesVec;
        std::vector<Season> seasonsVec;
        std::vector<Timetable> timetablesVec;

    protected:

    private:
        DatabaseHelper* databaseHelperVar;
        TimetableHelper* timetableHelperVar;
        PlayersHelper* playersHelperVar;

        PlayersDao* playersDao;
        LeaguesDao* leaguesDao;
        ClubsDao* clubsDao;
        SeasonsDao* seasonsDao;
        TimetableDao* timetableDao;

        MainView* mainViewVar;
        PlayerView* playerViewVar;
        ClubView* clubViewVar;
        TimetableView* timetableViewVar;

        Club* clubVar;
        Club clubVarTmp;
        League* leagueVar;
        Player* playerVar2;
        Player playerVar3;

        int submenuOption;

        Club clubTestVar;
        std::vector<Player> players;
};

#endif // GAME_H
