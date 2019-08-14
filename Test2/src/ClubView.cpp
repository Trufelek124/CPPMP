#include "ClubView.h"

ClubView::ClubView()
{
    playerViewVar = new PlayerView();
}

ClubView::~ClubView()
{
    //dtor
}

void ClubView::displayClubInfo(Club club){
    std::string myClub = club.getPlayerClub() == 1 ? " MY CLUB" : "";
    std::cout<< club.getName() << myClub << std::endl;
    std::cout << "Position: " << club.getPosition() << std::endl;
    std::cout << "Points: " << club.getPoints() << std::endl;
    std::cout << "Players:" << std::endl;
    playerViewVar->displayPlayersList(club.getPlayers());
};

void ClubView::displayClubInfoInLine(Club club){
    std::string myClub = club.getPlayerClub() == 1 ? " MY CLUB" : "";
    std::cout<< club.getName() << " - position: " << club.getPosition() << " - points: " << club.getPoints() << myClub << std::endl;
};

void ClubView::displayClubList(std::vector<Club> clubs){
    for(int i = 0; i < clubs.size(); i++){
        displayClubInfoInLine(clubs.at(i));
    };
};

void ClubView::displayClubSetup(){
    std::cout << " " << std::endl;
    std::cout << "Chose your club: " << std::endl;
};