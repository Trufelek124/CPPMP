#ifndef MAINVIEW_H
#define MAINVIEW_H

#include<iostream>

class MainView
{
    public:
        MainView();
        virtual ~MainView();

        void displayTestMenu();
        void displayMatchScore(int homeClubId, int awayClubId, int homeTeamGoals, int awayTeamGoals);
        int getUserInput();
        void displayInstructions();
        void displayAbout();

    protected:

    private:
};

#endif // MAINVIEW_H
