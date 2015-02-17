#ifndef ACTOR_H_
#define ACTOR_H_

#include "StudentWorld.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Member: public GraphObject
{
public:
    Member(int imID, int x, int y, Direction direc = none);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
private:
};

class Actor: public Member
{
public:
    Actor (int imID, int x, int y, Direction direc = none);
    virtual void doSomething() = 0;
    int getHP() const;
    int getAmmo() const;
private:
    int m_HP;
    int m_ammo;
    
};
// This class can shoot, move, and die

class Item: public Member
{
public:
    Item (int imID, int x, int y, Direction direc = none);
    virtual void doSomething() = 0;
    virtual int getHP() const;
private:
    int m_HP;
};
// This class can die, hold attributes

class Wall: public Item
{
public:
    Wall (int imID, int x, int y, Direction direc = none);
private:
};

class Player: public Actor
{
public:
    Player (int imID, int x, int y, Direction direc = right);
    virtual void doSomething();
    virtual int getHP() const;
    virtual int getAmmo() const;
private:
    int m_HP;
    int m_ammo;
};

class Robot: public Actor
{
    ;
};

class SnarlBot: public Robot
{
    ;
};

class HorizontalSnarlBot: public SnarlBot
{
    ;
};

class VerticalSnarlBot: public SnarlBot
{
    ;
};

class KleptoBot: public Robot
{
    ;
};

class RegularKleptoBot: public KleptoBot
{
    ;
};

class AngryKletoBot: public KleptoBot
{
    ;
};

class Factory: public GraphObject
{
    ;
};

class AngryKletoBotFactory: public Factory
{
    ;
};

class RegularKleptoBotFactory: public Factory
{
    ;
};

class Bullet: public Item
{
    ;
};

class Exit: public Item
{
    ;
};

class Boulder: public Item
{
    ;
};

class Hole: public Item
{
    ;
};

class Jewel: public Item
{
    ;
};

class Goodie: public Item
{
    ;
};

class RestoreHealthGoodie: public Goodie
{
    ;
};

class ExtraLifeGoodie: public Goodie
{
    ;
};

class AmmoGoodie: public Goodie
{
    ;
};

#endif // ACTOR_H_






