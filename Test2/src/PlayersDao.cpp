#include "PlayersDao.h"

PlayersDao::PlayersDao()
{
    //ctor
}

PlayersDao::~PlayersDao()
{
    //dtor
}

std::vector<Player> PlayersDao::getPlayers(){
    std::vector<Player> players;

    exit = sqlite3_open("test.db", &DB);
    q[sizeof q - 1] = '\0';
    snprintf(
        q,
        sizeof q - 1,
        "SELECT * from PLAYERS;"
    );

    sqlite3_prepare(DB, q, sizeof q, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                playerFromStatement(stmt);
                players.push_back(*playerTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return players;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return players;
}

Player PlayersDao::getPlayer(int playerId){
    std::vector<Player> players;
    Player player;

    exit = sqlite3_open("test.db", &DB);
    std::string sql = "SELECT * from PLAYERS WHERE PLAYER_ID = " + playerId + std::string(";");

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                playerFromStatement(stmt);
                players.push_back(*playerTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return player;;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    if(players.size() > 0){
        return players.at(0);
    }
}

int PlayersDao::savePlayer(Player playerVar){
 int playerId;
 std::string sql =  "INSERT INTO PLAYERS(NAME, POSITION, MATCHSQUAD, AGE, NETT_WORTH, HANDLING, DIVING, KICKING, REFLEXES, TACKLING, HEADING, "
                      "MARKING, INTERCEPTING, VISION, CROSSING, SHORT_PASS, LONG_PASS, FREE_KICKS, POSITIONING, FINISHING, POWER, VOLLEYS, LONG_SHOTS, TRAINING_TYPE, OVERALL_SCORE) "
                      "VALUES (\'" + playerVar.getName() + "\', \'" + playerVar.getPosition() + "\', " + std::to_string(playerVar.getMatchsquad())+
                      ", "+std::to_string(playerVar.getAge())+", "+std::to_string(playerVar.getNettWorth())+", "+std::to_string(playerVar.getHandling())+
                      ", "+std::to_string(playerVar.getDiving())+", "+std::to_string(playerVar.getKicking())+", "+std::to_string(playerVar.getReflexes())+
                      ", "+std::to_string(playerVar.getTackling())+", "+std::to_string(playerVar.getHeading())+", "+std::to_string(playerVar.getMarking())+
                      ", "+std::to_string(playerVar.getIntercepting())+", "+std::to_string(playerVar.getVision())+", "+std::to_string(playerVar.getCrossing())+
                      ", "+std::to_string(playerVar.getShortPasses())+", "+std::to_string(playerVar.getLongPasses())+", "+std::to_string(playerVar.getFreeKicks())+
                      ", "+std::to_string(playerVar.getPositioning())+", "+std::to_string(playerVar.getFinishing())+", "+std::to_string(playerVar.getPower())+
                      ", "+std::to_string(playerVar.getVolleys())+", "+std::to_string(playerVar.getLongShots())+", \'"+playerVar.getTrainingType()+"\', " + std::to_string(playerVar.getOverallScore()) + ");";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    }

    playerId = sqlite3_last_insert_rowid(DB);
    sqlite3_close(DB);

    return playerId;
};

void PlayersDao::updatePlayer(Player playerVar){
 std::string sql =  "UPDATE PLAYERS SET "
                    "NAME = \'" + playerVar.getName() + "\', "
                    "POSITION = \'" + playerVar.getPosition() + "\', "
                    "AGE = " + std::to_string(playerVar.getAge()) + ", "
                    "CLUB_ID = " + std::to_string(playerVar.getClubId()) + ", "
                    "MATCHSQUAD = " + std::to_string(playerVar.getMatchsquad()) + ", "
                    "NETT_WORTH = " + std::to_string(playerVar.getNettWorth()) + ", "
                    "HANDLING = " + std::to_string(playerVar.getHandling()) + ", "
                    "DIVING = " + std::to_string(playerVar.getDiving()) + ", "
                    "KICKING = "+std::to_string(playerVar.getKicking())+", "
                    "REFLEXES = "+std::to_string(playerVar.getReflexes())+", "
                    "TACKLING = "+std::to_string(playerVar.getTackling())+", "
                    "HEADING = "+std::to_string(playerVar.getHeading())+", "
                    "MARKING = "+std::to_string(playerVar.getMarking())+", "
                    "INTERCEPTING = "+std::to_string(playerVar.getIntercepting())+", "
                    "VISION = "+std::to_string(playerVar.getVision())+", "
                    "CROSSING = "+std::to_string(playerVar.getCrossing())+", "
                    "SHORT_PASS = "+std::to_string(playerVar.getShortPasses())+", "
                    "LONG_PASS = "+std::to_string(playerVar.getLongPasses())+", "
                    "FREE_KICKS = "+std::to_string(playerVar.getFreeKicks())+", "
                    "POSITIONING = "+std::to_string(playerVar.getPositioning())+", "
                    "FINISHING = "+std::to_string(playerVar.getFinishing())+", "
                    "POWER = "+std::to_string(playerVar.getPower())+", "
                    "VOLLEYS = "+std::to_string(playerVar.getVolleys())+", "
                    "TRAINING_TYPE = \'"+playerVar.getTrainingType()+"\', "
                    "OVERALL_SCORE = "+std::to_string(playerVar.getOverallScore())+", "
                    "LONG_SHOTS = "+std::to_string(playerVar.getLongShots())+" "
                    "WHERE PLAYER_ID = "+std::to_string(playerVar.getPlayerId())+";";

    exit = sqlite3_open("test.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        throw DBException();
    } else
    sqlite3_close(DB);
};

std::vector<Player> PlayersDao::getPlayersForClub(int clubIdQuery ){
    std::vector<Player> players;

    exit = sqlite3_open("test.db", &DB);
    std::string sql;

    if(clubIdQuery == 0){
            sql = "SELECT * FROM PLAYERS WHERE CLUB_ID is NULL OR CLUB_ID = 0;";

    } else {
        sql = "SELECT * FROM PLAYERS WHERE CLUB_ID = " + std::to_string(clubIdQuery) + ";";
    }

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                playerFromStatement(stmt);

                players.push_back(*playerTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return players;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return players;
}

std::vector<Player> PlayersDao::getPlayersForPlayersClub(){
    std::vector<Player> players;

    exit = sqlite3_open("test.db", &DB);
    std::string sql = "SELECT * FROM PLAYERS WHERE PLAYER_CLUB = 1;";

    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                playerFromStatement(stmt);
                players.push_back(*playerTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return players;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return players;
}

std::vector<Player> PlayersDao::getPlayersForPosition(std::string positionVar){
    std::vector<Player> players;
    exit = sqlite3_open("test.db", &DB);
    std::string sql;

    if(positionVar.empty() || positionVar == ""){
        return players;
    } else {
        sql = "SELECT * FROM PLAYERS WHERE POSITION LIKE \'" + positionVar + "\';";
    }
    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL);

    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                playerFromStatement(stmt);
                players.push_back(*playerTmp);

                row++;
                break;
            case SQLITE_DONE:
                done = true;
                break;
            default:
                return players;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return players;
};

void PlayersDao::playerFromStatement(sqlite3_stmt* stmt){
    playerTmp = new Player();
    id = sqlite3_column_text(stmt, 0);
    name = sqlite3_column_text(stmt, 1);
    position  = sqlite3_column_text(stmt, 2);
    clubId  = sqlite3_column_text(stmt, 3);
    matchsquad  = sqlite3_column_text(stmt, 4);
    age  = sqlite3_column_text(stmt, 5);
    nettWorth  = sqlite3_column_text(stmt, 6);
    handling  = sqlite3_column_text(stmt, 7);
    diving  = sqlite3_column_text(stmt, 8);
    kicking  = sqlite3_column_text(stmt, 9);
    reflexes  = sqlite3_column_text(stmt, 10);
    tackling  = sqlite3_column_text(stmt, 11);
    heading  = sqlite3_column_text(stmt, 12);
    marking  = sqlite3_column_text(stmt, 13);
    intercepting  = sqlite3_column_text(stmt, 14);
    vision  = sqlite3_column_text(stmt, 15);
    crossing  = sqlite3_column_text(stmt, 16);
    shortPasses  = sqlite3_column_text(stmt, 17);
    longPasses  = sqlite3_column_text(stmt, 18);
    freeKicks  = sqlite3_column_text(stmt, 19);
    positioning  = sqlite3_column_text(stmt, 20);
    finishing  = sqlite3_column_text(stmt, 21);
    power  = sqlite3_column_text(stmt, 22);
    volleys  = sqlite3_column_text(stmt, 23);
    longShots  = sqlite3_column_text(stmt, 24);
    trainingType  = sqlite3_column_text(stmt, 25);
    overallScore  = sqlite3_column_text(stmt, 26);

    idString = std::string(reinterpret_cast<const char*>(id));
    nameString = std::string(reinterpret_cast<const char*>(name));
    positionString = std::string(reinterpret_cast<const char*>(position));
    if(clubId != NULL){
        clubIdString = std::string(reinterpret_cast<const char*>(clubId));
    }
    matchsquadString = std::string(reinterpret_cast<const char*>(matchsquad));
    ageString = std::string(reinterpret_cast<const char*>(age));
    nettWorthString = std::string(reinterpret_cast<const char*>(nettWorth));
    handlingString = std::string(reinterpret_cast<const char*>(handling));
    divingString = std::string(reinterpret_cast<const char*>(diving));
    kickingString = std::string(reinterpret_cast<const char*>(kicking));
    reflexesString = std::string(reinterpret_cast<const char*>(reflexes));
    tacklingString = std::string(reinterpret_cast<const char*>(tackling));
    headingString = std::string(reinterpret_cast<const char*>(heading));
    markingString = std::string(reinterpret_cast<const char*>(marking));
    interceptingString = std::string(reinterpret_cast<const char*>(intercepting));
    visionString = std::string(reinterpret_cast<const char*>(vision));
    crossingString = std::string(reinterpret_cast<const char*>(crossing));
    shortPassesString = std::string(reinterpret_cast<const char*>(shortPasses));
    longPassesString = std::string(reinterpret_cast<const char*>(longPasses));
    freeKicksString = std::string(reinterpret_cast<const char*>(freeKicks));
    positioningString = std::string(reinterpret_cast<const char*>(positioning));
    finishingString = std::string(reinterpret_cast<const char*>(finishing));
    powerString = std::string(reinterpret_cast<const char*>(power));
    volleysString = std::string(reinterpret_cast<const char*>(volleys));
    longShotsString = std::string(reinterpret_cast<const char*>(longShots));
    trainingTypeString = std::string(reinterpret_cast<const char*>(trainingType));
    overallScoreString = std::string(reinterpret_cast<const char*>(overallScore));

    playerTmp->setPlayerId(std::stoi(idString));
    playerTmp->setName(nameString);
    playerTmp->setPosition(positionString);
    if(clubId != NULL){
        playerTmp->setClubId(std::stoi(clubIdString));
    }
    playerTmp->setMatchsquad(std::stoi(matchsquadString));
    playerTmp->setAge(std::stoi(ageString));
    playerTmp->setNettWorth(std::stoi(nettWorthString));
    playerTmp->setHandling(std::stoi(handlingString));
    playerTmp->setDiving(std::stoi(divingString));
    playerTmp->setKicking(std::stoi(kickingString));
    playerTmp->setReflexes(std::stoi(reflexesString));
    playerTmp->setTackling(std::stoi(tacklingString));
    playerTmp->setHeading(std::stoi(headingString));
    playerTmp->setMarking(std::stoi(markingString));
    playerTmp->setIntercepting(std::stoi(interceptingString));
    playerTmp->setVision(std::stoi(visionString));
    playerTmp->setCrossing(std::stoi(crossingString));
    playerTmp->setShortPasses(std::stoi(shortPassesString));
    playerTmp->setLongPasses(std::stoi(longPassesString));
    playerTmp->setFreeKicks(std::stoi(freeKicksString));
    playerTmp->setPositioning(std::stoi(positioningString));
    playerTmp->setFinishing(std::stoi(finishingString));
    playerTmp->setPower(std::stoi(powerString));
    playerTmp->setVolleys(std::stoi(volleysString));
    playerTmp->setLongShots(std::stoi(longShotsString));
    playerTmp->setTrainingType(trainingTypeString);
    playerTmp->setOverallScore(std::stoi(overallScoreString));
}
