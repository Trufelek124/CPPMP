#ifndef CLUBVIEW_H
#define CLUBVIEW_H

#include<vector>
#include"Club.h"
#include"PlayerView.h"
#include<string>

class ClubView
{
    public:
        ClubView();
        virtual ~ClubView();

        void displayClubInfo(Club club);
        void displayClubInfoInLine(Club club);
        void displayClubList(std::vector<Club> clubs);
        void displayClubSetup();

    protected:

    private:
        PlayerView* playerViewVar;
};

#endif // CLUBVIEW_H
