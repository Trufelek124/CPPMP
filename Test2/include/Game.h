#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Club.h"
#include "League.h"
#include "PlayersDao.h"
#include "PlayersHelper.h"
#include "LeaguesDao.h"
#include "Timetable.h"
#include "TimetableHelper.h"
#include "TimetableView.h"
#include "ClubsDao.h"
#include "ClubHelper.h"
#include "SeasonsDao.h"
#include "TimetableDao.h"
#include "PlayerView.h"
#include "MainView.h"
#include "PlayerView.h"
#include "ClubView.h"
#include "DatabaseHelper.h"
#include "MatchHelper.h"
#include <vector>

class Game
{
    public:
        Game();
        virtual ~Game();

        void setup();
        void programSetup();
        void matchweek(int matchweek);
        void match(int homeClubId, int awayClubId, int timetableId);
        int play();
        int handleMenu(int menuOption);

        std::vector<Player> playersVec;
        std::vector<Club> clubsVec;
        std::vector<League> leaguesVec;
        std::vector<Season> seasonsVec;
        std::vector<Timetable> timetablesVec;
        std::vector<Timetable> timetablesVecMatchweek;

    protected:

    private:
        DatabaseHelper* databaseHelperVar;
        TimetableHelper* timetableHelperVar;
        PlayersHelper* playersHelperVar;
        MatchHelper* matchHelperVar;
        ClubHelper* clubHelper;

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
