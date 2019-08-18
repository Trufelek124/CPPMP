#include "PlayersHelper.h"

PlayersHelper::PlayersHelper()
{
    playersDao = new PlayersDao();
    clubsDao = new ClubsDao();
}

PlayersHelper::~PlayersHelper()
{
    //dtor
}

void PlayersHelper::randommizeInitialSquads(){
    std::vector<Player> goalkeepers = playersDao->getPlayersForPosition("GK");
    std::vector<Player> defenders = playersDao->getPlayersForPosition("CB");
    std::vector<Player> midfielders = playersDao->getPlayersForPosition("MF");
    std::vector<Player> strikers = playersDao->getPlayersForPosition("ST");
    std::vector<Club> clubs = clubsDao->getClubs();
    int i = 0;//interator

    //the default formation id 442, so that's how we randomize initial squads

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(goalkeepers.begin(), goalkeepers.end());

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it, i++){
        Player goalkeeper;
        goalkeeper = goalkeepers.at(i);
        int id = it->getClubId();
        goalkeeper.setClubId(id);
        playersDao->updatePlayer(goalkeeper);
    }

    i = 0;

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it){
        for(int j = 0; j < 4; j++, i++){
            Player defender;
            defender = defenders.at(i);
            defender.setClubId(it->getClubId());
            playersDao->updatePlayer(defender);


            Player midfielder;
            midfielder = midfielders.at(i);
            midfielder.setClubId(it->getClubId());
            playersDao->updatePlayer(midfielder);
        }
    }

    i = 0;

    for(std::vector<Club>::iterator it = clubs.begin(); it != clubs.end(); ++it){
        for(int j = 0; j < 2; j++, i++){
            Player striker;
            striker = strikers.at(i);
            striker.setClubId(it->getClubId());
            playersDao->updatePlayer(striker);
        }
    }

    i = 0;

}
