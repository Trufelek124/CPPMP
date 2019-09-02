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
    std::cout << "Choose Your club" << std::endl;
    clubView->displayClubsInfo(clubsVec);
    clubView->displayClubSetup();
    int userOption = mainView->getUserInput();
    clubVarTmp = clubsVec.at(userOption - 1);
    clubVarTmp.setPlayerClub(1);
    clubsDao->updateClub(clubVarTmp);
    return clubVarTmp.getClubId();
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
