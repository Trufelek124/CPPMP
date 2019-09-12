#include "SeasonsDao.h"

SeasonsDao::SeasonsDao()
{
    //ctor
}

SeasonsDao::~SeasonsDao()
{
    //dtor
}

std::vector<Season> SeasonsDao::getSeasons(){
    std::vector<Season> seasons;

    exit = sqlite3_open("test.db", &DB);
    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT * from Seasons"
    );

    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                seasonTmp = new Season();
                id = sqlite3_column_text(stmt, 0);
                number = sqlite3_column_text(stmt, 1);

                idString = std::string(reinterpret_cast<const char*>(id));
                numberString = std::string(reinterpret_cast<const char*>(number));

                seasonTmp->setSeasonId(std::stoi(idString));
                seasonTmp->setNumber(std::stoi(numberString));

                seasons.push_back(*seasonTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return seasons;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return seasons;
}

int SeasonsDao::saveSeason(Season seasonVar){
    int seasonId;
    std::string sql =  "INSERT INTO SEASONS(NUMBER) "
                       "VALUES (\'" + std::to_string(seasonVar.getNumber()) + ");";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    }

    seasonId = sqlite3_last_insert_rowid(DB);
    sqlite3_close(DB);
    return seasonId;
};

void SeasonsDao::updateSeason(Season seasonVar){
 std::string sql =  "UPDATE SEASONS SET "
                    "NUMBER = \'" + std::to_string(seasonVar.getNumber()) + "\' "
                    "WHERE SEASON_ID = "+std::to_string(seasonVar.getSeasonId())+";";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    }
    sqlite3_close(DB);
};
