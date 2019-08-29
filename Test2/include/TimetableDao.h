#ifndef TIMETABLEDAO_H
#define TIMETABLEDAO_H

#include"Timetable.h"
#include<vector>
#include <sqlite3.h>
#include <iostream>
#include "TimetableView.h"

class TimetableDao
{
    public:
        TimetableDao();
        virtual ~TimetableDao();

        sqlite3* DB;
        int exit;
        sqlite3_stmt* stmt;
        int row = 0;
        int bytes;
        Timetable* timetableTmp;
        char q[999];

        const unsigned char* id;
        const unsigned char* homeClub;
        const unsigned char* awayClub;
        const unsigned char* matchweek;
        const unsigned char* seasonId;
        const unsigned char* springFall;
        const unsigned char* result;
        const unsigned char* goalsScored;
        const unsigned char* goalsLost;

        std::string idString;
        std::string homeClubString;
        std::string awayClubString;
        std::string matchweekString;
        std::string seasonIdString;
        std::string springFallString;
        std::string resultString;
        std::string goalsScoredString;
        std::string goalsLostString;

        std::vector<Timetable> getTimetables();
        std::vector<Timetable> getTimetablesForSeason(int seasonIdQuery);
        std::vector<Timetable> getTimetablesForClubForSeason(int clubIdQuery, int seasonIdQuery);
        std::vector<Timetable> getTimetablesForMatchweek(int matchweekVar, int seasonIdQuery);
        Timetable getTimetable(int timetableId);
        int saveTimetable(Timetable timetableVar);
        void saveTimetables(std::vector<Timetable> timetablesVar);
        void updateTimetable(Timetable timetableVar);

    protected:

    private:
        TimetableView* timetableViewVar;
};

#endif // TIMETABLEDAO_H
