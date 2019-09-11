#include "MatchHelper.h"

MatchHelper::MatchHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
    timetableDao = new TimetableDao();
    playerView = new PlayerView();
    mainView = new MainView();
    timetableView = new TimetableView();
    playersHelper = new PlayersHelper;
}

MatchHelper::~MatchHelper()
{
    //dtor
}

void MatchHelper::match(int homeClubId, int awayClubId, Timetable timetable, std::vector<Club> clubsVec){
    Club tmp;
    Player tmpPlayer;
    Club homeClub;
    Club awayClub;
    std::vector<Player> homeTeamPlayers;
    std::vector<Player> awayTeamPlayers;
    double homeFieldAdvantage = 0.0;
    double luckHomeTeam = 0.0;
    double luckAwayTeam = 0.0;
    int homeTeamGoals = 0;
    int awayTeamGoals = 0;
    int homeTeamChancesCreated;
    double homeTeamShotsSaved;
    int awayTeamChancesCreated;
    double awayTeamShotsSaved;
    std::string resultString;

    homeTeamGKStrength = 0.0;
    awayTeamGKStrength = 0.0;
    homeTeamCBStrength = 0.0;
    awayTeamCBStrength = 0.0;
    homeTeamMFStrength = 0.0;
    awayTeamMFStrength = 0.0;
    homeTeamSTStrength = 0.0;
    awayTeamSTStrength = 0.0;


    homeClub = clubsDao->getClub(homeClubId);
    awayClub = clubsDao->getClub(awayClubId);

    homeTeamPlayers = playersDao->getPlayersForClub(homeClubId);
    awayTeamPlayers = playersDao->getPlayersForClub(awayClubId);

    homeClub.setPlayers(homeTeamPlayers);
    awayClub.setPlayers(awayTeamPlayers);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    homeFieldAdvantage = ((double) dis(gen))/4;

    std::mt19937 gen2(rd());
    std::uniform_real_distribution<> dis2(0, 1);

    luckHomeTeam = ((double) dis2(gen2));

    std::mt19937 gen3(rd());
    std::uniform_real_distribution<> dis3(0, 1);

    luckAwayTeam = ((double) dis3(gen3));

    //home team strength
    for(int i = 0; i < homeTeamPlayers.size(); i++){
       tmpPlayer = homeTeamPlayers.at(i);

       tgroup.create_thread(boost::bind(&MatchHelper::getPlayerStats, this, tmpPlayer, "home"));
    }
    tgroup.join_all();

    homeTeamCBStrength = homeTeamCBStrength/(5.4*4);
    homeTeamMFStrength = homeTeamMFStrength/(5.4*4);
    homeTeamSTStrength = homeTeamSTStrength/(3.4*2);

    //away team strength
    for(int i = 0; i < awayTeamPlayers.size(); i++){
       tmpPlayer = awayTeamPlayers.at(i);
       tgroup2.create_thread(boost::bind(&MatchHelper::getPlayerStats, this, tmpPlayer, "away"));
    }
    tgroup2.join_all();

    awayTeamCBStrength = awayTeamCBStrength/(5.4*4);
    awayTeamMFStrength = awayTeamMFStrength/(5.4*4);
    awayTeamSTStrength = awayTeamSTStrength/(3.4*2);

    homeTeamChancesCreated = (int) (((homeTeamSTStrength/100)*8 + (homeTeamMFStrength/100)*3 + (homeTeamCBStrength/100) + 0.5 + homeFieldAdvantage) * (1/luckHomeTeam));
    homeTeamShotsSaved = ((homeTeamGKStrength/100)*0.7 + (awayTeamCBStrength/100)*0.25 + (homeFieldAdvantage/100) + (luckHomeTeam/100)*5);

    awayTeamChancesCreated = (int) (((awayTeamSTStrength/100)*8 + (awayTeamMFStrength/100)*3 + (awayTeamCBStrength/100) + 0.5) * (1/luckAwayTeam));
    awayTeamShotsSaved = ((homeTeamGKStrength/100)*0.7 + (awayTeamCBStrength/100)*0.25 + (luckAwayTeam/100)*5);


    switch(homeClub.getTactics()){
    case 1:
        homeTeamChancesCreated = homeTeamChancesCreated*0.5;
        homeTeamShotsSaved = homeTeamShotsSaved*1.5;
        break;
    case 2:
        homeTeamChancesCreated = homeTeamChancesCreated*0.75;
        homeTeamShotsSaved = homeTeamShotsSaved*1.25;
        break;
    case 3:
        //we do nothing
        break;
    case 4:
        homeTeamShotsSaved = homeTeamShotsSaved*0.75;
        homeTeamChancesCreated = homeTeamChancesCreated*1.25;
        break;
    default:
        homeTeamShotsSaved = homeTeamShotsSaved*0.5;
        homeTeamChancesCreated = homeTeamChancesCreated*1.5;
        break;
    }


    switch(awayClub.getTactics()){
    case 1:
        awayTeamChancesCreated = awayTeamChancesCreated*0.5;
        awayTeamShotsSaved = awayTeamShotsSaved*1.5;
        break;
    case 2:
        awayTeamChancesCreated = awayTeamChancesCreated*0.75;
        awayTeamShotsSaved = awayTeamShotsSaved*1.25;
        break;
    case 3:
        //we do nothing
        break;
    case 4:
        awayTeamShotsSaved = awayTeamShotsSaved*0.75;
        awayTeamChancesCreated = awayTeamChancesCreated*1.25;
        break;
    default:
        awayTeamShotsSaved = awayTeamShotsSaved*0.5;
        awayTeamChancesCreated = awayTeamChancesCreated*1.5;
        break;
    }

    homeTeamGoals = (int) (homeTeamChancesCreated/(awayTeamShotsSaved*10));
    awayTeamGoals = (int) (awayTeamChancesCreated/(homeTeamShotsSaved*10));

    mainView->displayMatchScore(homeClubId, awayClubId, homeTeamGoals, awayTeamGoals);
    homeClub.setGoalsScored(homeClub.getGoalsScored()+homeTeamGoals);
    homeClub.setGoalsLost(homeClub.getGoalsLost()+awayTeamGoals);
    awayClub.setGoalsScored(awayClub.getGoalsScored()+awayTeamGoals);
    awayClub.setGoalsLost(awayClub.getGoalsLost()+homeTeamGoals);

    int points = 0, points2 = 0;

    if(homeTeamGoals == awayTeamGoals){
        //draw
        resultString = "Draw";
        points = homeClub.getPoints()+1;
        homeClub.setPoints(points);
        points2 = awayClub.getPoints()+1;
        awayClub.setPoints(points2);
        homeClub.setDraws(homeClub.getDraws()+1);
        homeClub.setBudget(homeClub.getBudget()+200000);
        awayClub.setDraws(awayClub.getDraws()+1);
        awayClub.setBudget(awayClub.getBudget()+200000);
    } else if (homeTeamGoals > awayTeamGoals){
        //home teams wins
        resultString = homeClub.getName() + " wins";
        points = homeClub.getPoints()+3;
        homeClub.setPoints(points);
        homeClub.setWins(homeClub.getWins()+1);
        homeClub.setBudget(homeClub.getBudget()+500000);
        awayClub.setLoses(awayClub.getLoses()+1);
        awayClub.setBudget(awayClub.getBudget()+100000);
    } else {
        //away team wins
        resultString = awayClub.getName() + " wins";
        points = awayClub.getPoints()+3;
        awayClub.setPoints(points);
        homeClub.setLoses(homeClub.getLoses()+1);
        homeClub.setBudget(homeClub.getBudget()+100000);
        awayClub.setWins(awayClub.getWins()+1);
        awayClub.setBudget(awayClub.getBudget()+500000);
    }

    timetable.setResult(resultString);
    timetable.setHomeTeamGoals(homeTeamGoals);
    timetable.setAwayTeamGoals(awayTeamGoals);

    timetableDao->updateTimetable(timetable);
    clubsDao->updateClub(homeClub);
    clubsDao->updateClub(awayClub);
}

