#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include<iostream>
#include"Player.h"
#include<vector>

class PlayerView
{
    public:
        PlayerView();
        virtual ~PlayerView();

        void displayPlayersList(std::vector<Player> players);
        void displayPlayer(Player player);

    protected:

    private:
};

#endif // PLAYERVIEW_H
