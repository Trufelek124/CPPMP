#include "TransferListHelper.h"

TransferListHelper::TransferListHelper()
{
    playersDao = new PlayersDao();
    playerView = new PlayerView();
    playersHelper = new PlayersHelper();
    clubsDao = new ClubsDao();
}

TransferListHelper::~TransferListHelper()
{
    //dtor
}

void TransferListHelper::getTransferList(){
    int transferOutResponse, transferInResponse, transferInValue, transferOutValue, clubBudget, differenceForClub;
    Player transferOut, transferIn;
    Club playerClub;
    std::vector<Player> freePlayersList = playersDao->getPlayersForClub(0); //for 0 it shows all players without clubs
    std::cout << "Transfer list" << std::endl;
    playerView->displayPlayersList(freePlayersList);
    std::vector<Player> playersPlayersList = playersDao->getPlayersForPlayersClub(); //for 0 it shows all players for player clubs
    std::cout << "My players list" << std::endl;
    playerView->displayPlayersList(playersPlayersList);
    std::cout << "Please type in player id from Your team to trade: ";
    std::cin >> transferOutResponse;
    std::cout << std::endl << "Please type in player id of player You want from transfer list: ";
    std::cin >> transferInResponse;
    std::cout << std::endl;
    transferOut = playersDao->getPlayer(transferOutResponse);
    transferIn = playersDao->getPlayer(transferInResponse);

    transferOutValue = playersHelper->getPlayerWorth(transferOut);
    transferInValue = playersHelper->getPlayerWorth(transferIn);

    playerClub = clubsDao->getPlayerClub();
    clubBudget = playerClub.getBudget();

    if((clubBudget + transferOutValue) <= transferInValue){
        differenceForClub = transferOutValue - transferInValue;
        playerClub.setBudget(clubBudget+differenceForClub);
        transferOut.setClubId(0);
        transferIn.setClubId(playerClub.getClubId());

        playersDao->updatePlayer(transferOut);
        playersDao->updatePlayer(transferIn);
        clubsDao->updateClub(playerClub);
    } else {
        std::cout << "You don't have sufficient founds" << std::endl;
    }
};

void TransferListHelper::transferPlayerToTheTeam(){

};
