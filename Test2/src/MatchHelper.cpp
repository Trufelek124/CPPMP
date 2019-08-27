#include "MatchHelper.h"

MatchHelper::MatchHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
    timetableDao = new TimetableDao();
}

MatchHelper::~MatchHelper()
{
    //dtor
}

void MatchHelper::match(int homeClubId, int awayClubId, int timetableId, std::vector<Club> clubsVec){Club tmp;
    Player tmpPlayer;
    Club homeClub;
    Club awayClub;
    std::vector<Player> homeTeamPlayers;
    std::vector<Player> awayTeamPlayers;
    double homeFieldAdvantage;
    double luckHomeTeam;
    double luckAwayTeam;

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

    homeFieldAdvantage = ((double) dis(gen))/2;

    std::mt19937 gen2(rd());
    std::uniform_real_distribution<> dis2(0, 1);

    luckHomeTeam = ((double) dis2(gen2))/2;

    std::mt19937 gen3(rd());
    std::uniform_real_distribution<> dis3(0, 1);

    luckAwayTeam = ((double) dis3(gen3))/2;

    double homeTeamGKStrength;
    double awayTeamGKStrength;
    double homeTeamCBStrength;
    double awayTeamCBStrength;
    double homeTeamMFStrength;
    double awayTeamMFStrength;
    double homeTeamSTStrength;
    double awayTeamSTStrength;

    //home team strength
    for(int i = 0; i < homeTeamPlayers.size(); i++){
       tmpPlayer = homeTeamPlayers.at(i);
       if(tmpPlayer.getPosition() == "GK"){
            homeTeamGKStrength = (((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9)/3.1);//handling, diving, kicking, reflexes
       } else if(tmpPlayer.getPosition() == "CB"){
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = (((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = ((((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7)*0.25);
           //positioning, finishing, power, volleys, longShots
           stStrength = ((((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5)*0.1);
           homeTeamCBStrength += cbStrength;
           homeTeamMFStrength += mfStrength;
           homeTeamSTStrength += stStrength;
           //dodawac, a pozniej podzielic na 4 - ju¿ pozniej
       } else if(tmpPlayer.getPosition() == "MF"){
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = ((((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55)*0.25);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7);
           //positioning, finishing, power, volleys, longShots
           stStrength = ((((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5)*0.25);
           homeTeamCBStrength += cbStrength;
           homeTeamMFStrength += mfStrength;
           homeTeamSTStrength += stStrength;
       } else {
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = ((((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55)*0.1);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = ((((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7)*0.1);
           //positioning, finishing, power, volleys, longShots
           stStrength = (((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5);
           homeTeamCBStrength += cbStrength;
           homeTeamMFStrength += mfStrength;
           homeTeamSTStrength += stStrength;
       }
    }
    homeTeamCBStrength = homeTeamCBStrength/5.4;
    homeTeamMFStrength = homeTeamMFStrength/5.4;
    homeTeamSTStrength = homeTeamSTStrength/3.4;


    //away team strength
    for(int i = 0; i < awayTeamPlayers.size(); i++){
       tmpPlayer = awayTeamPlayers.at(i);
       if(tmpPlayer.getPosition() == "GK"){
            awayTeamGKStrength = (((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9)/3.1);//handling, diving, kicking, reflexes
       } else if(tmpPlayer.getPosition() == "CB"){
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = (((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = ((((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7)*0.25);
           //positioning, finishing, power, volleys, longShots
           stStrength = ((((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5)*0.1);
           awayTeamCBStrength += cbStrength;
           awayTeamMFStrength += mfStrength;
           awayTeamSTStrength += stStrength;
           //dodawac, a pozniej podzielic na 4 - ju¿ pozniej
       } else if(tmpPlayer.getPosition() == "MF"){
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = ((((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55)*0.25);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = (((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7);
           //positioning, finishing, power, volleys, longShots
           stStrength = ((((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5)*0.25);
           awayTeamCBStrength += cbStrength;
           awayTeamMFStrength += mfStrength;
           awayTeamSTStrength += stStrength;
       } else {
           double cbStrength = 0.0;
           double mfStrength = 0.0;
           double stStrength = 0.0;
           //tackling, heading, marking, intercepting
           cbStrength = ((((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55)*0.1);
           //vision, crossing, shortPasses, longPasses, freeKicks, positioning, longShots
           mfStrength = ((((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7)*0.1);
           //positioning, finishing, power, volleys, longShots
           stStrength = (((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5);
           awayTeamCBStrength += cbStrength;
           awayTeamMFStrength += mfStrength;
           awayTeamSTStrength += stStrength;
       }
    }
    awayTeamCBStrength = homeTeamCBStrength/5.4;
    awayTeamMFStrength = homeTeamMFStrength/5.4;
    awayTeamSTStrength = homeTeamSTStrength/3.4;
    //Mam sklady i zespoly
    //TODO
    //Algorytm meczowy
}
