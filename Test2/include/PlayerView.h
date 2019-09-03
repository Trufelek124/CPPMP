#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include<iostream>
#include"Player.h"
#include<vector>
#include <string>

class PlayerView
{
    public:
        PlayerView();
        virtual ~PlayerView();

        void displayPlayersList(std::vector<Player> players);
        void displayPlayer(Player player);
        void simpleStatsView(Player player);
        void playerDetails(Player tmpPlayer);
        void displayPlayersListTraining(std::vector<Player> players);

    protected:

    private:
};

#endif // PLAYERVIEW_H
