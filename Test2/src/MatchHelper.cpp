#include "MatchHelper.h"

MatchHelper::MatchHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
    timetableDao = new TimetableDao();
    playerView = new PlayerView();
    mainView = new MainView();
}

MatchHelper::~MatchHelper()
{
    //dtor
}

void MatchHelper::match(int homeClubId, int awayClubId, int timetableId, std::vector<Club> clubsVec){
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

    if(homeTeamPlayers.empty() || awayTeamPlayers.empty()){
        homeTeamPlayers = playersDao->getPlayersForClub(homeClubId);
        awayTeamPlayers = playersDao->getPlayersForClub(awayClubId);
    }

    Timetable timetable = timetableDao->getTimetable(timetableId);

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
            homeTeamGKStrength = getGkStrength(tmpPlayer);//handling, diving, kicking, reflexes
       } else if(tmpPlayer.getPosition() == "CB"){
           //tackling, heading, marking, intercepting
           cbStrength = getCbStrength(tmpPlayer);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (getMfStrength(tmpPlayer)*0.25);
           //positioning, finishing, power, volleys, longShots
           stStrength = (getStStrength(tmpPlayer)*0.1);
           //dodawac, a pozniej podzielic na 4 - ju¿ pozniej
       } else if(tmpPlayer.getPosition() == "MF"){
           //tackling, heading, marking, intercepting
           cbStrength = (getCbStrength(tmpPlayer)*0.25);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = getMfStrength(tmpPlayer);
           //positioning, finishing, power, volleys, longShots
           stStrength = (getStStrength(tmpPlayer)*0.25);
       } else {
           //tackling, heading, marking, intercepting
           cbStrength = (getCbStrength(tmpPlayer)*0.1);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (getMfStrength(tmpPlayer)*0.1);
           //positioning, finishing, power, volleys, longShots
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
            awayTeamGKStrength = getGkStrength(tmpPlayer);//handling, diving, kicking, reflexes
       } else if(tmpPlayer.getPosition() == "CB"){
           //tackling, heading, marking, intercepting
           cbStrength = getCbStrength(tmpPlayer);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (getMfStrength(tmpPlayer)*0.25);
           //positioning, finishing, power, volleys, longShots
           stStrength = (getStStrength(tmpPlayer)*0.1);
           //dodawac, a pozniej podzielic na 4 - ju¿ pozniej
       } else if(tmpPlayer.getPosition() == "MF"){
           //tackling, heading, marking, intercepting
           cbStrength = (getCbStrength(tmpPlayer)*0.25);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = getMfStrength(tmpPlayer);
           //positioning, finishing, power, volleys, longShots
           stStrength = (getStStrength(tmpPlayer)*0.25);
       } else {
           //tackling, heading, marking, intercepting
           cbStrength = (getCbStrength(tmpPlayer)*0.1);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (getMfStrength(tmpPlayer)*0.1);
           //positioning, finishing, power, volleys, longShots
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
    //TODO
    //Algorytm meczowy

    homeTeamChancesCreated = (int) ((((homeTeamSTStrength/100)*8 + (homeTeamMFStrength/100)*3 + (homeTeamCBStrength/100)) + homeFieldAdvantage) * (1/luckHomeTeam));
    awayTeamChancesCreated = (int) (((awayTeamSTStrength/100)*8 + (awayTeamMFStrength/100)*3 + (awayTeamCBStrength/100)) * (1/luckAwayTeam));

    //Percent of saved shots
    homeTeamShotsSaved = (((homeTeamGKStrength/100)*0.8 + (awayTeamCBStrength/100)*0.5 + ((homeFieldAdvantage/100)*5)) + (luckHomeTeam/100)*5);
    awayTeamShotsSaved = (((homeTeamGKStrength/100)*0.8 + (awayTeamCBStrength/100)*0.5) + (luckAwayTeam/100)*5);


    homeTeamGoals = homeTeamShotsSaved/(awayTeamShotsSaved*10);
    awayTeamGoals = awayTeamChancesCreated/(homeTeamShotsSaved*10);

    mainView->displayMatchScore(homeClubId, awayClubId, homeTeamGoals, awayTeamGoals);

}

double MatchHelper::getGkStrength(Player tmpPlayer){
    //playerView->displayPlayer(tmpPlayer);
    double result = (((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9)/3.1);
    return result;
};

double MatchHelper::getCbStrength(Player tmpPlayer){
    //playerView->displayPlayer(tmpPlayer);
    double result = ((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9);
    return result;
};

double MatchHelper::getMfStrength(Player tmpPlayer){
    //playerView->displayPlayer(tmpPlayer);
    double result = (((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7);
    return result;
};

double MatchHelper::getStStrength(Player tmpPlayer){
    //playerView->displayPlayer(tmpPlayer);
    double result = (((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5);
    return result;
};
