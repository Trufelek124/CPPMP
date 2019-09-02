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

void TransferListHelper::transferWindow(int playerClubId){
    bool done = false;
        int transferOutResponse, transferInResponse;

    while(!done){
        std::vector<Player> playersPlayersList = playersDao->getPlayersForClub(playerClubId); //for 0 it shows all players for player clubs
        std::vector<Player> freePlayersList = playersDao->getPlayersForClub(0); //for 0 it shows all players without clubs
        std::cout << "Team players list" << std::endl;
        playerView->displayPlayersList(playersPlayersList);
        std::cout << std::endl;
        std::cout << "Transfer list" << std::endl;
        playerView->displayPlayersList(freePlayersList);
        std::cout << "Please type in player id from Your team to trade, or type 0 to exit: ";
        std::cin >> transferOutResponse;

        if(transferOutResponse != 0){
            std::cout << std::endl << "Please type in player id of player You want from transfer list: ";
            std::cin >> transferInResponse;
            std::cout << std::endl;
            makeTransfer(transferOutResponse, transferInResponse, playerClubId, playersPlayersList, freePlayersList);
            system("pause");
            system ("CLS");
        } else {
            done = true;
        }
    }
};

void TransferListHelper::makeTransfer(int transferOutResponse, int transferInResponse, int playerClubId, std::vector<Player> playersPlayersList, std::vector<Player> freePlayersList){
    int transferInValue, transferOutValue, clubBudget, differenceForClub;
    Player transferOut, transferIn;
    Club playerClub;
    playerClub = clubsDao->getClub(playerClubId);
    for(int i = 0; i < playersPlayersList.size(); i++){
        Player tmp = playersPlayersList.at(i);
        if(tmp.getPlayerId() == transferOutResponse){
            transferOut = tmp;
        }
    }
    for(int i = 0; i < freePlayersList.size(); i++){
        Player tmp = freePlayersList.at(i);
        if(tmp.getPlayerId() == transferInResponse){
            transferIn = tmp;
        }
    }

    if(transferOut.getClubId() != playerClubId){
        std::cout << "You can transfer out only Your players!" << std::endl;
    } else if(transferIn.getClubId() != 0){
        std::cout << "You can transfer in only players from transfer list!" << std::endl;
    } else {

        transferOutValue = playersHelper->getPlayerWorth(transferOut);
        transferInValue = playersHelper->getPlayerWorth(transferIn);

        playerClub = clubsDao->getPlayerClub();
        clubBudget = playerClub.getBudget();

        if((clubBudget + transferOutValue) >= transferInValue){
            differenceForClub = transferOutValue - transferInValue;
            playerClub.setBudget(clubBudget+differenceForClub);
            transferOut.setClubId(0);
            transferIn.setClubId(playerClub.getClubId());

            playersDao->updatePlayer(transferOut);
            playersDao->updatePlayer(transferIn);
            clubsDao->updateClub(playerClub);
            std::cout << "Transfer made :)." << std::endl;
        } else {
            std::cout << "You don't have sufficient founds." << std::endl;
            std::cout << "You have: " << clubBudget << " + " << transferOutValue << ", while You need: " << transferInValue << std::endl;
        }
    }

}
