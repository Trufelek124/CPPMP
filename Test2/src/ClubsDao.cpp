#include "ClubsDao.h"

ClubsDao::ClubsDao()
{
    //ctor
}

ClubsDao::~ClubsDao()
{
    //dtor
}

std::vector<Club> ClubsDao::getClubs(){
    std::vector<Club> clubs;

    exit = sqlite3_open("test.db", &DB);
    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT * FROM CLUBS"
    );

    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                clubTmp = new Club();
                id = sqlite3_column_text(stmt, 0);
                name = sqlite3_column_text(stmt, 1);
                budget  = sqlite3_column_text(stmt, 2);
                points  = sqlite3_column_text(stmt, 3);
                position  = sqlite3_column_text(stmt, 4);
                leagueId  = sqlite3_column_text(stmt, 5);
                playerClub  = sqlite3_column_text(stmt, 6);
                goalsScored  = sqlite3_column_text(stmt, 7);
                goalsLost  = sqlite3_column_text(stmt, 8);

                idString = std::string(reinterpret_cast<const char*>(id));
                nameString = std::string(reinterpret_cast<const char*>(name));
                budgetString = std::string(reinterpret_cast<const char*>(budget));
                pointsString = std::string(reinterpret_cast<const char*>(points));
                positionString = std::string(reinterpret_cast<const char*>(position));
                leagueIdString = std::string(reinterpret_cast<const char*>(leagueId));
                playerClubString = std::string(reinterpret_cast<const char*>(playerClub));
                goalsScoredString = std::string(reinterpret_cast<const char*>(goalsScored));
                goalsLostString = std::string(reinterpret_cast<const char*>(goalsLost));

                clubTmp->setClubId(std::stoi(idString));
                clubTmp->setName(nameString);
                clubTmp->setBudget(std::stoi(budgetString));
                clubTmp->setPoints(std::stoi(pointsString));
                clubTmp->setPosition(std::stoi(positionString));
                clubTmp->setLeagueId(std::stoi(leagueIdString));
                clubTmp->setPlayerClub(std::stoi(playerClubString));
                clubTmp->setGoalsScored(std::stoi(goalsScoredString));
                clubTmp->setGoalsLost(std::stoi(goalsLostString));

                clubs.push_back(*clubTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                sqlite3_finalize(stmt);
                sqlite3_close(DB);
                return clubs;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return clubs;
}

int ClubsDao::saveClub(Club clubVar){
    int clubId;
    std::string sql =  "INSERT INTO CLUBS(NAME, BUDGET, POINTS, POSITION, LEAGUE_ID, PLAYER_CLUB, GOALS_SCORED, GOALS_LOST) "
                      "VALUES (\'" + clubVar.getName() + "\', "+std::to_string(clubVar.getBudget())+
                      ", "+std::to_string(clubVar.getPoints())+", "+std::to_string(clubVar.getPosition())+", "+std::to_string(clubVar.getLeagueId())+
                      ", "+std::to_string(clubVar.getPlayerClub())+", " + std::to_string(clubVar.getGoalsScored()) + ", " + std::to_string(clubVar.getGoalsLost()) + ");";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error inserting records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    } else
        std::cout << "Records inserted successfully" << std::endl;

    clubId = sqlite3_last_insert_rowid(DB);
    sqlite3_close(DB);
    return clubId;
};

void ClubsDao::updateClub(Club clubVar){
 std::string sql =  "UPDATE CLUBS SET "
                    "NAME = \'" + clubVar.getName() + "\', "
                    "BUDGET = \'" + std::to_string(clubVar.getBudget()) + "\', "
                    "POINTS = " + std::to_string(clubVar.getPoints()) + ", "
                    "POSITION = " + std::to_string(clubVar.getPosition()) + ", "
                    "LEAGUE_ID = " + std::to_string(clubVar.getLeagueId()) +", "
                    "PLAYER_CLUB = " + std::to_string(clubVar.getPlayerClub()) + ", "
                    "GOALS_SCORED = " + std::to_string(clubVar.getGoalsScored()) + ", "
                    "GOALS_LOST = " + std::to_string(clubVar.getGoalsLost()) + " "
                    "WHERE CLUB_ID = " + std::to_string(clubVar.getClubId()) + ";";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error updating records" << std::endl;
        std::cerr << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    } else
        std::cout << "Records updated successfully" << std::endl;
    sqlite3_close(DB);
};


