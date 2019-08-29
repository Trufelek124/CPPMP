#ifndef TIMETABLEVIEW_H
#define TIMETABLEVIEW_H

#include<iostream>
#include "Timetable.h"
#include <vector>

class TimetableView
{
    public:
        TimetableView();
        virtual ~TimetableView();

        void displayTimetableList(std::vector<Timetable> timetables);
        void displayTimetable(Timetable timetable);

    protected:

    private:
};

#endif // TIMETABLEVIEW_H
