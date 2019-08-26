#include "TimetableDao.h"

TimetableDao::TimetableDao()
{
    //ctor
}

TimetableDao::~TimetableDao()
{
    //dtor
}

std::vector<Timetable> TimetableDao::getTimetables(){
    std::vector<Timetable> timetables;

    exit = sqlite3_open("test.db", &DB);
    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT * from Timetables"
    );

    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                timetableTmp = new Timetable();
                id = sqlite3_column_text(stmt, 0);
                homeClub = sqlite3_column_text(stmt, 1);
                awayClub = sqlite3_column_text(stmt, 2);
                matchweek = sqlite3_column_text(stmt, 3);
                seasonId = sqlite3_column_text(stmt, 4);
                springFall = sqlite3_column_text(stmt, 5);
                result = sqlite3_column_text(stmt, 6);

                idString = std::string(reinterpret_cast<const char*>(id));
                homeClubString = std::string(reinterpret_cast<const char*>(homeClub));
                awayClubString = std::string(reinterpret_cast<const char*>(awayClub));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                springFallString = std::string(reinterpret_cast<const char*>(springFall));
                resultString = std::string(reinterpret_cast<const char*>(result));

                timetableTmp->setSeasonId(std::stoi(idString));
                timetableTmp->setHomeClub(std::stoi(homeClubString));
                timetableTmp->setAwayClub(std::stoi(awayClubString));
                timetableTmp->setMatchweek(std::stoi(matchweekString));
                timetableTmp->setSeasonId(std::stoi(seasonIdString));
                timetableTmp->setSpringFall(std::stoi(springFallString));
                timetableTmp->setResult(resultString);

                timetables.push_back(*timetableTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return timetables;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return timetables;
}

int TimetableDao::saveTimetable(Timetable timetableVar){
 int timetableId;
 std::string sql =  "INSERT INTO TIMETABLES(HOME_CLUB, AWAY_CLUB, MATCHWEEK, SEASON_ID, SPRING_FALL, RESULT) "
                      "VALUES ("+std::to_string(timetableVar.getHomeClub())+", "+std::to_string(timetableVar.getAwayClub())+", "+std::to_string(timetableVar.getMatchweek())+
                      ", "+std::to_string(timetableVar.getSeasonId())+", "+std::to_string(timetableVar.getSpringFall())+", \'"+timetableVar.getResult()+"\');";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error inserting records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    }

    timetableId = sqlite3_last_insert_rowid(DB);
    sqlite3_close(DB);

    return timetableId;
};

void TimetableDao::updateTimetable(Timetable timetableVar){
 std::string sql =  "UPDATE TIMETABLES SET "
                    "HOME_CLUB = \'" + std::to_string(timetableVar.getHomeClub()) + "\', "
                    "AWAY_CLUB = \'" + std::to_string(timetableVar.getAwayClub()) + "\', "
                    "MATCHWEEK = " + std::to_string(timetableVar.getMatchweek()) + ", "
                    "SEASON_ID = " + std::to_string(timetableVar.getSeasonId()) + ", "
                    "SPRING_FALL = " + std::to_string(timetableVar.getSpringFall()) +", "
                    "RESULT = " + timetableVar.getResult() +" "
                    "WHERE TIMETABLE_ID = "+std::to_string(timetableVar.getTimetableId())+";";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error updating records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    }
    sqlite3_close(DB);
};

