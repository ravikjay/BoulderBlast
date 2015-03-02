#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
using namespace std;

class Member;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        m_levelFinish = false;
        jewelCount = 0;
        m_bonus = 1000;
	}
    
    Member* findMember (int x, int y);
    Member* findSpecificMember (int x, int y, string ID);
    Member* findPlayer ();
    Member* isPlayerInCol(int y);
    Member* isPlayerInRow(int x);
    void addToList (Member* mp);
    void setDisplayText();
    int getBonus();
    void changeBonus(int bonusAddition);
    string formatDisplay(int score, int level, int lives, int health, int ammo, unsigned int bonus);
    double playerHP(Member* mp);
    int playerAmmo(Member* mp);
    void setLevelFinished();
    bool isLevelDone();
    void giveBonus();
    bool anyJewels() const;
    bool decJewels();
    bool existsClearShotToPlayer(int x, int y, int dirX, int dirY);
    bool isObstacle (Member* mp);
    void addToListBack (Member* mp);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld ();

private:
    bool m_levelFinish;
    int jewelCount;
    int m_bonus;
    list<Member*> MemberList;
};

#endif // STUDENTWORLD_H_