std::vector<Club> ClubsDao::getClubsForLeague(int leagueIdQuery){
    std::vector<Club> clubs;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;

    if(leagueIdQuery == 0){
        sql = "SELECT * FROM CLUBS WHERE LEAGUE_ID is NULL;";
    } else {
        sql = "SELECT * FROM CLUBS WHERE LEAGUE_ID = " + std::to_string(leagueIdQuery) + ";";;
    }

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                clubTmp = new Club();
                id = sqlite3_column_text(stmt, 0);
                name = sqlite3_column_text(stmt, 1);
                budget  = sqlite3_column_text(stmt, 2);
                points  = sqlite3_column_text(stmt, 3);
                position  = sqlite3_column_text(stmt, 4);
                leagueId  = sqlite3_column_text(stmt, 5);
                playerClub  = sqlite3_column_text(stmt, 6);
                goalsScored  = sqlite3_column_text(stmt, 7);
                goalsLost  = sqlite3_column_text(stmt, 8);

                idString = std::string(reinterpret_cast<const char*>(id));
                nameString = std::string(reinterpret_cast<const char*>(name));
                budgetString = std::string(reinterpret_cast<const char*>(budget));
                pointsString = std::string(reinterpret_cast<const char*>(points));
                positionString = std::string(reinterpret_cast<const char*>(position));
                leagueIdString = std::string(reinterpret_cast<const char*>(leagueId));
                playerClubString = std::string(reinterpret_cast<const char*>(playerClub));
                goalsScoredString = std::string(reinterpret_cast<const char*>(goalsScored));
                goalsLostString = std::string(reinterpret_cast<const char*>(goalsLost));

                clubTmp->setClubId(std::stoi(idString));
                clubTmp->setName(nameString);
                clubTmp->setBudget(std::stoi(budgetString));
                clubTmp->setPoints(std::stoi(pointsString));
                clubTmp->setPosition(std::stoi(positionString));
                clubTmp->setLeagueId(std::stoi(leagueIdString));
                clubTmp->setPlayerClub(std::stoi(playerClubString));
                clubTmp->setGoalsScored(std::stoi(goalsScoredString));
                clubTmp->setGoalsLost(std::stoi(goalsLostString));

                clubs.push_back(*clubTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                sqlite3_finalize(stmt);
                sqlite3_close(DB);
                return clubs;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return clubs;
}

Club ClubsDao::getPlayerClub(){
    std::vector<Club> clubs;
    Club playerClubResult;

    exit = sqlite3_open("test.db", &DB);
    std::string sql = "SELECT * FROM CLUBS WHERE PLAYER_CLUB = 1;";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                clubTmp = new Club();
                id = sqlite3_column_text(stmt, 0);
                name = sqlite3_column_text(stmt, 1);
                budget  = sqlite3_column_text(stmt, 2);
                points  = sqlite3_column_text(stmt, 3);
                position  = sqlite3_column_text(stmt, 4);
                leagueId  = sqlite3_column_text(stmt, 5);
                playerClub  = sqlite3_column_text(stmt, 6);
                goalsScored  = sqlite3_column_text(stmt, 7);
                goalsLost  = sqlite3_column_text(stmt, 8);

                idString = std::string(reinterpret_cast<const char*>(id));
                nameString = std::string(reinterpret_cast<const char*>(name));
                budgetString = std::string(reinterpret_cast<const char*>(budget));
                pointsString = std::string(reinterpret_cast<const char*>(points));
                positionString = std::string(reinterpret_cast<const char*>(position));
                leagueIdString = std::string(reinterpret_cast<const char*>(leagueId));
                playerClubString = std::string(reinterpret_cast<const char*>(playerClub));
                goalsScoredString = std::string(reinterpret_cast<const char*>(goalsScored));
                goalsLostString = std::string(reinterpret_cast<const char*>(goalsLost));

                clubTmp->setClubId(std::stoi(idString));
                clubTmp->setName(nameString);
                clubTmp->setBudget(std::stoi(budgetString));
                clubTmp->setPoints(std::stoi(pointsString));
                clubTmp->setPosition(std::stoi(positionString));
                clubTmp->setLeagueId(std::stoi(leagueIdString));
                clubTmp->setPlayerClub(std::stoi(playerClubString));
                clubTmp->setGoalsScored(std::stoi(goalsScoredString));
                clubTmp->setGoalsLost(std::stoi(goalsLostString));

                clubs.push_back(*clubTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                sqlite3_finalize(stmt);
                sqlite3_close(DB);
                return playerClubResult;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if(clubs.size() >= 1){
        playerClubResult = clubs.at(0);
    };
    return playerClubResult;
}

Club ClubsDao::getClub(int clubIdVar){
    std::vector<Club> clubs;
    Club playerClubResult;

    exit = sqlite3_open("test.db", &DB);
    std::string sql = "SELECT * FROM CLUBS WHERE CLUB_ID = " + std::to_string(clubIdVar)+ ";";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                clubTmp = new Club();
                id = sqlite3_column_text(stmt, 0);
                name = sqlite3_column_text(stmt, 1);
                budget  = sqlite3_column_text(stmt, 2);
                points  = sqlite3_column_text(stmt, 3);
                position  = sqlite3_column_text(stmt, 4);
                leagueId  = sqlite3_column_text(stmt, 5);
                playerClub  = sqlite3_column_text(stmt, 6);
                goalsScored  = sqlite3_column_text(stmt, 7);
                goalsLost  = sqlite3_column_text(stmt, 8);

                idString = std::string(reinterpret_cast<const char*>(id));
                nameString = std::string(reinterpret_cast<const char*>(name));
                budgetString = std::string(reinterpret_cast<const char*>(budget));
                pointsString = std::string(reinterpret_cast<const char*>(points));
                positionString = std::string(reinterpret_cast<const char*>(position));
                leagueIdString = std::string(reinterpret_cast<const char*>(leagueId));
                playerClubString = std::string(reinterpret_cast<const char*>(playerClub));
                goalsScoredString = std::string(reinterpret_cast<const char*>(goalsScored));
                goalsLostString = std::string(reinterpret_cast<const char*>(goalsLost));

                clubTmp->setClubId(std::stoi(idString));
                clubTmp->setName(nameString);
                clubTmp->setBudget(std::stoi(budgetString));
                clubTmp->setPoints(std::stoi(pointsString));
                clubTmp->setPosition(std::stoi(positionString));
                clubTmp->setLeagueId(std::stoi(leagueIdString));
                clubTmp->setPlayerClub(std::stoi(playerClubString));
                clubTmp->setGoalsScored(std::stoi(goalsScoredString));
                clubTmp->setGoalsLost(std::stoi(goalsLostString));

                clubs.push_back(*clubTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                sqlite3_finalize(stmt);
                sqlite3_close(DB);
                return playerClubResult;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if(clubs.size() >= 1){
        playerClubResult = clubs.at(0);
    };
    return playerClubResult;
}
