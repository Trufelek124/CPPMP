#ifndef TIMETABLEHELPER_H
#define TIMETABLEHELPER_H

#include "Club.h"
#include <vector>
#include <stdlib.h>
#include <ctime>
#include "Timetable.h"
#include <algorithm>
#include <cstdlib>
#include "TimetableDao.h"
#include "TimetableView.h"

class TimetableHelper
{
    public:
        TimetableHelper();
        virtual ~TimetableHelper();

        std::vector<Timetable> createTimetableForSeason(int seasonId, std::vector<Club> clubs);
        bool vectorContains(std::string val, std::vector<std::string> v);

    protected:

    private:
        TimetableDao* timetableDao;
        TimetableView* timetableViewVar;
};

#endif // TIMETABLEHELPER_H
