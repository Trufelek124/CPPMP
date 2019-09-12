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
    seasonNumber = 1;
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
    std::string response;
    bool done = false;
    switch(menuOption){
    case 1:
        programSetup();
        while(!done){
            season();
            std::cout << "Do You want to play another season (Y/N)? ";
            std::cin >> response;
            if(response == "N"){
                done = true;
            } else {
                timetablesVec.clear();
                seasonNumber += 1;
                system("CLS");
            }
        }
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
        try{
            databaseHelperVar->dropTables();
        } catch (DBException& ex)
        {
            std::cout << ex.what() << std::endl;
        }
        system("pause");
        system ("CLS");
        return 1;
    case 4:
        mainViewVar->displayInstructions();
        system("pause");
        system ("CLS");
        return 1;
    case 5:
        exit();
        system("pause");
        system ("CLS");
        return 0;
    case 6:
        mainViewVar->displayAbout();
        system("pause");
        system ("CLS");
        return 1;
    default:
        return 0;
    }
}

void Game::exit(){
    std::cout << "    ThankYou for playing :)" << std::endl;
    std::cout << std::endl;
    mainViewVar->displayAbout();
}

void Game::programSetup(){

    playersVec = playersDao->getPlayers();
    std::vector<Club> clubsVecTmp = clubsDao->getClubs();
    leaguesVec = leaguesDao->getLeagues();
    seasonsVec = seasonsDao->getSeasons();
    timetablesVec = timetableDao->getTimetables();

    if(!playersVec.empty()){
        playersHelperVar->updateOverallScoreForPlayers(playersVec);
        playersHelperVar->randommizeInitialSquads();
        clubsVecTmp = clubsDao->getClubs();

        for(int i = 0; i < clubsVecTmp.size(); i++){
            clubTestVar = clubsVecTmp.at(i);
            players = playersDao->getPlayersForClub(clubTestVar.getClubId());
            clubTestVar.setPlayers(players);
            clubsVec.push_back(clubTestVar);
        }

        playerClubId = clubHelper->setUserClub(clubsVec);

    } else {
        std::cout << "No data in database" << std::endl;
    }
}

void Game::season(){
    Club clubTmp;
    std::vector<Club> clubsVecTmp;

    if(timetablesVec.empty()){
        timetableHelperVar->createTimetableForSeason(seasonNumber, clubsVec);
        timetablesVec = timetableDao->getTimetablesForSeason(seasonNumber);
        std::cout << "All season timetable" << std::endl;
        timetableViewVar->displayTimetableList(timetablesVec);
        std::cout << std::endl;
    };

    clubsVec = clubsDao->getClubs();
    for(int i = 0; i < (clubsVec.size()-1); i++){ //kolejki - 12
        system("CLS");
        std::cout << "Matchweek: " << i+1 << std::endl;
        timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, seasonNumber); //na razie sezon = 1 - 3
        timetableViewVar->displayTimetableList(timetablesVecMatchweek);
        clubsVec = clubHelper->chooseTacticsForClub(playerClubId, clubsVec);
        std::cout << "Results: " << std::endl;
        for(int j = 0; j < timetablesVecMatchweek.size(); j++){
            Timetable tmp = timetablesVecMatchweek.at(j);
            matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
        }

        //oblicz pozycjê zespo³u
        clubsVec = clubsDao->getClubs();
        clubHelper->updateClubsPosition(clubsVec);

        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubViewVar->displayClubList(clubsSortedByPoints);

        system("pause");
        system("CLS");

        playersVec = playersDao->getPlayers();
        playersVec = playersHelperVar->playersClubPlayersTraining(playersVec, playerClubId);
        for(int i = 0; i < playersVec.size(); i++){
            Player tmpPlayer = playersVec.at(i);
            playersHelperVar->trainPlayer(tmpPlayer);
        };

        playersHelperVar->updateOverallScoreForPlayers(playersVec);
    }

    transferListHelper->transferWindow(playerClubId);

    //lista transferowa
    for(int i = (clubsVec.size()-1); i < (clubsVec.size()-1)*2; i++){
        system("CLS");
        std::cout << "Matchweek: " << i+1 << std::endl;
        clubsVec = clubHelper->chooseTacticsForClub(playerClubId, clubsVec);
        timetablesVecMatchweek = timetableDao->getTimetablesForMatchweek(i+1, 1); //na razie sezon = 1 - 3
        timetableViewVar->displayTimetableList(timetablesVecMatchweek);
        clubsVec = clubHelper->chooseTacticsForClub(playerClubId, clubsVec);
        std::cout << "Results: " << std::endl;
        for(int j = 0; j < timetablesVecMatchweek.size(); j++){
            Timetable tmp = timetablesVecMatchweek.at(j);
            matchHelperVar->match(tmp.getHomeClub(), tmp.getAwayClub(), tmp, clubsVec);
        }

        //oblicz pozycjê zespo³u
        clubsVec = clubsDao->getClubs();
        clubHelper->updateClubsPosition(clubsVec);

        std::vector<Club> clubsSortedByPoints = clubsVec;
        std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
        clubHelper->updateClubsPosition(clubsVec);
        clubViewVar->displayClubList(clubsSortedByPoints);

        system("pause");
        system("CLS");

        playersVec = playersDao->getPlayers();
        playersVec = playersHelperVar->playersClubPlayersTraining(playersVec, playerClubId);
        for(int i = 0; i < playersVec.size(); i++){
            Player tmpPlayer = playersVec.at(i);
            playersHelperVar->trainPlayer(tmpPlayer);
        }
    }
        playersHelperVar->updateOverallScoreForPlayers(playersVec);

    timetablesVec = timetableDao->getTimetables();
    timetableViewVar->displayTimetableList(timetablesVec);

    clubsVecTmp = clubsDao->getClubs();
    clubsVec.clear();


    for(int i = 0; i < clubsVecTmp.size(); i++){
        clubTestVar = clubsVecTmp.at(i);
        if(clubTestVar.getPosition() == 1){ //prize for the end result
            clubTestVar.setBudget(clubTestVar.getBudget()+5000000);
        } else if(clubTestVar.getPosition() == 2){
            clubTestVar.setBudget(clubTestVar.getBudget()+2500000);
        } else if(clubTestVar.getPosition() == 3){
            clubTestVar.setBudget(clubTestVar.getBudget()+1000000);
        }

        clubsDao->updateClub(clubTestVar);
        clubsVec.push_back(clubTestVar);
    }

    std::vector<Club> clubsSortedByPoints = clubsVec;
    std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());
    clubViewVar->displayClubList(clubsSortedByPoints);

    transferListHelper->transferWindow(playerClubId);

    std::cout << "OFFICIAL SEASON STANDINGS" << std::endl;
    clubViewVar->displayClubList(clubsSortedByPoints);

    //postarzanie zawodników
    playersVec = playersDao->getPlayers();
    for(int i = 0; i < playersVec.size(); i++){
        Player tmpPlayer = playersVec.at(i);
        tmpPlayer.setAge(tmpPlayer.getAge()+1);
        playersDao->updatePlayer(tmpPlayer);
    }

    //resetowanie wyników klubów
    for(int i = 0; i < clubsVec.size(); i++){
        Club tmpClub = clubsVec.at(i);
        tmpClub.setPoints(0);
        tmpClub.setWins(0);
        tmpClub.setDraws(0);
        tmpClub.setLoses(0);
        clubsDao->updateClub(tmpClub);
    }
}
