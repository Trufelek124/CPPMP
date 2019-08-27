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
        programSetup();
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
        timetablesVec = timetableDao->getTimetables();
        timetableViewVar->displayTimetableList(timetablesVec);
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
        playersHelperVar->randommizeInitialSquads();
        clubsVec = clubsDao->getClubs();
        clubTestVar = clubsVec.at(0);
        players = playersDao->getPlayersForClub(clubTestVar.getClubId());
        std::cout<<players.size()<<std::endl;
        clubTestVar.setPlayers(players);
        clubViewVar->displayClubInfo(clubTestVar);
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
            std::cout<<players.size()<<std::endl;
            clubTestVar.setPlayers(players);
            clubViewVar->displayClubInfo(clubTestVar);
        }

        timetableHelperVar->createTimetableForSeason(1, clubsVec);
        timetablesVec = timetableDao->getTimetables();
        timetableViewVar->displayTimetableList(timetablesVec);
    } else {
        std::cout << "No data in database" << std::endl;
    }
}

void Game::matchweek(int matchweek){
    if(!timetablesVec.empty()){
        clubsVec = clubsDao->getClubs();
        for(int i = 0; i < (clubsVec.size()-1)*2; i++){ //kolejki
            timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, 1); //na razie sezon = 1
            for(int j = 0; j < timetablesVecMatchweek.size(); j++){
                Timetable tmp = timetablesVecMatchweek.at(j);
                match(tmp.getHomeClub(), tmp.getAwayClub(), tmp.getTimetableId());
            }
        }
    }
}

void Game::match(int homeClubId, int awayClubId, int timetableId){
    Club tmp;
    Club homeClub;
    Club awayClub;
    std::vector<Player> homeTeamPlayers;
    std::vector<Player> awayTeamPlayers;
    double homeFieldAdvantage;

    if(!clubsVec.empty()){
        for(int i = 0; i < clubsVec.size(); i++){
            tmp = clubsVec.at(i);
            if(tmp.getClubId() == homeClubId)
                homeClub = clubsVec.at(i);
            if(tmp.getClubId() == awayClubId)
                awayClub = clubsVec.at(i);
        }

        homeTeamPlayers = homeClub.getPlayers();
        awayTeamPlayers = awayClub.getPlayers();
    } else {
        homeClub = clubsDao->getClub(homeClubId);
        awayClub = clubsDao->getClub(awayClubId);

        homeTeamPlayers = playersDao->getPlayersForClub(homeClubId);
        awayTeamPlayers = playersDao->getPlayersForClub(awayClubId);

        homeClub.setPlayers(homeTeamPlayers);
        awayClub.setPlayers(awayTeamPlayers);
    }

    Timetable timetable = timetableDao->getTimetable(timetableId);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    homeFieldAdvantage = (double) dis(gen);

    double homeTeamGKStrength;
    double awayTeamGKStrength;
    double homeTeamCBStrength;
    double awayTeamCBStrength;
    double homeTeamMFStrength;
    double awayTeamMFStrength;
    double homeTeamSTStrength;
    double awayTeamSTStrength;
    //Mam sk�ady i zespo�y
    //TODO
    //Algorytm meczowy
}
