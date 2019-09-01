#include "TransferListHelper.h"

TransferListHelper::TransferListHelper()
{
    playersDao = new PlayersDao();
    playerView = new PlayerView();
}

TransferListHelper::~TransferListHelper()
{
    //dtor
}

void TransferListHelper::getTransferList(){
    std::vector<Player> freePlayersList = playersDao->getPlayersForClub(0); //for 0 it shows all players without clubs
    std::cout << "Transfer list" << std::endl;
    playerView->displayPlayersList(freePlayersList);

};

void TransferListHelper::transferPlayerToTheTeam(){

};
