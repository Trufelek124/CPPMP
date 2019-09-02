#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::setup(){
    databaseHelperVar = new DatabaseHelper();
    timetableHelperVar = new TimetableHelper();
    playersHelperVar = new PlayersHelper();
    matchHelperVar = new MatchHelper();
    clubHelper = new ClubHelper();
    transferListHelper = new TransferListHelper();

    playersDao = new PlayersDao();
    leaguesDao = new LeaguesDao();
    clubsDao = new ClubsDao();
    seasonsDao = new SeasonsDao();
    timetableDao = new TimetableDao();

    mainViewVar = new MainView();
    playerViewVar = new PlayerView();
    clubViewVar = new ClubView();
    timetableViewVar = new TimetableView();

    clubVar = new Club();

  //  programSetup();
}

int Game::play(){

    int continueProgram = 1;

    while(continueProgram == 1){
        mainViewVar->displayTestMenu();
        int menuOption = mainViewVar->getUserInput();
        continueProgram = handleMenu(menuOption);
    };
    return 0;

}

int Game::handleMenu(int menuOption){
    switch(menuOption){
    case 1:
        programSetup();
        season();
        system("pause");
        system ("CLS");
        return 1;
    case 2:
        databaseHelperVar->createTables();
        databaseHelperVar->insertInitialData();
        system("pause");
        system ("CLS");
        return 1;
    case 3:
        databaseHelperVar->dropTables();
        system("pause");
        system ("CLS");
        return 1;
    case 4:
        return 0;
    default:
        return 0;
    }
}

void Game::programSetup(){

    playersVec = playersDao->getPlayers();
    std::vector<Club> clubsVecTmp = clubsDao->getClubs();
    leaguesVec = leaguesDao->getLeagues();
    seasonsVec = seasonsDao->getSeasons();
    timetablesVec = timetableDao->getTimetables();

    if(!playersVec.empty()){
        playersHelperVar->randommizeInitialSquads();
        clubsVecTmp = clubsDao->getClubs();

        for(int i = 0; i < clubsVecTmp.size(); i++){
            clubTestVar = clubsVecTmp.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
            clubsVec.push_back(clubTestVar);
        }

        playerClubId = clubHelper->setUserClub(clubsVec);

        if(timetablesVec.empty()){
            timetableHelperVar->createTimetableForSeason(1, clubsVec);
            timetablesVec = timetableDao->getTimetables();
            timetableViewVar->displayTimetableList(timetablesVec);
        }

    } else {
        std::cout << "No data in database" << std::endl;
    }
}

void Game::matchweek(int matchweek){
    Club clubTmp;
    std::vector<Club> clubsVecTmp;
    if(!timetablesVec.empty()){
        clubsVecTmp = clubsDao->getClubs();


        for(int i = 0; i < clubsVecTmp.size(); i++){
            clubTestVar = clubsVecTmp.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
            clubsVec.push_back(clubTestVar);
        }

        timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(matchweek, 1); //na razie sezon = 1 - 3
        for(int j = 0; j < timetablesVecMatchweek.size(); j++){
            Timetable tmp = timetablesVecMatchweek.at(j);
            //timetableViewVar->displayTimetable(tmp);
            matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
        }

        //oblicz pozycj� zespo�u
        clubsVec = clubsDao->getClubs();
        clubHelper->updateClubsPosition(clubsVec);
        timetableViewVar->displayTimetableList(timetablesVecMatchweek);
        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubViewVar->displayClubsInfo(clubsSortedByPoints);
    }
}

void Game::season(){
    Club clubTmp;
    std::vector<Club> clubsVecTmp;
    if(!timetablesVec.empty()){
        clubsVec = clubsDao->getClubs();
        for(int i = 0; i < (clubsVec.size()-1); i++){ //kolejki - 12
            timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, 1); //na razie sezon = 1 - 3
            std::cout << "Kolejka: " << i << std::endl;
            for(int j = 0; j < timetablesVecMatchweek.size(); j++){
                Timetable tmp = timetablesVecMatchweek.at(j);
                //timetableViewVar->displayTimetable(tmp);
                matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
            }

            //oblicz pozycj� zespo�u
            clubsVec = clubsDao->getClubs();
            clubHelper->updateClubsPosition(clubsVec);

            std::vector<Club> clubsSortedByPoints = clubsVec;
            std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
            clubViewVar->displayClubList(clubsSortedByPoints);

            system("pause");
            //system ("CLS");
        }

        transferListHelper->transferWindow(playerClubId);

        //lista transferowa
        for(int i = (clubsVec.size()-1); i < (clubsVec.size()-1)*2; i++){
            timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, 1); //na razie sezon = 1 - 3
            std::cout << "Kolejka: " << i << std::endl;
            for(int j = 0; j < timetablesVecMatchweek.size(); j++){
                Timetable tmp = timetablesVecMatchweek.at(j);
                //timetableViewVar->displayTimetable(tmp);
                matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
            }

            //oblicz pozycj� zespo�u
            clubsVec = clubsDao->getClubs();
            clubHelper->updateClubsPosition(clubsVec);

            std::vector<Club> clubsSortedByPoints = clubsVec;
            std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
            clubHelper->updateClubsPosition(clubsVec);
            clubViewVar->displayClubList(clubsSortedByPoints);

            system("pause");
        }

        timetablesVec = timetableDao->getTimetables();
        timetableViewVar->displayTimetableList(timetablesVec);

        //clubsVec = clubsDao->getClubs();

        clubsVecTmp = clubsDao->getClubs();
        clubsVec.clear();


        for(int i = 0; i < clubsVecTmp.size(); i++){
            clubTestVar = clubsVecTmp.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
            clubsVec.push_back(clubTestVar);
        }

        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubViewVar->displayClubList(clubsSortedByPoints);
    }
}

