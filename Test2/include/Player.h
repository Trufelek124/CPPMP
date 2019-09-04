#ifndef PLAYER_H
#define PLAYER_H

#include<string>

class Player
{
    public:

        Player();
        virtual ~Player();

        int getPlayerId() { return playerId; }
        void setPlayerId(int val) { playerId = val; }
        std::string getName() { return name; }
        void setName(std::string val) { name = val; }
        std::string getPosition() { return position; }
        void setPosition(std::string val) { position = val; }
        int getClubId() { return clubId; }
        void setClubId(int val) { clubId = val; }
        int getAge() { return age; }
        void setAge(int val) { age = val; }
        int getNettWorth() { return nettWorth; }
        void setNettWorth(int val) { nettWorth = val; }
        int getHandling() { return handling; }
        void setHandling(int val) { handling = val; }
        int getDiving() { return diving; }
        void setDiving(int val) { diving = val; }
        int getKicking() { return kicking; }
        void setKicking(int val) { kicking = val; }
        int getReflexes() { return reflexes; }
        void setReflexes(int val) { reflexes = val; }
        int getTackling() { return tackling; }
        void setTackling(int val) { tackling = val; }
        int getHeading() { return heading; }
        void setHeading(int val) { heading = val; }
        int getMarking() { return marking; }
        void setMarking(int val) { marking = val; }
        int getIntercepting() { return intercepting; }
        void setIntercepting(int val) { intercepting = val; }
        int getVision() { return vision; }
        void setVision(int val) { vision = val; }
        int getCrossing() { return crossing; }
        void setCrossing(int val) { crossing = val; }
        int getShortPasses() { return shortPasses; }
        void setShortPasses(int val) { shortPasses = val; }
        int getLongPasses() { return longPasses; }
        void setLongPasses(int val) { longPasses = val; }
        int getFreeKicks() { return freeKicks; }
        void setFreeKicks(int val) { freeKicks = val; }
        int getPositioning() { return positioning; }
        void setPositioning(int val) { positioning = val; }
        int getFinishing() { return finishing; }
        void setFinishing(int val) { finishing = val; }
        int getPower() { return power; }
        void setPower(int val) { power = val; }
        int getVolleys() { return volleys; }
        void setVolleys(int val) { volleys = val; }
        int getLongShots() { return longShots; }
        void setLongShots(int val) { longShots = val; }
        int getMatchsquad(){ return matchsquad; };
        void setMatchsquad(int val){ matchsquad = val; };
        std::string getTrainingType(){ return trainingType; };
        void setTrainingType(std::string val){ trainingType = val; };

    protected:

    private:
        int playerId;
        std::string name;
        std::string position;
        int clubId;
        int matchsquad;
        int age;
        int nettWorth;
        int handling;
        int diving;
        int kicking;
        int reflexes;
        int tackling;
        int heading;
        int marking;
        int intercepting;
        int vision;
        int crossing;
        int shortPasses;
        int longPasses;
        int freeKicks;
        int positioning;
        int finishing;
        int power;
        int volleys;
        int longShots;
        std::string trainingType;
};

#endif // PLAYER_H
