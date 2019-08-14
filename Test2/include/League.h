#ifndef LEAGUE_H
#define LEAGUE_H

#include<vector>
#include"Club.h"

class League
{
    public:
        League();
        virtual ~League();

        int getLeagueId() { return leagueId; }
        void setLeagueId(int val) { leagueId = val; }
        std::vector<int> getClubsIds() { return clubsIds; }
        void setClubsIds(std::vector<int> val) { clubsIds = val; }
        int getSeason() { return seasonId; }
        void setSeason(int val) { seasonId = val; }
        int getMatchweek() { return matchweek; }
        void setMatchweek(int val) { matchweek = val; }
        std::vector<Club> getClubs() { return clubs; }
        void setClubs(std::vector<Club> val) { clubs = val; }

    protected:

    private:
        int leagueId;
        std::vector<int> clubsIds;
        int seasonId;
        int matchweek;
        std::vector<Club> clubs;
};

#endif // LEAGUE_H
