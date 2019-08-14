#ifndef TIMETABLE_H
#define TIMETABLE_H

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

    protected:

    private:
        int timetableId;
        int homeClub;
        int awayClub;
        int seasonId;
        int matchweek;
        int springFall; //0 - spring, 1 - fall
};

#endif // TIMETABLE_H