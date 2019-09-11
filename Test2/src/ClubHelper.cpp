#include "ClubHelper.h"

ClubHelper::ClubHelper()
{
    clubsDao = new ClubsDao();
    clubView = new ClubView();
    mainView = new MainView();
    playersDao = new PlayersDao();
}

ClubHelper::~ClubHelper()
{
    //dtor
}

int ClubHelper::setUserClub(std::vector<Club> clubsVec){
    try{
        std::cout << "Choose Your club" << std::endl;
        clubView->displayClubsInfo(clubsVec);
        clubView->displayClubSetup();
        int userOption = mainView->getUserInput();
        clubVarTmp = clubsVec.at(userOption - 1);
        clubVarTmp.setPlayerClub(1);
        clubsDao->updateClub(clubVarTmp);
    return clubVarTmp.getClubId();
    } catch(std::out_of_range e){
        std:: cerr << "Please choose one from the list" << std::endl;
        setUserClub(clubsVec);
    }
}

void ClubHelper::updateClubsPosition(std::vector<Club> clubsVec){
    std::vector<Club> clubsSortedByPoints = clubsVec;
    std::sort(clubsSortedByPoints.begin(), clubsSortedByPoints.end(), ClubComparator());

    int currentPoints = -1;
    int currentPosition = 1;

    for(int i = 0; i < clubsSortedByPoints.size(); i++){

        Club tmp = clubsSortedByPoints.at(i);

        if(currentPoints == -1 || currentPoints == tmp.getPoints()){
            tmp.setPosition(currentPosition);
        } else {
            currentPosition += 1;
            tmp.setPosition(currentPosition);
        }
        currentPoints = tmp.getPoints();
        clubsDao->updateClub(tmp);
    }
}

std::vector<Club> ClubHelper::chooseTacticsForClub(int playerClubId, std::vector<Club> clubsVec){
    Club tmpClub = clubsDao->getClub(playerClubId);
    std::vector<Club> vec;
    int response;
    std::cout << "Current team tactics: " << tmpClub.getTactics() << " " << tmpClub.getTacticsString() << std::endl;
    std::cout << "Please choose new tactics for You club (1 - 5: 1 - ultradeffensive, 5 - ultraoffensive), or type in 0 to skip this step: ";
    std::cin >> response;
    for(int i = 0; i < clubsVec.size(); i++){
        Club tmp = clubsVec.at(i);
        if(tmp.getClubId() == playerClubId && response > 0 && response <= 5){
            tmp.setTactics(response);
            clubsDao->updateClub(tmp);
        }
        vec.push_back(tmp);
    }
    return vec;
};
