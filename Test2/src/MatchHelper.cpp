#include "MatchHelper.h"

MatchHelper::MatchHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
    timetableDao = new TimetableDao();
    playerView = new PlayerView();
    mainView = new MainView();
    timetableView = new TimetableView();
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
    double homeTeamGKStrength = 0.0;
    double awayTeamGKStrength = 0.0;
    double homeTeamCBStrength = 0.0;
    double awayTeamCBStrength = 0.0;
    double homeTeamMFStrength = 0.0;
    double awayTeamMFStrength = 0.0;
    double homeTeamSTStrength = 0.0;
    double awayTeamSTStrength = 0.0;
    int homeTeamChancesCreated;
    double homeTeamShotsSaved;
    int awayTeamChancesCreated;
    double awayTeamShotsSaved;
    std::string resultString;


    homeClub = clubsDao->getClub(homeClubId);
    awayClub = clubsDao->getClub(awayClubId);

    homeTeamPlayers = playersDao->getPlayersForClub(homeClubId);
    awayTeamPlayers = playersDao->getPlayersForClub(awayClubId);

    homeClub.setPlayers(homeTeamPlayers);
    awayClub.setPlayers(awayTeamPlayers);

    if(homeTeamPlayers.empty() || awayTeamPlayers.empty()){
        homeTeamPlayers = playersDao->getPlayersForClub(homeClubId);
        awayTeamPlayers = playersDao->getPlayersForClub(awayClubId);
    }

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
       double cbStrength = 0.0;
       double mfStrength = 0.0;
       double stStrength = 0.0;

       if(tmpPlayer.getPosition() == "GK"){
            //handling, diving, kicking, reflexes
            homeTeamGKStrength = getGkStrength(tmpPlayer);
       } else if(tmpPlayer.getPosition() == "CB"){
           //tackling, heading, marking, intercepting
           cbStrength = getCbStrength(tmpPlayer);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (getMfStrength(tmpPlayer)*0.25);
           //positioning, finishing, power, volleys, longShots
           stStrength = (getStStrength(tmpPlayer)*0.1);
       } else if(tmpPlayer.getPosition() == "MF"){
           cbStrength = (getCbStrength(tmpPlayer)*0.25);
           mfStrength = getMfStrength(tmpPlayer);
           stStrength = (getStStrength(tmpPlayer)*0.25);
       } else {
           cbStrength = (getCbStrength(tmpPlayer)*0.1);
           mfStrength = (getMfStrength(tmpPlayer)*0.1);
           stStrength = getStStrength(tmpPlayer);
       }

    homeTeamCBStrength += cbStrength;
    homeTeamMFStrength += mfStrength;
    homeTeamSTStrength += stStrength;
    }

    //away team strength
    for(int i = 0; i < awayTeamPlayers.size(); i++){
       tmpPlayer = awayTeamPlayers.at(i);
       double cbStrength = 0.0;
       double mfStrength = 0.0;
       double stStrength = 0.0;

       if(tmpPlayer.getPosition() == "GK"){
            //handling, diving, kicking, reflexes
            awayTeamGKStrength = getGkStrength(tmpPlayer);
       } else if(tmpPlayer.getPosition() == "CB"){
           cbStrength = getCbStrength(tmpPlayer);
           mfStrength = (getMfStrength(tmpPlayer)*0.25);
           stStrength = (getStStrength(tmpPlayer)*0.1);
       } else if(tmpPlayer.getPosition() == "MF"){
           cbStrength = (getCbStrength(tmpPlayer)*0.25);
           mfStrength = getMfStrength(tmpPlayer);
           stStrength = (getStStrength(tmpPlayer)*0.25);
       } else {
           cbStrength = (getCbStrength(tmpPlayer)*0.1);
           mfStrength = (getMfStrength(tmpPlayer)*0.1);
           stStrength = getStStrength(tmpPlayer);
       }
    awayTeamCBStrength += cbStrength;
    awayTeamMFStrength += mfStrength;
    awayTeamSTStrength += stStrength;
    }

    homeTeamCBStrength = homeTeamCBStrength/(5.4*4);
    homeTeamMFStrength = homeTeamMFStrength/(5.4*4);
    homeTeamSTStrength = homeTeamSTStrength/(3.4*2);

    awayTeamCBStrength = awayTeamCBStrength/(5.4*4);
    awayTeamMFStrength = awayTeamMFStrength/(5.4*4);
    awayTeamSTStrength = awayTeamSTStrength/(3.4*2);

    homeTeamChancesCreated = (int) (((homeTeamSTStrength/100)*8 + (homeTeamMFStrength/100)*3 + (homeTeamCBStrength/100) + 0.5 + homeFieldAdvantage) * (1/luckHomeTeam));
    awayTeamChancesCreated = (int) (((awayTeamSTStrength/100)*8 + (awayTeamMFStrength/100)*3 + (awayTeamCBStrength/100) + 0.5) * (1/luckAwayTeam));

    //Percent of saved shots
    homeTeamShotsSaved = ((homeTeamGKStrength/100)*0.7 + (awayTeamCBStrength/100)*0.25 + (homeFieldAdvantage/100) + (luckHomeTeam/100)*5);
    awayTeamShotsSaved = ((homeTeamGKStrength/100)*0.7 + (awayTeamCBStrength/100)*0.25 + (luckAwayTeam/100)*5);

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
        awayClub.setDraws(awayClub.getDraws()+1);
    } else if (homeTeamGoals > awayTeamGoals){
        //home teams wins
        resultString = homeClub.getName() + " wins";
        points = homeClub.getPoints()+3;
        homeClub.setPoints(points);
        homeClub.setWins(homeClub.getWins()+1);
        awayClub.setLoses(awayClub.getLoses()+1);
    } else {
        //away team wins
        resultString = awayClub.getName() + " wins";
        points = awayClub.getPoints()+3;
        awayClub.setPoints(points);
        homeClub.setLoses(homeClub.getLoses()+1);
        awayClub.setWins(awayClub.getWins()+1);
    }

    timetable.setResult(resultString);
    timetable.setHomeTeamGoals(homeTeamGoals);
    timetable.setAwayTeamGoals(awayTeamGoals);

    timetableDao->updateTimetable(timetable);
    clubsDao->updateClub(homeClub);
    clubsDao->updateClub(awayClub);
}

double MatchHelper::getGkStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9)/3.1);
    return result;
};

double MatchHelper::getCbStrength(Player tmpPlayer){
    double result = ((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9);
    return result;
};

double MatchHelper::getMfStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7);
    return result;
};

double MatchHelper::getStStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5);
    return result;
};
