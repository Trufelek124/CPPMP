#ifndef MAINVIEW_H
#define MAINVIEW_H

#include<iostream>

class MainView
{
    public:
        MainView();
        virtual ~MainView();

        void displayTestMenu();
        int getUserInput();

    protected:

    private:
};

#endif // MAINVIEW_H
