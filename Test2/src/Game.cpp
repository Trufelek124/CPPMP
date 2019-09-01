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
    case 0:
        programSetupGame();
        system("pause");
        system ("CLS");
        return 1;
    case 1:
        //TODO new game itd
        programSetup();
        clubHelper->setUserClub();
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

void Game::programSetupGame(){

    playersVec = playersDao->getPlayers();
    clubsVec = clubsDao->getClubs();
    leaguesVec = leaguesDao->getLeagues();
    seasonsVec = seasonsDao->getSeasons();
    timetablesVec = timetableDao->getTimetables();

    if(!playersVec.empty()){
        playersHelperVar->randommizeInitialSquads();
        clubsVec = clubsDao->getClubs();

        for(int i = 0; i < clubsVec.size(); i++){
            clubTestVar = clubsVec.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
           // clubViewVar->displayClubInfo(clubTestVar);
        }
        if(timetablesVec.empty()){
            timetableHelperVar->createTimetableForSeason(1, clubsVec);
            timetablesVec = timetableDao->getTimetables();
            timetableViewVar->displayTimetableList(timetablesVec);
        }
        season();

    } else {
        std::cout << "No data in database" << std::endl;
    }
}

void Game::programSetup(){

    playersVec = playersDao->getPlayers();
    clubsVec = clubsDao->getClubs();
    leaguesVec = leaguesDao->getLeagues();
    seasonsVec = seasonsDao->getSeasons();
    timetablesVec = timetableDao->getTimetables();

    if(!playersVec.empty()){
        playersHelperVar->randommizeInitialSquads();
        clubsVec = clubsDao->getClubs();

        for(int i = 0; i < clubsVec.size(); i++){
            clubTestVar = clubsVec.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
           // clubViewVar->displayClubInfo(clubTestVar);
        }
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
    if(!timetablesVec.empty()){
        clubsVec = clubsDao->getClubs();
        timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(matchweek, 1); //na razie sezon = 1 - 3
        for(int j = 0; j < timetablesVecMatchweek.size(); j++){
            Timetable tmp = timetablesVecMatchweek.at(j);
            //timetableViewVar->displayTimetable(tmp);
            matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
        }

        //oblicz pozycjê zespo³u
        clubsVec = clubsDao->getClubs();
        clubHelper->updateClubsPosition(clubsVec);
        timetableViewVar->displayTimetableList(timetablesVecMatchweek);
        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubViewVar->displayClubsInfo(clubsSortedByPoints);

      //  system("pause");
      //  system ("CLS");
    }
}

void Game::season(){
    Club clubTmp;
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

            //oblicz pozycjê zespo³u
            clubsVec = clubsDao->getClubs();
            clubHelper->updateClubsPosition(clubsVec);

            std::vector<Club> clubsSortedByPoints = clubsVec;
            std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
            clubViewVar->displayClubList(clubsSortedByPoints);

            system("pause");
            //system ("CLS");
        }

        //lista transferowa
        for(int i = (clubsVec.size()-1); i < (clubsVec.size()-1)*2; i++){
            timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, 1); //na razie sezon = 1 - 3
            std::cout << "Kolejka: " << i << std::endl;
            for(int j = 0; j < timetablesVecMatchweek.size(); j++){
                Timetable tmp = timetablesVecMatchweek.at(j);
                //timetableViewVar->displayTimetable(tmp);
                matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
            }

            //oblicz pozycjê zespo³u
            clubsVec = clubsDao->getClubs();
            clubHelper->updateClubsPosition(clubsVec);

            std::vector<Club> clubsSortedByPoints = clubsVec;
            std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
            clubViewVar->displayClubList(clubsSortedByPoints);

            system("pause");
        }

        timetablesVec = timetableDao->getTimetables();
        timetableViewVar->displayTimetableList(timetablesVec);

        clubsVec = clubsDao->getClubs();

        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubViewVar->displayClubsInfo(clubsSortedByPoints);
    }
}

