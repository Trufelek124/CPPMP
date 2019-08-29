#include "TimetableHelper.h"

TimetableHelper::TimetableHelper()
{
    timetableDao = new TimetableDao();
    timetableViewVar = new TimetableView();
}

TimetableHelper::~TimetableHelper()
{
    //dtor
}

/**
Very simple method to create timetable - it only works for even number of teams.
It is VERY suboptimal - it depends on pure luck, by shuffling table.
This part is the only thing limiting the number of teams - if it's less than 10 algorithm works reasonably fast and reliably.
*/
std::vector<Timetable> TimetableHelper::createTimetableForSeason(int seasonId, std::vector<Club> clubs){
    std::vector<Timetable> timetables;
    std::vector<Timetable> timetablesFall;
    int clubsSize = clubs.size();
    int halfClubsSize = clubsSize/2;

    std::vector<std::string> simplifiedTimetable;
    std::string matchStringTmp;
    std::string homeClubStringTmp;
    std::string awayClubStringTmp;

    int homeClubTmp;
    int awayClubTmp;

    std::vector<int> clubIds; //vektor idków
    for(int i = 0; i < clubsSize; i++){
        clubIds.push_back(clubs.at(i).getClubId());
    }

    for(int x = 0; x < (clubsSize-1); x++){ //tylko dla po³owy sezonu - druga jest taka sama tylko odwrócona
        bool done = false;
        std::vector<int> isConflict;

        while(!done){
            //randomizacja tabeli idków
            std::srand ( unsigned ( std::time(0) ) );
            std::random_shuffle(clubIds.begin(), clubIds.end());

            if(!simplifiedTimetable.empty()){
                isConflict.clear();
                //dopiero tutaj sprawdzamy czy s¹ takie
                for(int i =0; i < halfClubsSize; i++){
                    homeClubTmp = clubIds.at(i);
                    awayClubTmp = clubIds.at(i+halfClubsSize);

                    if(homeClubTmp < 10){
                        homeClubStringTmp = "0" + std::to_string(homeClubTmp);
                    } else {
                        homeClubStringTmp = std::to_string(homeClubTmp);
                    }

                    if(awayClubTmp < 10){
                        awayClubStringTmp = "0" + std::to_string(awayClubTmp);
                    } else {
                        awayClubStringTmp = std::to_string(awayClubTmp);
                    }

                    matchStringTmp = homeClubStringTmp + awayClubStringTmp;
                    //tutaj mamy stringa dla ka¿dego z nowych meczów - musimy ka¿dy sprawdziæ i jak jakikolwiek bêdzie
                    //siê powtarza³, to ca³oœæ robimy jeszcze raz. Mo¿na daæ while zmienna - i jak bêdzie powtórzone to
                    //dajemy zmienn¹ na false - normalnie od pocz¹tku jest na true
                    if(vectorContains(matchStringTmp, simplifiedTimetable)){
                        isConflict.push_back(1);
                    } else {
                        isConflict.push_back(0);
                    }

                }

                done = true;
                for(int z = 0; z < isConflict.size(); z++){
                    if(isConflict.at(z) == 1){
                        done = false;
                    }
                }
            } else {
                done = true;
            }
        }

        //tworzenie timetable
        for(int i =0; i < halfClubsSize; i++){
            Timetable* timetableVar = new Timetable();
            timetableVar->setHomeClub(clubIds.at(i));
            timetableVar->setAwayClub(clubIds.at(i+halfClubsSize));
            timetableVar->setSeasonId(seasonId);
            timetableVar->setMatchweek(x+1);
            timetableVar->setSpringFall(0);
            timetableVar->setResult(std::string("NOT PLAYED"));
            timetableVar->setHomeTeamGoals(0);
            timetableVar->setAwayTeamGoals(0);
            timetables.push_back(*timetableVar);

            //tworzenie stringa do sprawdzania czy mecze siê nie powtarzaj¹
            if(timetableVar->getHomeClub() < 10){
                homeClubStringTmp = "0" + std::to_string(timetableVar->getHomeClub());
            } else {
                homeClubStringTmp = std::to_string(timetableVar->getHomeClub());
            }

            if(timetableVar->getAwayClub() < 10){
                awayClubStringTmp = "0" + std::to_string(timetableVar->getAwayClub());
            } else {
                awayClubStringTmp = std::to_string(timetableVar->getAwayClub());
            }

            matchStringTmp = homeClubStringTmp + awayClubStringTmp;
            simplifiedTimetable.push_back(matchStringTmp);
        }
    }
    for(int i = 0; i < timetables.size(); i++){
        Timetable timetableTmp = timetables.at(i);
        Timetable* timetableFall = new Timetable();
        timetableFall->setSeasonId(timetableTmp.getSeasonId());
        timetableFall->setSpringFall(1);
        timetableFall->setHomeClub(timetableTmp.getAwayClub());
        timetableFall->setAwayClub(timetableTmp.getHomeClub());
        timetableFall->setMatchweek(timetableTmp.getMatchweek()+clubsSize-1);
        timetableFall->setResult(std::string("NOT PLAYED"));
        timetableFall->setHomeTeamGoals(0);
        timetableFall->setAwayTeamGoals(0);
        timetablesFall.push_back(*timetableFall);
        //timetables.push_back(*timetableFall);
    }
    timetables.insert(timetables.end(), timetablesFall.begin(), timetablesFall.end());
    //timetableViewVar->displayTimetableList(timetables);
    timetableDao->saveTimetables(timetables);
    return timetables;
};

bool TimetableHelper::vectorContains(std::string val, std::vector<std::string> v){
    if (std::find(v.begin(), v.end(), val) != v.end())
    {
      return true;
    }
    return false;
}