void MatchHelper::getPlayerStats(Player tmpPlayer, std::string homeAway){

    double cbStrength = 0.0;
    double mfStrength = 0.0;
    double stStrength = 0.0;

    if(tmpPlayer.getPosition() == "GK"){
        //handling, diving, kicking, reflexes
        homeTeamGKStrength = playersHelper->getGkStrength(tmpPlayer);
    } else if(tmpPlayer.getPosition() == "CB"){
        cbStrength = playersHelper->getCbStrength(tmpPlayer);
        mfStrength = (playersHelper->getMfStrength(tmpPlayer)*0.25);
        stStrength = (playersHelper->getStStrength(tmpPlayer)*0.1);
    } else if(tmpPlayer.getPosition() == "MF"){
        cbStrength = (playersHelper->getCbStrength(tmpPlayer)*0.25);
        mfStrength = playersHelper->getMfStrength(tmpPlayer);
    stStrength = (playersHelper->getStStrength(tmpPlayer)*0.25);
    } else{
        cbStrength = (playersHelper->getCbStrength(tmpPlayer)*0.1);
        mfStrength = (playersHelper->getMfStrength(tmpPlayer)*0.1);
        stStrength = playersHelper->getStStrength(tmpPlayer);
    }

    if(homeAway == "home"){
        mutex.lock();
        homeTeamCBStrength += cbStrength;
        homeTeamMFStrength += mfStrength;
        homeTeamSTStrength += stStrength;
        mutex.unlock();
    } else {
        mutex.lock();
        awayTeamCBStrength += cbStrength;
        awayTeamMFStrength += mfStrength;
        awayTeamSTStrength += stStrength;
        mutex.unlock();
    }
}
