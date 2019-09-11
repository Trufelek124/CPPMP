#include "PlayersHelper.h"

PlayersHelper::PlayersHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
    playersView = new PlayerView();
}

PlayersHelper::~PlayersHelper()
{
    //dtor
}

void PlayersHelper::randommizeInitialSquads(){
    std::vector<Player> goalkeepers = playersDao->getPlayersForPosition("GK");
    std::vector<Player> defenders = playersDao->getPlayersForPosition("CB");
    std::vector<Player> midfielders = playersDao->getPlayersForPosition("MF");
    std::vector<Player> strikers = playersDao->getPlayersForPosition("ST");
    std::vector<Club> clubs = clubsDao->getClubs();
    int i = 0;//interator

    //the default formation id 442, so that's how we randomize initial squads

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(goalkeepers.begin(), goalkeepers.end());
    std::random_shuffle(defenders.begin(), defenders.end());
    std::random_shuffle(midfielders.begin(), midfielders.end());
    std::random_shuffle(strikers.begin(), strikers.end());

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it, i++){
        Player goalkeeper;
        goalkeeper = goalkeepers.at(i);
        int id = it->getClubId();
        goalkeeper.setClubId(id);
        playersDao->updatePlayer(goalkeeper);
    }

    i = 0;

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it){
        for(int j = 0; j < 4; j++, i++){
            Player defender;
            defender = defenders.at(i);
            defender.setClubId(it->getClubId());
            playersDao->updatePlayer(defender);


            Player midfielder;
            midfielder = midfielders.at(i);
            midfielder.setClubId(it->getClubId());
            playersDao->updatePlayer(midfielder);
        }
    }

    i = 0;

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it){
        for(int j = 0; j < 2; j++, i++){
            Player striker;
            striker = strikers.at(i);
            striker.setClubId(it->getClubId());
            playersDao->updatePlayer(striker);
        }
    }

    i = 0;

}

double PlayersHelper::getGkStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9)/3.1);
    return result;
};

double PlayersHelper::getCbStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getTackling()*0.75 + (double) tmpPlayer.getHeading()*0.5 + (double) tmpPlayer.getMarking()*0.3 + (double) tmpPlayer.getIntercepting())/2.55);
    return result;
};

double PlayersHelper::getMfStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getVision() + (double) tmpPlayer.getCrossing() * 0.9 + (double) tmpPlayer.getShortPasses()*0.9 + (double) tmpPlayer.getLongPasses()*0.8 + (double) tmpPlayer.getFreeKicks()*0.1 + (double) tmpPlayer.getPositioning()*0.5 + (double) tmpPlayer.getLongShots()*0.5)/4.7);
    return result;
};

double PlayersHelper::getStStrength(Player tmpPlayer){
    double result = (((double) tmpPlayer.getPositioning() + (double) tmpPlayer.getFinishing() + (double) tmpPlayer.getPower()*0.8 + (double) tmpPlayer.getVolleys()*0.2 + (double) tmpPlayer.getLongShots()*0.5)/3.5);
    return result;
};


int PlayersHelper::getPlayerOverallScore(Player tmpPlayer){
    int overallScore;
    double ghStrength = 0.0; //between 0 and 100
    double cbStrength = 0.0;
    double mfStrength = 0.0;
    double stStrength = 0.0;

    ghStrength = getGkStrength(tmpPlayer);
    cbStrength = getCbStrength(tmpPlayer);
    mfStrength = getMfStrength(tmpPlayer);
    stStrength = getStStrength(tmpPlayer);

    if(tmpPlayer.getPosition() == "GK"){
        overallScore = (int) ghStrength; //for 100(max)
    } else if(tmpPlayer.getPosition() == "CB"){
        overallScore = (int) (cbStrength*0.8 + mfStrength * 0.15 + stStrength * 0.05);
    } else if(tmpPlayer.getPosition() == "MF"){
        overallScore = (int) (cbStrength*0.1 + mfStrength * 0.75 + stStrength * 0.15);
    } else if(tmpPlayer.getPosition() == "ST"){
        overallScore = (int) (cbStrength*0.05 + mfStrength * 0.15 + stStrength * 0.8);
    }
    return overallScore;
};

std::vector<Player> PlayersHelper::updateOverallScoreForPlayers(std::vector<Player> players){
    for(int i = 0; i < players.size(); i++){
        Player tmpPlayer = players.at(i);
        tmpPlayer.setOverallScore(getPlayerOverallScore(tmpPlayer));
        tmpPlayer.setNettWorth(getPlayerWorth(tmpPlayer));
        playersDao->updatePlayer(tmpPlayer);
    }
    std::vector<Player> updatedPlayers = playersDao->getPlayers();
    return updatedPlayers;
}

