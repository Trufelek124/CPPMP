#include "ClubHelper.h"

ClubHelper::ClubHelper()
{
    clubsDao = new ClubsDao();
    clubView = new ClubView();
    mainView = new MainView();
}

ClubHelper::~ClubHelper()
{
    //dtor
}

int ClubHelper::setUserClub(){
    clubsVec = clubsDao->getClubs();
    clubView->displayClubList(clubsVec);
    clubView->displayClubSetup();
    int userOption = mainView->getUserInput();
    clubVarTmp = clubsVec.at(userOption - 1);
    clubVarTmp.setPlayerClub(1);
    clubsDao->updateClub(clubVarTmp);
    return clubVarTmp.getClubId();
}
