#ifndef ACTOR_H_
#define ACTOR_H_

#include "StudentWorld.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Member: public GraphObject
{
public:
    Member(int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    int getHP();
    void setHP(int health);
    void initHP(int health);
    bool isDead () const;
    void setDead (bool b);
    virtual bool isBlocked () =0;
    string memberID();
private:
    string m_name;
    int m_HP;
    StudentWorld* stWorld;
    bool m_dead;
};

class Actor: public Member
{
public:
    Actor (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething() = 0;
    virtual int getAmmo() const;
private:
    string m_name;
    int m_ammo;
    
};
// This class can shoot, move, and die

class Item: public Member
{
public:
    Item (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething() = 0;
private:
    string m_name;
};
// This class can die, hold attributes

class Wall: public Item
{
public:
    Wall (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked ();
private:
    string m_name;
};

class Player: public Actor
{
public:
    Player (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual int getHP() const;
    virtual void setHP(int health);
    virtual int getAmmo() const;
    void damage ();
    void setAmmo(int newRounds);
    virtual bool isBlocked ();
    unsigned int getHealthPercentage() const;
private:
    void checkMove (int x, int y, Direction direc);
    void playerFire();
    string m_name;
    int m_HP;
    int m_ammo;
};

class Bullet: public Item
{
public:
    Bullet (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    void bulletCheckTarget();
    void bulletMove();
    string m_name;
};

class Exit: public Item
{
public:
    Exit (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
    bool isVisible();
    // Checks if Exit is visible & makes sure the exit isn't continually revealed
    bool playerPresence();
    // Checks if the Player is currently standing on the exit
private:
    bool m_visibility;
    bool m_playerPresence;
    string m_name;
};

class Boulder: public Item
{
public:
    Boulder (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    void push(int x, int y);
    //virtual void setHP(int health);
    virtual bool isBlocked ();
    void damage();
private:
    string m_name;
    //int m_HP;
};

class Hole: public Item
{
public:
    Hole (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    string m_name;
};


// Robots
class Robot: public Actor
{
public:
    Robot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void robotTryToFire(Member *mp);
    virtual void doSomething();
    virtual bool isBlocked();
    bool isDamageable();
    bool isShootingRobot();
    bool canItMoveThisTick(int aSpecificLevelsTicks);
    void incTickCount();
    void reverseDirection(Direction direc);
    void robotFire();
    void checkMove(int x, int y, Direction direc, Member* mp);
    bool checkY(Member* mp);
    bool checkX(Member* mp);
    bool checkDirection(Direction direc, Member* mp);
    void shootIfPossible (Member* mp);
private:
    int m_tickCount;
    string m_name;
};

class SnarlBot: public Robot
{
public:
    SnarlBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    void damage();
private:
    string m_name;
};

class KleptoBot: public Robot
{
public:
    KleptoBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual void damage();
    void pickUpGoodie(int x, int y);
    bool isGoodieHere (int x, int y);
    void dropGoodie();
    void checkMoveKlepto (int x, int y, Direction direc);
    void resetStepsMoved();
    void incStepsMoved();
    int getStepsMoved();
    void checkAnotherMove(int x, int y, Direction direc);
    void resetDistanceBeforeTurning();
    int getDistanceBeforeTurning();
    Direction getRandomDirection();
    bool ifObstruction(int x, int y, Direction direc);
private:
    string m_stolenGoodie;
    int m_stepsMoved;
    int m_distanceBeforeTurning;
    string m_name;
};

class AngryKleptoBot: public KleptoBot
{
public:
    AngryKleptoBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual void damage();
private:
    string m_name;
};

class Factory: public Item
{
public:
    Factory (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name, bool isAngryFactory);
    virtual void doSomething();
    virtual bool isBlocked();
    bool getIsItAnAngryFactory();
    void setIsItAnAngryFactory(bool set);
private:
    bool m_isAngryFactory;
    string m_name;
};



//Items

class Goodie: public Item
{
public:
    Goodie (int imID, int x, int y, Direction none, StudentWorld* studWorld, string name);
    virtual void doSomething()=0;
    virtual bool isBlocked()=0;
    void goodieFunction(Goodie* goodieItem);
private:
    string m_name;
};

class Jewel: public Goodie
{
public:
    Jewel (int imID, int x, int y, Direction none, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    string m_name;
};

class RestoreHealthGoodie: public Goodie
{
public:
    RestoreHealthGoodie (int imID, int x, int y, Direction none, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    string m_name;
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie (int imID, int x, int y, Direction none, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    string m_name;
};

class AmmoGoodie: public Goodie
{
public:
    AmmoGoodie (int imID, int x, int y, Direction none, StudentWorld* studWorld, string name);
    virtual void doSomething();
    virtual bool isBlocked();
private:
    string m_name;
};

#endif // ACTOR_H_






