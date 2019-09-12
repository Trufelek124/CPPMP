#include "LeaguesDao.h"

LeaguesDao::LeaguesDao()
{
    //ctor
}

LeaguesDao::~LeaguesDao()
{
    //dtor
}

std::vector<League> LeaguesDao::getLeagues(){
    std::vector<League> leagues;

    exit = sqlite3_open("test.db", &DB);
    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT * from Leagues"
    );

    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                leagueTmp = new League();
                id = sqlite3_column_text(stmt, 0);
                seasonId = sqlite3_column_text(stmt, 1);
                matchweek  = sqlite3_column_text(stmt, 2);

                idString = std::string(reinterpret_cast<const char*>(id));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));

                leagueTmp->setLeagueId(std::stoi(idString));
                leagueTmp->setSeason(std::stoi(seasonIdString));
                leagueTmp->setMatchweek(std::stoi(matchweekString));

                leagues.push_back(*leagueTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return leagues;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return leagues;
}

int LeaguesDao::saveLeague(League leagueVar){
    int leagueId;
    std::string sql =  "INSERT INTO LEAGUES(SEASON_ID, MATCHWEEK) "
                       "VALUES (\'" + std::to_string(leagueVar.getSeason()) + "\', "+std::to_string(leagueVar.getMatchweek())+");";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    }

    leagueId = sqlite3_last_insert_rowid(DB);
    sqlite3_close(DB);
    return leagueId;
};

void LeaguesDao::updateLeague(League leagueVar){
 std::string sql =  "UPDATE LEAGUES SET "
                    "SEASON_ID = \'" + std::to_string(leagueVar.getSeason()) + "\', "
                    "MATCHWEEK = " + std::to_string(leagueVar.getMatchweek()) +" "
                    "WHERE LEAGUE_ID = "+std::to_string(leagueVar.getLeagueId())+";";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    }
    sqlite3_close(DB);
};

League LeaguesDao::getLeagueForClub(int leagueIdQuery){
    std::vector<League> leagues;
    League leagueRes;

    exit = sqlite3_open("test.db", &DB);

    std::string sql = "SELECT * FROM LEAGUES WHERE LEAGUE_ID = " + std::to_string(leagueIdQuery) + " ORDER BY LEAGUE_ID DESC;";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                leagueTmp = new League();
                id = sqlite3_column_text(stmt, 0);
                seasonId = sqlite3_column_text(stmt, 1);
                matchweek  = sqlite3_column_text(stmt, 2);

                idString = std::string(reinterpret_cast<const char*>(id));
                seasonIdString = std::string(reinterpret_cast<const char*>(seasonId));
                matchweekString = std::string(reinterpret_cast<const char*>(matchweek));

                leagueTmp->setLeagueId(std::stoi(idString));
                leagueTmp->setSeason(std::stoi(seasonIdString));
                leagueTmp->setMatchweek(std::stoi(matchweekString));

                leagues.push_back(*leagueTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                break;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if(leagues.size() > 1){
        leagueRes = leagues.at(0);
    };
    return leagues.at(0);
}
