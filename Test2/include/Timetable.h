#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>

class Timetable
{
    public:
        Timetable();
        virtual ~Timetable();

        int getTimetableId() { return timetableId; }
        void setTimetableId(int val) { timetableId = val; }
        int getHomeClub() { return homeClub; }
        void setHomeClub(int val) { homeClub = val; }
        int getAwayClub() { return awayClub; }
        void setAwayClub(int val) { awayClub = val; }
        int getSeasonId() { return seasonId; }
        void setSeasonId(int val) { seasonId = val; }
        int getSpringFall() { return springFall; }
        void setSpringFall(int val) { springFall = val; }
        int getMatchweek() { return matchweek; }
        void setMatchweek(int val) { matchweek = val; }
        std::string getResult() { return result; }
        void setResult(std::string val) { result = val; }
        int getGoalsScored() { return goalsScored; }
        void setGoalsScored(int val) { goalsScored = val; }
        int getGoalsLost() { return goalsLost; }
        void setGoalsLost(int val) { goalsLost = val; }

    protected:

    private:
        int timetableId;
        int homeClub;
        int awayClub;
        int seasonId;
        int matchweek;
        int springFall; //0 - spring, 1 - fall
        std::string result;
        int goalsScored;
        int goalsLost;
};

#endif // TIMETABLE_H
