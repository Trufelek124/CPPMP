#include "DatabaseHelper.h"

DatabaseHelper::DatabaseHelper()
{
    //ctor
}

void DatabaseHelper::createTables(){

    //Players table creation
    std::string sql = "CREATE TABLE PLAYERS("
                      "PLAYER_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "NAME         TEXT   NOT NULL, "
                      "POSITION     TEXT   NOT NULL, "
                      "CLUB_ID      INT, "
                      "MATCHSQUAD   INT    NOT NULL, "
                      "AGE          INT    NOT NULL, "
                      "NETT_WORTH   INT    NOT NULL, "
                      "HANDLING     INT    NOT NULL, "
                      "DIVING       INT    NOT NULL, "
                      "KICKING      INT    NOT NULL, "
                      "REFLEXES     INT    NOT NULL, "
                      "TACKLING     INT    NOT NULL, "
                      "HEADING      INT    NOT NULL, "
                      "MARKING      INT    NOT NULL, "
                      "INTERCEPTING INT    NOT NULL, "
                      "VISION       INT    NOT NULL, "
                      "CROSSING     INT    NOT NULL, "
                      "SHORT_PASS   INT    NOT NULL, "
                      "LONG_PASS    INT    NOT NULL, "
                      "FREE_KICKS   INT    NOT NULL, "
                      "POSITIONING  INT    NOT NULL, "
                      "FINISHING    INT    NOT NULL, "
                      "POWER        INT    NOT NULL, "
                      "VOLLEYS      INT    NOT NULL, "
                      "LONG_SHOTS   INT    NOT NULL);"

                      "CREATE TABLE CLUBS("
                      "CLUB_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "NAME       TEXT   NOT NULL, "
                      "BUDGET     INT    NOT NULL, "
                      "POINTS     INT    NOT NULL, "
                      "POSITION   INT    NOT NULL, "
                      "LEAGUE_ID  INT    NOT NULL, "
                      "PLAYER_CLUB INT   NOT NULL);"

                      "CREATE TABLE TIMETABLES("
                      "TIMETABLE_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "HOME_CLUB   INT    NOT NULL, "
                      "AWAY_CLUB   INT    NOT NULL, "
                      "MATCHWEEK   INT    NOT NULL, "
                      "SEASON_ID   INT    NOT NULL, "
                      "SPRING_FALL INT    NOT NULL);"

                      "CREATE TABLE LEAGUES("
                      "LEAGUE_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "SEASON_ID     INT   NOT NULL, "
                      "MATCHWEEK     INT    NOT NULL);"

                      "CREATE TABLE SEASONS("
                      "SEASON_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                      "NUMBER   INT     NOT NULL);";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error create tables" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    } else
        std::cout << "Tables created successfully" << std::endl;
    sqlite3_close(DB);
};


void DatabaseHelper::dropTables(){

    std::string sql = "DROP TABLE PLAYERS;"
                      "DROP TABLE CLUBS;"
                      "DROP TABLE TIMETABLES;"
                      "DROP TABLE LEAGUES;"
                      "DROP TABLE SEASONS;";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error dropping tables" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    } else
        std::cout << "Tables dropped successfully" << std::endl;
    sqlite3_close(DB);
};

void DatabaseHelper::insertInitialData(){

    std::string sql = "INSERT INTO SEASONS(NUMBER) "
                      "VALUES(1);"

                      "INSERT INTO LEAGUES(SEASON_ID, MATCHWEEK) "
                      "VALUES((SELECT MAX(SEASON_ID) FROM SEASONS), 0);"

                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Piast Gliwice\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"
                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Legia Warszawa\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"
                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Lechia Gdansk\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"
                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Gornik Zabrze\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"
                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Wisla Krakow\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"
                      "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB) "
                      "VALUES(\'Lech Poznan\', 10000000, 0, 1, (SELECT MAX(LEAGUE_ID) FROM LEAGUES), 0);"

                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'David De Gea\', \'GK\', 0, 28, 2000000, 85, 90, 87, 94, 10, 10, 10, 10, 10, 10, 10, 10, 10, 88, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Gianluigi Donnarumma\', \'GK\', 0, 20, 2000000, 79, 88, 73, 89, 10, 10, 10, 10, 10, 10, 10, 10, 10, 79, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Jan Oblak\', \'GK\', 0, 26, 2000000, 92, 86, 78, 89, 10, 10, 10, 10, 10, 10, 10, 10, 10, 88, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Kevin Trapp\', \'GK\', 0, 29, 2000000, 74, 79, 77, 83, 10, 10, 10, 10, 10, 10, 10, 10, 10, 82, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Yann Sommer\', \'GK\', 0, 30, 2000000, 84, 79, 81, 85, 10, 10, 10, 10, 10, 10, 10, 10, 10, 80, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Alisson\', \'GK\', 0, 26, 2000000, 82, 84, 87, 89, 10, 10, 10, 10, 10, 10, 10, 10, 10, 87, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Ederson\', \'GK\', 0, 25, 2000000, 80, 85, 90, 87, 10, 10, 10, 10, 10, 10, 10, 10, 10, 82, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Marc Andre Ter Stegen\', \'GK\', 0, 27, 2000000, 85, 87, 88, 90, 10, 10, 10, 10, 10, 10, 10, 10, 10, 85, 10, 10, 10, 10);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Wojciech Szczesny\', \'GK\', 0, 29, 2000000, 89, 89, 79, 90, 10, 10, 10, 10, 10, 10, 10, 10, 10, 88, 10, 10, 10, 10);"

                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Sergio Ramos\', \'CB\', 0, 33, 2000000, 10, 10, 10, 10, 92, 91, 89, 90, 63, 66, 78, 72, 67, 52, 60, 79, 66, 55);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Giorgio Chiellini\', \'CB\', 0, 35, 2000000, 10, 10, 10, 10, 92, 84, 94, 88, 50, 59, 60, 60, 31, 28, 33, 78, 45, 49);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Diego Godin\', \'CB\', 0, 33, 2000000, 10, 10, 10, 10, 89, 92, 90, 88, 52, 55, 79, 70, 51, 48, 42, 67, 47, 43);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Mats Hummels\', \'CB\', 0, 30, 2000000, 10, 10, 10, 10, 91, 87, 89, 92, 79, 64, 82, 85, 53, 56, 55, 71, 60, 51);"
                      "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS) "
                      "VALUES (\'Kalidou Koulibaly\', \'CB\', 0, 28, 2000000, 10, 10, 10, 10, 88, 81, 92, 89, 36, 31, 70, 51, 29, 24, 19, 55, 14, 15);"
                      ;
    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error inserting records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    } else
        std::cout << "Records inserted successfully" << std::endl;
    sqlite3_close(DB);

}
