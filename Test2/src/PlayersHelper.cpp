#include "PlayersHelper.h"

PlayersHelper::PlayersHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
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
    double result = ((double) tmpPlayer.getDiving() + (double) tmpPlayer.getHandling()*0.7 + (double) tmpPlayer.getKicking()*0.5 + (double) tmpPlayer.getReflexes()*0.9);
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


int PlayersHelper::getPlayerWorth(Player player){
    int playerWorth = 0;
    double strength = 0.0;

    if(player.getPosition() == "GK"){
        playerWorth = ((int) (sqrt ((getGkStrength(player)) * 1000.0))); //for 100(max) - 10 million
    } else if(player.getPosition() == "CB"){
        playerWorth = ((int) (sqrt ((getCbStrength(player)) * 2500.0))); //for 100(max) - 25 million
    } else if(player.getPosition() == "MF"){
        playerWorth = ((int) (sqrt ((getMfStrength(player)) * 10000.0))); //for 100(max) - 100 million
    } else {
        playerWorth = ((int) (sqrt ((getStStrength(player)) * 7500.0))); //for 100(max) - 75 million
    }

    return playerWorth;
};
