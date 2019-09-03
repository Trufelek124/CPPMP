#include "PlayerView.h"

PlayerView::PlayerView()
{
    //ctor
}

PlayerView::~PlayerView()
{
    //dtor
}
void PlayerView::displayPlayersList(std::vector<Player> players){
    Player player;
    for(int i = 0; i < players.size(); i++){
        player = players.at(i);
        std::cout << player.getPlayerId() << " " << player.getName() << " " << player.getPosition() << " " << player.getClubId() << std::endl;
    };
};


void PlayerView::displayPlayer(Player player){
    std::cout << player.getPlayerId() << " " << player.getName() << " " << player.getPosition() << " " << player.getClubId() << std::endl;
};

void PlayerView::displayPlayersListTraining(std::vector<Player> players){
    for(int i = 0; i < players.size(); i++){
        Player tmpPlayer = players.at(i);
        std::cout << tmpPlayer.getPlayerId() << " " << tmpPlayer.getName() << " " << tmpPlayer.getPosition() << std::endl;
        std::cout << "Current training type: " << tmpPlayer.getTrainingType() << std::endl;
        std::cout << "GK stats:        " << std::endl;
        std::cout << "    Diving       " << tmpPlayer.getDiving() << std::endl;
        std::cout << "    Handling     " << tmpPlayer.getHandling() << std::endl;
        std::cout << "    Kicking      " << tmpPlayer.getKicking() << std::endl;
        std::cout << "    Reflex       " << tmpPlayer.getReflexes() << std::endl;
        std::cout << "CB stats:        " << std::endl;
        std::cout << "    Tackling     " << tmpPlayer.getTackling() << std::endl;
        std::cout << "    Heading      " << tmpPlayer.getHeading() << std::endl;
        std::cout << "    Marking      " << tmpPlayer.getMarking() << std::endl;
        std::cout << "    Intercepting " << tmpPlayer.getIntercepting() << std::endl;
        std::cout << "MF stats:        " << std::endl;
        std::cout << "    Vision       " << tmpPlayer.getVision() << std::endl;
        std::cout << "    Crossing     " << tmpPlayer.getCrossing() << std::endl;
        std::cout << "    Short passes " << tmpPlayer.getShortPasses() << std::endl;
        std::cout << "    Long passes  " << tmpPlayer.getLongPasses() << std::endl;
        std::cout << "    Free kicks   " << tmpPlayer.getFreeKicks() << std::endl;
        std::cout << "    Positioning  " << tmpPlayer.getPositioning() << std::endl;
        std::cout << "ST stats:        " << std::endl;
        std::cout << "    Finishing    " << tmpPlayer.getFinishing() << std::endl;
        std::cout << "    Power        " << tmpPlayer.getPower() << std::endl;
        std::cout << "    Volleys      " << tmpPlayer.getVolleys() << std::endl;
        std::cout << "    Long shots   " << tmpPlayer.getLongShots() << std::endl;
        std::cout << " " << std::endl;
    }
};
