#ifndef TIMETABLEVIEW_H
#define TIMETABLEVIEW_H

#include<iostream>
#include "Timetable.h"
#include "Club.h"
#include "ClubsDao.h"
#include <vector>
#include <string>

class TimetableView
{
    public:
        TimetableView();
        virtual ~TimetableView();

        void displayTimetableList(std::vector<Timetable> timetables);
        void displayTimetable(Timetable timetable);

    protected:

    private:
        ClubsDao* clubsDao;
};

#endif // TIMETABLEVIEW_H
