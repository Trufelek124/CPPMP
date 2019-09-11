#include "MainView.h"

MainView::MainView()
{
    //ctor
}

MainView::~MainView()
{
    //dtor
}

void MainView::displayTestMenu(){
std::cout << "------MENAGER PILKARSKI------by Krzysztof Werner------" << std::endl;
std::cout << "" << std::endl;
std::cout << "" << std::endl;
std::cout << "MENU" << std::endl;
std::cout << "" << std::endl;
std::cout << "1. New game" << std::endl;
std::cout << "2. Setup database" << std::endl;
std::cout << "3. Drop database" << std::endl;
std::cout << "4. Instructions" << std::endl;
std::cout << "5. Exit" << std::endl;
std::cout << "6. About" << std::endl;
std::cout << "" << std::endl;

}

int MainView::getUserInput(){
    int response = 0;
    std::cin >> response;
    return response;
}

void MainView::displayMatchScore(int homeClubId, int awayClubId, int homeTeamGoals, int awayTeamGoals){
    std::cout << homeClubId << " vs " << awayClubId << std::endl;
    std::cout << homeTeamGoals << " : " << awayTeamGoals << std::endl;
}

void MainView::displayInstructions(){
std::cout << "" << std::endl;
std::cout << "    INSTRUCTIONS" << std::endl;
std::cout << "" << std::endl;
std::cout << "    The game uses console interface and it's text only." << std::endl;
std::cout << "    To set up a game the user must first prepare the database using options 3 and 2 from the main menu one after another." << std::endl;
std::cout << "    After that step user can start a new game, by choosing option 1 from the main menu." << std::endl;
std::cout << "    First step is to choose the club - the clubs with players and it's stats should be displayed on the screen." << std::endl;
std::cout << "    After that the timetable for the season is shown, and player have the chance to choose tactics for the team." << std::endl;
std::cout << "    The tactics to choose are:" << std::endl;
std::cout << "        1 - ultradefensive" << std::endl;
std::cout << "        2 - defensive" << std::endl;
std::cout << "        3 - balanced (choosed automatically)" << std::endl;
std::cout << "        4 - ultraoffensive" << std::endl;
std::cout << "        5 - offensive" << std::endl;
std::cout << "    After that step the match is played, the results and the table are shown." << std::endl;
std::cout << "    Then user can choose the training type for the players, or leave things as they are." << std::endl;
std::cout << "    If user chooses to leave default training ('A'), then the player have a chance to gain +1 on 3 of its stats" << std::endl;
std::cout << "    If user chooses the special training dependable on the position, or stats to change, player can gain +1, on one of its stats specified by the raining type." << std::endl;
std::cout << "    Training types are 'GK', 'CB', 'MF' and 'ST'" << std::endl;
std::cout << "    In the middle of the season hte transfer window appears, and players can trade any of its players, to ones on the transfer list." << std::endl;
std::cout << "    Both lists (players team, and free players) are shown on the screen." << std::endl;
std::cout << "    After transfer window, the rest of the game runs as earlier." << std::endl;
std::cout << "    At the end of the season, transfer window is once again, and after that official standings are presented." << std::endl;
std::cout << "    After that user can choose to play another season or not." << std::endl;
}

void MainView::displayAbout(){
std::cout << "    Menager pi³karski" << std::endl;
std::cout << "    " << std::endl;
std::cout << "    Written by:" << std::endl;
std::cout << "        Krzysztof Werner" << std::endl;
std::cout << "    " << std::endl;
std::cout << "    2019" << std::endl;
std::cout << "    " << std::endl;
std::cout << "    Project for PK4 classes" << std::endl;
}
