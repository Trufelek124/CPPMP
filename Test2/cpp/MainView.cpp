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
std::cout << "0. Main menu" << std::endl;
std::cout << "1. Setup database" << std::endl;
std::cout << "2. Select players" << std::endl;
std::cout << "3. Drop database" << std::endl;
std::cout << "4. Exit" << std::endl;
std::cout << "5. Club+players" << std::endl;
std::cout << "6. Update player" << std::endl;
std::cout << "8. Clubs list" << std::endl;
std::cout << "9. Timetable test" << std::endl;
std::cout << "" << std::endl;

}

int MainView::getUserInput(){
    int response = 0;
    std::cin >> response;
    return response;
}
