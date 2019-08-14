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
    playersDao = new PlayersDao();
    leaguesDao = new LeaguesDao();
    clubsDao = new ClubsDao();
    seasonsDao = new SeasonsDao();
    timetableDao = new TimetableDao();
    mainViewVar = new MainView();
    playerViewVar = new PlayerView();
    clubViewVar = new ClubView();
    timetableViewVar = new TimetableView();

    //getting initial data from database to program

    playersVec = playersDao->getPlayers();
    clubsVec = clubsDao->getClubs();
    leaguesVec = leaguesDao->getLeagues();
    seasonsVec = seasonsDao->getSeasons();
    timetablesVec = timetableDao->getTimetables();

    clubVar = new Club();
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
        clubSetup();
        system("pause");
        system ("CLS");
        return 1;
    case 1:
        databaseHelperVar->createTables();
        databaseHelperVar->insertInitialData();
        system("pause");
        system ("CLS");
        return 1;
    case 2:
        playersVec = playersDao->getPlayers();
        playerViewVar->displayPlayersList(playersVec);
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
    case 5:
        playerVar2 = new Player();
        playerVar2->setName("Krzysztof Werner");
        playerVar2->setPosition("ST");
        playerVar2->setAge(26);
        playerVar2->setClubId(1);
        playersDao->savePlayer(*playerVar2);
        system("pause");
        system ("CLS");
        return 1;
    case 6:
        playerVar3 = playersVec.at(playersVec.size()-1);
        playerVar3.setName("Aleksander Werner");
        playerVar3.setPosition("ST");
        playerVar3.setAge(26);
        playerVar3.setClubId(1);
        playersDao->updatePlayer(playerVar3);
        system("pause");
        system ("CLS");
        return 1;
    case 7:
        return 1;
    case 8:
        clubsVec = clubsDao->getClubs();
        clubViewVar->displayClubList(clubsVec);
        system("pause");
        system ("CLS");
        return 1;
    case 9:
        clubsVec = clubsDao->getClubs();
        timetableHelperVar->createTimetableForSeason(1, clubsVec);
        timetablesVec = timetableDao->getTimetables();
        timetableViewVar->displayTimetableList(timetablesVec);
        system("pause");
        system ("CLS");
        return 1;
    default:
        return 0;
    }
}

void Game::clubSetup(){
    clubsVec = clubsDao->getClubs();
    clubViewVar->displayClubList(clubsVec);
    clubViewVar->displayClubSetup();
    submenuOption = mainViewVar->getUserInput();
    clubVarTmp = clubsVec.at(submenuOption - 1);
    clubVarTmp.setPlayerClub(1);
    clubsDao->updateClub(clubVarTmp);
}
