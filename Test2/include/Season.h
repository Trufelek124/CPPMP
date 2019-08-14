#ifndef SEASON_H
#define SEASON_H

#include<vector>
#include"Timetable.h"

class Season
{
    public:
        Season();
        virtual ~Season();

        int getSeasonId() { return seasonId; }
        void setSeasonId(int val) { seasonId = val; }
        int getNumber() { return number; }
        void setNumber(int val) { number = val; }
        std::vector<Timetable> getTimetables() { return timetables; }
        void setTimetables(std::vector<Timetable> val) { timetables = val; }

    protected:

    private:
        int seasonId;
        int number;
        std::vector<Timetable> timetables;
};

#endif // SEASON_H
