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
    std::cout << "MATCHWEEK | HOME | AWAY |          RESULT          | H_GOALS | A_GOALS" << std::endl;
    std::cout << "______________________________________________________________________" << std::endl;
    for(int i = 0; i < timetables.size(); i++){
        timetable = timetables.at(i);
        std:: string result = timetable.getResult();
        int numberOfWhitespacesResult = 25 - result.length();
        int numberOPfWhitespacesMatchweek;
        if(timetable.getMatchweek() < 10){
            numberOPfWhitespacesMatchweek = 9;
        } else {
            numberOPfWhitespacesMatchweek = 8;
        }

        std::cout << timetable.getMatchweek();
        for(int j = 0; j < numberOPfWhitespacesMatchweek; j++){
            std::cout << " ";
        }
        std::cout << "| " << timetable.getHomeClub() << "    | " << timetable.getAwayClub() << "    | " << result;
        for(int j = 0; j < numberOfWhitespacesResult; j++){
            std::cout << " ";
        }
        std::cout << "| " << timetable.getHomeTeamGoals() << "       | " << timetable.getAwayTeamGoals() << std::endl;
    };
};


void TimetableView::displayTimetable(Timetable timetable){
    std::cout << timetable.getTimetableId() << " | " << timetable.getMatchweek() << "         | " << timetable.getHomeClub() << "    | " << timetable.getAwayClub() << "    | " << timetable.getResult() << "    | " << timetable.getHomeTeamGoals() << "    | " << timetable.getAwayTeamGoals() << std::endl;
};