int PlayersHelper::getPlayerWorth(Player player){
    int playerWorth = 0;

    if(player.getPosition() == "GK"){
        playerWorth = ((int) ((getGkStrength(player)*getGkStrength(player)) * 500.0)); //for 100(max) - 10 million
    } else if(player.getPosition() == "CB"){
        playerWorth = ((int) ((getCbStrength(player)*getCbStrength(player)) * 1250.0)); //for 100(max) - 25 million
    } else if(player.getPosition() == "MF"){
        playerWorth = ((int) ((getMfStrength(player)*getMfStrength(player)) * 1500.0)); //for 100(max) - 100 million
    } else if(player.getPosition() == "ST"){
        playerWorth = ((int) ((getStStrength(player)*getStStrength(player)) * 3750.0)); //for 100(max) - 75 million
    }

    return playerWorth;
};

void PlayersHelper::trainPlayer(Player tmpPlayer){
    int stat;
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    std::string treningType = tmpPlayer.getTrainingType();
    double trainingEffectiveness = ((double) dis(gen)) - tmpPlayer.getAge()/100; //after 50 - no chance

    if(trainingEffectiveness > 0.5){
        if(treningType == "GK"){
            stat = (rand() % 4);
            switch(stat){
            case 0:
                //diving
                if(tmpPlayer.getDiving() < 97)
                    tmpPlayer.setDiving(tmpPlayer.getDiving()+2);
                break;
            case 1:
                //handling
                if(tmpPlayer.getHandling() < 97)
                    tmpPlayer.setHandling(tmpPlayer.getHandling()+2);
                break;
            case 2:
                //kicking
                if(tmpPlayer.getKicking() < 97)
                    tmpPlayer.setKicking(tmpPlayer.getKicking()+2);
                break;
            default:
                //reflex
                if(tmpPlayer.getReflexes() < 97)
                    tmpPlayer.setReflexes(tmpPlayer.getReflexes()+2);
                break;
            }
        } else if(treningType == "CB"){
            stat = (rand() % 4);
            switch(stat){
            case 0:
                //tackling
                if(tmpPlayer.getTackling() < 97)
                    tmpPlayer.setTackling(tmpPlayer.getTackling()+2);
                break;
            case 1:
                //heading
                if(tmpPlayer.getHeading() < 97)
                    tmpPlayer.setHeading(tmpPlayer.getHeading()+2);
                break;
            case 2:
                //marking
                if(tmpPlayer.getMarking() < 97)
                    tmpPlayer.setMarking(tmpPlayer.getMarking()+2);
                break;
            default:
                //intercepting
                if(tmpPlayer.getIntercepting() < 97)
                    tmpPlayer.setIntercepting(tmpPlayer.getIntercepting()+2);
                break;
            }
        } else if(treningType == "MF"){
            stat = (rand() % 7);
            switch(stat){
            case 0:
                //vision
                if(tmpPlayer.getVision() < 97)
                    tmpPlayer.setVision(tmpPlayer.getVision()+2);
                break;
            case 1:
                //crossing
                if(tmpPlayer.getCrossing() < 97)
                    tmpPlayer.setCrossing(tmpPlayer.getCrossing()+2);
                break;
            case 2:
                //short passes
                if(tmpPlayer.getShortPasses() < 97)
                    tmpPlayer.setShortPasses(tmpPlayer.getShortPasses()+2);
                break;
            case 3:
                //long passes
                if(tmpPlayer.getLongPasses() < 97)
                    tmpPlayer.setLongPasses(tmpPlayer.getLongPasses()+2);
                break;
            case 4:
                //free kicks
                if(tmpPlayer.getFreeKicks() < 97)
                    tmpPlayer.setFreeKicks(tmpPlayer.getFreeKicks()+2);
                break;
            case 5:
                //positioning
                if(tmpPlayer.getPositioning() < 97)
                    tmpPlayer.setPositioning(tmpPlayer.getPositioning()+2);
                break;
            default:
                //long shots
                if(tmpPlayer.getLongShots() < 97)
                    tmpPlayer.setLongShots(tmpPlayer.getLongShots()+2);
                break;
            }
        } else if(treningType == "ST"){
            stat = (rand() % 5);
            switch(stat){
            case 0:
                //positioning
                if(tmpPlayer.getPositioning() < 97)
                    tmpPlayer.setPositioning(tmpPlayer.getPositioning()+2);
                break;
            case 1:
                //finishing
                if(tmpPlayer.getFinishing() < 97)
                    tmpPlayer.setFinishing(tmpPlayer.getFinishing()+2);
                break;
            case 2:
                //power
                if(tmpPlayer.getPower() < 97)
                    tmpPlayer.setPower(tmpPlayer.getPower()+2);
                break;
            case 3:
                //volleys
                if(tmpPlayer.getVolleys() < 97)
                    tmpPlayer.setVolleys(tmpPlayer.getVolleys()+2);
                break;
            default:
                //long shots
                if(tmpPlayer.getLongShots() < 97)
                    tmpPlayer.setLongShots(tmpPlayer.getLongShots()+2);
                break;
            }
        } else { //all around training
            for(int i = 0; i < 3; i++){
                stat = (rand() % 19);
                switch(stat){
                case 0:
                    //vision
                    if(tmpPlayer.getVision() < 98)
                        tmpPlayer.setVision(tmpPlayer.getVision()+1);
                    break;
                case 1:
                    //crossing
                    if(tmpPlayer.getCrossing() < 98)
                        tmpPlayer.setCrossing(tmpPlayer.getCrossing()+1);
                    break;
                case 2:
                    //short passes
                    if(tmpPlayer.getShortPasses() < 98)
                        tmpPlayer.setShortPasses(tmpPlayer.getShortPasses()+1);
                    break;
                case 3:
                    //long passes
                    if(tmpPlayer.getLongPasses() < 98)
                        tmpPlayer.setLongPasses(tmpPlayer.getLongPasses()+1);
                    break;
                case 4:
                    //free kicks
                    if(tmpPlayer.getFreeKicks() < 98)
                        tmpPlayer.setFreeKicks(tmpPlayer.getFreeKicks()+1);
                    break;
                case 5:
                    //positioning
                    if(tmpPlayer.getPositioning() < 98)
                        tmpPlayer.setPositioning(tmpPlayer.getPositioning()+1);
                    break;
                case 6:
                    //tackling
                    if(tmpPlayer.getTackling() < 98)
                        tmpPlayer.setTackling(tmpPlayer.getTackling()+1);
                    break;
                case 7:
                    //heading
                    if(tmpPlayer.getHeading() < 98)
                        tmpPlayer.setHeading(tmpPlayer.getHeading()+1);
                    break;
                case 8:
                    //marking
                    if(tmpPlayer.getMarking() < 98)
                        tmpPlayer.setMarking(tmpPlayer.getMarking()+1);
                    break;
                case 9:
                    //intercepting
                    if(tmpPlayer.getIntercepting() < 98)
                        tmpPlayer.setIntercepting(tmpPlayer.getIntercepting()+1);
                    break;
                case 10:
                    //positioning
                    if(tmpPlayer.getPositioning() < 98)
                        tmpPlayer.setPositioning(tmpPlayer.getPositioning()+1);
                    break;
                case 11:
                    //finishing
                    if(tmpPlayer.getFinishing() < 98)
                        tmpPlayer.setFinishing(tmpPlayer.getFinishing()+1);
                    break;
                case 12:
                    //power
                    if(tmpPlayer.getPower() < 98)
                        tmpPlayer.setPower(tmpPlayer.getPower()+1);
                    break;
                case 13:
                    //volleys
                    if(tmpPlayer.getVolleys() < 98)
                        tmpPlayer.setVolleys(tmpPlayer.getVolleys()+1);
                    break;
                case 14:
                    //diving
                    if(tmpPlayer.getDiving() < 98)
                        tmpPlayer.setDiving(tmpPlayer.getDiving()+1);
                    break;
                case 15:
                    //handling
                    if(tmpPlayer.getHandling() < 98)
                        tmpPlayer.setHandling(tmpPlayer.getHandling()+1);
                    break;
                case 16:
                    //kicking
                    if(tmpPlayer.getKicking() < 98)
                        tmpPlayer.setKicking(tmpPlayer.getKicking()+1);
                    break;
                case 17:
                    //reflex
                    if(tmpPlayer.getReflexes() < 98)
                        tmpPlayer.setReflexes(tmpPlayer.getReflexes()+1);
                    break;
                default:
                    //long shots
                    if(tmpPlayer.getLongShots() < 98)
                        tmpPlayer.setLongShots(tmpPlayer.getLongShots()+1);
                    break;
                }
            }
        }
    }
    playersDao->updatePlayer(tmpPlayer);
};


