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