std::vector<Timetable> TimetableDao::getTimetablesForSeason(int seasonIdQuery){
    std::vector<Timetable> timetables;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;

    if(seasonIdQuery == 0){
        sql = "SELECT * from TIMETABLE WHERE SEASON_ID is NULL;";
    } else {
        sql = "SELECT * from TIMETABLE WHERE SEASON_ID = " + std::to_string(seasonIdQuery) + ";";
    }

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                timetableTmp = new Timetable();
                id = sqlite3_column_text(stmt, 0);
                homeClub = sqlite3_column_text(stmt, 1);
                awayClub = sqlite3_column_text(stmt, 2);
                matchweek = sqlite3_column_text(stmt, 3);
                seasonId = sqlite3_column_text(stmt, 4);
                springFall = sqlite3_column_text(stmt, 5);
                result = sqlite3_column_text(stmt, 6);

                idString = std::string(reinterpret_cast<const char*>(id));
                homeClubString = std::string(reinterpret_cast<const char*>(homeClub));
                awayClubString = std::string(reinterpret_cast<const char*>(awayClub));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                springFallString = std::string(reinterpret_cast<const char*>(springFall));
                resultString = std::string(reinterpret_cast<const char*>(result));

                timetableTmp->setSeasonId(std::stoi(idString));
                timetableTmp->setHomeClub(std::stoi(homeClubString));
                timetableTmp->setAwayClub(std::stoi(awayClubString));
                timetableTmp->setMatchweek(std::stoi(matchweekString));
                timetableTmp->setSeasonId(std::stoi(seasonIdString));
                timetableTmp->setSpringFall(std::stoi(springFallString));
                timetableTmp->setResult(resultString);

                timetables.push_back(*timetableTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                fprintf(stderr, "Failed.\n");
                return timetables;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return timetables;
}


std::vector<Timetable> TimetableDao::getTimetablesForClubForSeason(int clubIdQuery, int seasonIdQuery){
    std::vector<Timetable> timetables;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;
    std::string sqlClub;
    std::string sqlSeason;

    if(clubIdQuery == 0){
        sqlClub = "is NULL";
    } else {
        sqlClub = "= " + std::to_string(clubIdQuery);
    }

    if(clubIdQuery == 0){
        sqlSeason = "is NULL";
    } else {
        sqlSeason = "= " + std::to_string(seasonIdQuery);
    }

    sql = "SELECT * from TIMETABLE WHERE (HOME_CLUB " + sqlClub + " OR AWAY_CLUB " + sqlClub + ") AND SEASON_ID " + sqlSeason + ";";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                timetableTmp = new Timetable();
                id = sqlite3_column_text(stmt, 0);
                homeClub = sqlite3_column_text(stmt, 1);
                awayClub = sqlite3_column_text(stmt, 2);
                matchweek = sqlite3_column_text(stmt, 3);
                seasonId = sqlite3_column_text(stmt, 4);
                springFall = sqlite3_column_text(stmt, 5);
                result = sqlite3_column_text(stmt, 6);

                idString = std::string(reinterpret_cast<const char*>(id));
                homeClubString = std::string(reinterpret_cast<const char*>(homeClub));
                awayClubString = std::string(reinterpret_cast<const char*>(awayClub));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                springFallString = std::string(reinterpret_cast<const char*>(springFall));
                resultString = std::string(reinterpret_cast<const char*>(result));

                timetableTmp->setSeasonId(std::stoi(idString));
                timetableTmp->setHomeClub(std::stoi(homeClubString));
                timetableTmp->setAwayClub(std::stoi(awayClubString));
                timetableTmp->setMatchweek(std::stoi(matchweekString));
                timetableTmp->setSeasonId(std::stoi(seasonIdString));
                timetableTmp->setSpringFall(std::stoi(springFallString));
                timetableTmp->setResult(resultString);

                timetables.push_back(*timetableTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return timetables;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return timetables;
}



std::vector<Timetable> TimetableDao::getTimetablesForMatchweek(int matchweekVar, int seasonIdQuery){
    std::vector<Timetable> timetables;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;
    std::string sqlClub;
    std::string sqlSeason;


    sql = "SELECT * from TIMETABLE WHERE MATCHWEEK = " + std::to_string(matchweekVar) + " AND SEASON_ID = " + std::to_string(seasonIdQuery) + ";";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                timetableTmp = new Timetable();
                id = sqlite3_column_text(stmt, 0);
                homeClub = sqlite3_column_text(stmt, 1);
                awayClub = sqlite3_column_text(stmt, 2);
                matchweek = sqlite3_column_text(stmt, 3);
                seasonId = sqlite3_column_text(stmt, 4);
                springFall = sqlite3_column_text(stmt, 5);
                result = sqlite3_column_text(stmt, 6);

                idString = std::string(reinterpret_cast<const char*>(id));
                homeClubString = std::string(reinterpret_cast<const char*>(homeClub));
                awayClubString = std::string(reinterpret_cast<const char*>(awayClub));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                springFallString = std::string(reinterpret_cast<const char*>(springFall));
                resultString = std::string(reinterpret_cast<const char*>(result));

                timetableTmp->setSeasonId(std::stoi(idString));
                timetableTmp->setHomeClub(std::stoi(homeClubString));
                timetableTmp->setAwayClub(std::stoi(awayClubString));
                timetableTmp->setMatchweek(std::stoi(matchweekString));
                timetableTmp->setSeasonId(std::stoi(seasonIdString));
                timetableTmp->setSpringFall(std::stoi(springFallString));
                timetableTmp->setResult(resultString);

                timetables.push_back(*timetableTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return timetables;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return timetables;
}

Timetable TimetableDao::getTimetable(int timetableId){
    std::vector<Timetable> timetables;
    Timetable timetableResult;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;
    std::string sqlClub;
    std::string sqlSeason;


    sql = "SELECT * from TIMETABLE WHERE TIMETABLE_ID = " + std::to_string(timetableId) + ";";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                timetableTmp = new Timetable();
                id = sqlite3_column_text(stmt, 0);
                homeClub = sqlite3_column_text(stmt, 1);
                awayClub = sqlite3_column_text(stmt, 2);
                matchweek = sqlite3_column_text(stmt, 3);
                seasonId = sqlite3_column_text(stmt, 4);
                springFall = sqlite3_column_text(stmt, 5);
                result = sqlite3_column_text(stmt, 6);

                idString = std::string(reinterpret_cast<const char*>(id));
                homeClubString = std::string(reinterpret_cast<const char*>(homeClub));
                awayClubString = std::string(reinterpret_cast<const char*>(awayClub));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                springFallString = std::string(reinterpret_cast<const char*>(springFall));
                resultString = std::string(reinterpret_cast<const char*>(result));

                timetableTmp->setSeasonId(std::stoi(idString));
                timetableTmp->setHomeClub(std::stoi(homeClubString));
                timetableTmp->setAwayClub(std::stoi(awayClubString));
                timetableTmp->setMatchweek(std::stoi(matchweekString));
                timetableTmp->setSeasonId(std::stoi(seasonIdString));
                timetableTmp->setSpringFall(std::stoi(springFallString));
                timetableTmp->setResult(resultString);

                timetables.push_back(*timetableTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return timetableResult;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if(timetables.size() >= 1){
        timetableResult = timetables.at(0);
    };
    return timetableResult;
}


void TimetableDao::saveTimetables(std::vector<Timetable> timetablesVar){

Timetable timetableVar;
exit = sqlite3_open("test.db", &DB);

for(int i = 0; i < timetablesVar.size(); i++){

    timetableVar = timetablesVar.at(i);
    std::string sql =  "INSERT INTO TIMETABLES(HOME_CLUB, AWAY_CLUB, MATCHWEEK, SEASON_ID, SPRING_FALL, RESULT) "
                      "VALUES ("+std::to_string(timetableVar.getHomeClub())+", "+std::to_string(timetableVar.getAwayClub())+", "+std::to_string(timetableVar.getMatchweek())+
                      ", "+std::to_string(timetableVar.getSeasonId())+", "+std::to_string(timetableVar.getSpringFall())+", \'"+timetableVar.getResult()+"\');";
//std::cout << sql << std::endl;
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error inserting records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    }
}
sqlite3_close(DB);
};
