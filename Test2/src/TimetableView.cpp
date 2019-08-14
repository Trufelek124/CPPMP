#include "TimetableView.h"

TimetableView::TimetableView()
{
    //ctor
}

TimetableView::~TimetableView()
{
    //dtor
}

void TimetableView::displayTimetableList(std::vector<Timetable> timetables){

    Timetable timetable;
    for(int i = 0; i < timetables.size(); i++){
        timetable = timetables.at(i);
        std::cout << "Matchweek: " << timetable.getMatchweek() << ", home: " << timetable.getHomeClub() << ", away: " << timetable.getAwayClub() << "  " << ((timetable.getSpringFall() == 0) ? "Spring" : "Fall") << std::endl;
    };
};
