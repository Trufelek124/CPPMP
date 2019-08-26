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
    std::cout << "MATCHWEEK | HOME | AWAY | RESULT" << std::endl;
    std::cout << "________________________________" << std::endl;
    for(int i = 0; i < timetables.size(); i++){
        timetable = timetables.at(i);
        if(timetable.getMatchweek() < 10){
            std::cout << timetable.getMatchweek() << "         | " << timetable.getHomeClub() << "    | " << timetable.getAwayClub() << "    | " << timetable.getResult() << std::endl;
        } else {
            std::cout << timetable.getMatchweek() << "        | " << timetable.getHomeClub() << "    | " << timetable.getAwayClub() << "    | " << timetable.getResult() << std::endl;
        }
    };
};