std::vector<Player> PlayersHelper::playersClubPlayersTraining(std::vector<Player> playersVec, int playerClubId){
    std::vector<Player> playersClubPlayers;
    bool done = false;
    int response;
    Player trainedPlayer;
    std::string responseType;

    for(int i = 0; i < playersVec.size(); i++){
        Player tmpPlayer = playersVec.at(i);
        if(tmpPlayer.getClubId() == playerClubId){
            playersClubPlayers.push_back(tmpPlayer);
        }
    };

    playersView->displayPlayersListTraining(playersClubPlayers);
    while(!done){
        std::cout << "If you want to change training type for any of Your players please type in its id, if not - type in 0: " << std::endl;
        std::cin >> response;
        if(response == 0){
            done = true;
        } else {
            for(int i = 0; i < playersClubPlayers.size(); i++){
                if(playersClubPlayers.at(i).getPlayerId() == response){
                    std::cout << "Now type in training type for Your player (GK, CB, MF, ST, or anything different for general training: " << std::endl;
                    std::cin >> responseType;

                    playersClubPlayers.at(i).setTrainingType(responseType);
                }
            }
        }
    }

    for(int i = 0; i < playersVec.size(); i++){
        Player tmpPlayer = playersVec.at(i);
        if(tmpPlayer.getClubId() != playerClubId){
            playersClubPlayers.push_back(tmpPlayer);
        }
    };

    return playersClubPlayers;
};
