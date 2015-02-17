#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

// Constructors

Member::Member (int imID, int x, int y, Direction direc)
:GraphObject(imID, x, y, direc){}

Actor::Actor (int imID, int x, int y, Direction direc)
:Member (imID, x, y, direc){}

Item::Item (int imID, int x, int y, Direction direc)
:Member (imID, x, y, direc){}

Player::Player (int imID, int x, int y, Direction direc)
:Actor (imID, x, y, direc)
{
    imID = IID_PLAYER;
    m_ammo = 20;
    m_HP = 20;
    setVisible(true);
}


// Methods

StudentWorld* Member::getWorld()
{
    StudentWorld *p;
    return p;
}

void Player::doSomething()
{
    int ch;
    if (getWorld()->getKey(ch)) {
        // user hit a key this tick!
        switch (ch)
        {
            case KEY_PRESS_UP:
                moveTo(getX(), getY()+1);
                setDirection(up);
                break;
            case KEY_PRESS_DOWN:
                moveTo(getX(), getY()-1);
                setDirection(down);
                break;
            case KEY_PRESS_LEFT:
                moveTo(getX()-1, getY());
                setDirection(left);
                break;
            case KEY_PRESS_RIGHT:
                moveTo(getX()+1, getY());
                setDirection(right);
                break;
            case KEY_PRESS_SPACE:
                break;
            case KEY_PRESS_ESCAPE:
                break;
            default:
                break;
        }
    }
}

int Player::getAmmo() const
{
    return m_ammo;
}

int Player::getHP() const
{
    return m_HP;
}

int Item::getHP() const
{
    return m_HP;
}



