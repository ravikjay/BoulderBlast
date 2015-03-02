#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


StudentWorld* Member::getWorld()
{
    return stWorld;
}

// Constructors
    
Member::Member (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:GraphObject(imID, x, y, direc)
{
    m_name = name;
    stWorld = studWorld;
    direc = none;
    m_dead = false;
}

Actor::Actor (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Member (imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
}

Item::Item (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Member (imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
}

Player::Player (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Actor (imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc= right;
    imID = IID_PLAYER;
    m_ammo = 20;
    m_HP = 20;
    setVisible(true);
}

Wall::Wall (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_WALL;
    setVisible(true);
}

Boulder::Boulder (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    //m_HP = 10;
    initHP(10);
    imID = IID_BOULDER;
    setVisible(true);
}

Hole::Hole (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_HOLE;
    setVisible(true);
}

Jewel::Jewel (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Goodie(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_JEWEL;
    setVisible(true);
}

Goodie::Goodie (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
}

RestoreHealthGoodie::RestoreHealthGoodie (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Goodie(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_RESTORE_HEALTH;
    setVisible(true);
}

AmmoGoodie::AmmoGoodie (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Goodie(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_AMMO;
    setVisible(true);
}

ExtraLifeGoodie::ExtraLifeGoodie (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Goodie(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_EXTRA_LIFE;
    setVisible(true);
}

Bullet::Bullet (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = getDirection();
    imID = IID_BULLET;
    setVisible(true);
}

Exit::Exit (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Item(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = none;
    imID = IID_EXIT;
    setVisible(false);
    m_visibility = false;
    m_playerPresence = false;
}

Robot::Robot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Actor(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    initHP(10);
    direc = getDirection();
    setVisible(true);
    m_tickCount = 0;
}

SnarlBot::SnarlBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Robot(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = getDirection();
}

KleptoBot::KleptoBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:Robot(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = right;
    initHP(5);
    resetDistanceBeforeTurning();
    m_stolenGoodie = "";
    resetStepsMoved();
}

AngryKleptoBot::AngryKleptoBot (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name)
:KleptoBot(imID, x, y, direc, studWorld, name)
{
    m_name = name;
    direc = right;
    initHP(8);
    resetDistanceBeforeTurning();
    resetStepsMoved();
}

Factory::Factory (int imID, int x, int y, Direction direc, StudentWorld* studWorld, string name, bool isAngryFactory)
:Item(imID, x, y, direc, studWorld, name)
{
    setIsItAnAngryFactory(isAngryFactory);
    m_name = name;
    direc = none;
//    m_isAngryFactory = true;
    setVisible(true);
}

// Methods

void Player::playerFire()
{
    if (getAmmo() <= 0){
        return;
    }
    int x = 0;
    int y = 0;
    switch (this->getDirection()) {
        case up:
            y = 1;
            break;
        case down:
            y = -1;
            break;
        case left:
            x = -1;
            break;
        case right:
            x = 1;
            break;
        default:
            break;
    }
    Bullet* b = new Bullet(IID_BULLET, Player::getX()+x, Player::getY()+y, getDirection(), getWorld(), "Bullet");
    getWorld()->addToList(b);
    setAmmo(-1);
    b->doSomething();
    getWorld()->playSound(4);
    return;
}

void Player::doSomething()
{
    if (m_HP == 0){
        setDead(true);
    }
    int ch;
    //Member* mp;
    if (getWorld()->getKey(ch)) {
        // user hit a key this tick!
        switch (ch)
        {
            case KEY_PRESS_UP:
                checkMove(0, 1, up);
                break;
            case KEY_PRESS_DOWN:
                checkMove(0, -1, down);
                break;
            case KEY_PRESS_LEFT:
                checkMove(-1, 0, left);
                break;
            case KEY_PRESS_RIGHT:
                checkMove(1, 0, right);
                break;
            case KEY_PRESS_SPACE:
                playerFire();
                break;
            case KEY_PRESS_ESCAPE:
                setDead(true);
                break;
            default:
                break;
        }
    }
}


void Player::checkMove(int x, int y, Direction direc)
{
    if (isDead()){
        return;
    }
    Member* mp = getWorld()->findMember(getX()+x, getY()+y);
    Member* mp2 = getWorld()->findMember(getX()+x+x, getY()+y+y);
    // checks two spots ahead
    
    if (mp == nullptr || !(mp->isBlocked()))
    {
        moveTo(getX()+x, getY()+y);
        setDirection(direc);
        return;
    }
    if (mp != nullptr)
    {
        if (mp->memberID() == "Boulder"){
            if (mp2 == nullptr || !(mp2->isBlocked()) || mp2->memberID() == "Hole"){
                Boulder* bp = static_cast<Boulder*>(mp);
                moveTo(getX()+x, getY()+y);
                bp->push(x, y);
                setDirection(direc);
                return;
            }
        }
        if (mp->memberID() == "Jewel"){
            //getWorld()->decJewels();
            setDirection(direc);
            return;
        }
        setDirection(direc);
    }
}

string Member::memberID() {return m_name;}

bool Member::isDead() const{return m_dead;}
void Member::setDead(bool b) {m_dead = b;}

void Member::initHP(int health) {m_HP = health;}
void Member::setHP(int health) {(m_HP+= health);}
void Player::setHP(int health) {(m_HP+=health);}
//void Boulder::setHP(int health) {(m_HP+=health);}

int Member::getHP(){return m_HP;}
int Player::getHP() const{return m_HP;}

int Actor::getAmmo() const {return m_ammo;}
int Player::getAmmo() const {return m_ammo;}

void Boulder::push(int x, int y){
    moveTo(getX()+x, getY()+y);
}
void Player::setAmmo(int newRounds){
    m_ammo += newRounds;
}

void Player::damage(){
    Player::setHP(-2);
    cerr << "Player has been hurt!" << endl;
    if (getHP() == 0){
        setDead(true);
    }
}

unsigned int Player::getHealthPercentage() const
{
    cout.setf(ios::fixed);
    cout.precision(2);
    double healthPercentage = (getHP()*5.00);
//    healthPercentage = ((healthPercentage / 20.0)*100);
    return healthPercentage;
}

void Wall::doSomething(){}
void Boulder::doSomething(){}

void Boulder::damage(){
    //m_HP -= 2;
    setHP(-2);
    //if (m_HP == 0) {setDead(true);}
    if (getHP() == 0) {setDead(true);}
}

void Hole::doSomething()
{
    if (isDead()){
        return;
    }
    else
    {
        Member* mp = getWorld()->findMember(getX(), getY());
        if (mp->memberID() == "Boulder"){
            Boulder* bp = static_cast<Boulder*>(mp);
            bp->setDead(true);
            Hole::setDead(true);
        }
    }
}

bool Exit::isVisible() {return m_visibility;}
bool Exit::playerPresence() {return m_playerPresence;}

void Exit::doSomething()
{
    Member* mp = getWorld()->findSpecificMember(getX(), getY(), "Player");
    if (!isVisible()){
        if (getWorld()->anyJewels() == false){
            cerr << "Exit revealed!" << endl;
            m_visibility = true;
            Exit::setVisible(true);
            getWorld()->playSound(6);
            return;
        }
    }
    if (!playerPresence()){
        if (mp != nullptr && isVisible() == true)
        {
            cerr << "Player steps on exit" << endl;
            getWorld()->playSound(7);
            getWorld()->increaseScore(2000);
            getWorld()->setLevelFinished();
            getWorld()->giveBonus();
            m_playerPresence = true;
        }
    }
}
// The exit's method in StudentWorld hasn't been implemented yet

void Bullet::bulletCheckTarget()
{
    Member* bp = getWorld()->findSpecificMember(getX(), getY(), "Boulder");
    Member* wp = getWorld()->findSpecificMember(getX(), getY(), "Wall");
    Member* pp = getWorld()->findSpecificMember(getX(), getY(), "Player");
    Member* hsb = getWorld()->findSpecificMember(getX(), getY(), "HorizontalSnarlBot");
    Member* vsb = getWorld()->findSpecificMember(getX(), getY(), "VerticalSnarlBot");
    Member* kb = getWorld()->findSpecificMember(getX(), getY(), "KleptoBot");
    Member* akb = getWorld()->findSpecificMember(getX(), getY(), "AngryKleptoBot");
    Member* fp = getWorld()->findSpecificMember(getX(), getY(), "Factory");
    if (bp != nullptr){
        Boulder* boulderPtr = static_cast<Boulder*>(bp);
        boulderPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (wp != nullptr){
        Bullet::setDead(true);
        return;
    }
    if (pp != nullptr){
        Player* playerPtr = static_cast<Player*>(pp);
        playerPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (hsb != nullptr){
        SnarlBot* snarlPtr = static_cast<SnarlBot*>(hsb);
        snarlPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (vsb != nullptr){
        SnarlBot* snarlPtr = static_cast<SnarlBot*>(vsb);
        snarlPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (kb != nullptr){
        KleptoBot* kleptoPtr = static_cast<KleptoBot*>(kb);
        kleptoPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (akb != nullptr){
        AngryKleptoBot* angryKleptoPtr = static_cast<AngryKleptoBot*>(akb);
        angryKleptoPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (fp != nullptr && kb!= nullptr){
        KleptoBot* kleptoPtr = static_cast<KleptoBot*>(kb);
        kleptoPtr->damage();
        Bullet::setDead(true);
        return;
    }
    if (fp != nullptr && akb!= nullptr){
        AngryKleptoBot* angryKleptoPtr = static_cast<AngryKleptoBot*>(akb);
        angryKleptoPtr->damage();
        Bullet::setDead(true);
        return;
    }
}

void Bullet::bulletMove()
{
    if (isDead()){
        return;
    }
    switch (this->getDirection()){
        case up:{
            Bullet::moveTo(getX(), getY()+1);
            break;
        }
        case down:{
            Bullet::moveTo(getX(), getY()-1);
            break;
        }
        case left:{
            Bullet::moveTo(getX()-1, getY());
            break;
        }
        case right:{
            Bullet::moveTo(getX()+1, getY());
            break;
        }
        case none:
            break;
    }
}

void Bullet::doSomething()
{
    if (isDead()){
        return;
    }
    bulletCheckTarget();
    bulletMove();
    bulletCheckTarget();
}

void Goodie::goodieFunction(Goodie* goodieItem)
{
    if (goodieItem->isDead()){
        return;
    }
    else
    {
        Member* mp = getWorld()->findSpecificMember(getX(), getY(), "Player");
        if (mp != nullptr)
        {
            if (goodieItem->memberID() == "Jewel"){
                getWorld()->increaseScore(50);
                getWorld()->decJewels();
            }
            if (goodieItem->memberID() == "Health"){
                getWorld()->increaseScore(500);
                Player* sp = static_cast<Player*>(mp);
                sp->setHP(20);
            }
            if (goodieItem->memberID() == "Ammo"){
                getWorld()->increaseScore(100);
                Player* sp = static_cast<Player*>(mp);
                sp->setAmmo(20);
            }
            if (goodieItem->memberID() == "Life"){
                getWorld()->incLives();
                getWorld()->increaseScore(1000);
            }
            getWorld()->playSound(5);
            goodieItem->setDead(true);
        }
    }
}

void Jewel::doSomething() {goodieFunction(this);}
void RestoreHealthGoodie::doSomething() {goodieFunction(this);}
void AmmoGoodie::doSomething() {goodieFunction(this);}
void ExtraLifeGoodie::doSomething() {goodieFunction(this);}

// Robot Implementations
void Robot::doSomething(){}
bool Robot::isDamageable() {return true;}
bool Robot::isShootingRobot() {return true;}

void SnarlBot::damage()
{
    setHP(-2);
    getWorld()->playSound(9);
    if (getHP() == 0){
        getWorld()->playSound(1);
        setDead(true);
        getWorld()->increaseScore(100);
    }
}

bool Robot::canItMoveThisTick(int aSpecificLevelsTicks){
    if (m_tickCount == aSpecificLevelsTicks){
        m_tickCount = 0;
        return true;
    }
    return false;
}

void Robot::robotFire()
{
    int x = 0;
    int y = 0;
    switch (this->getDirection()) {
        case up:
            y = 1;
            break;
        case down:
            y = -1;
            break;
        case left:
            x = -1;
            break;
        case right:
            x = 1;
            break;
        default:
            break;
    }
    Bullet* b = new Bullet(IID_BULLET, getX()+x, getY()+y, getDirection(), getWorld(), "Bullet");
    getWorld()->addToList(b);
    b->doSomething();
    getWorld()->playSound(3);
    return;
}

void Robot::incTickCount() {m_tickCount++;}

bool Robot::checkY(Member* mp)
{
    Member* pp = getWorld()->isPlayerInRow(mp->getX());
    if (pp != nullptr){
        return true;
    }
    return false;
}

bool Robot::checkX(Member* mp)
{
    Member* pp = getWorld()->isPlayerInCol(mp->getY());
    if (pp != nullptr){
        return true;
    }
    return false;
}

void Robot::reverseDirection(Direction direc)
{
    switch (direc) {
        case up:
            setDirection(down);
            break;
        case down:
            setDirection(up);
            break;
        case right:
            setDirection(left);
            break;
        case left:
            setDirection(right);
            break;
        case none:
            break;
    }
}

void Robot::checkMove(int x, int y, Direction direc, Member* mp)
{
    Member* pp = getWorld()->findMember(mp->getX()+x, mp->getY()+y);
    if (pp == nullptr || !(pp->isBlocked()))
    {
        moveTo(mp->getX()+x, mp->getY()+y);
        setDirection(direc);
        return;
    }
    if (pp == nullptr || pp->isBlocked())
    {
        reverseDirection(direc);
    }
}

bool Robot::checkDirection(Direction direc, Member* mp)
{
    Member* pp = getWorld()->findPlayer();
    int playerPosX = pp->getX();
    int playerPosY = pp->getY();
    switch (direc)
    {
        case up:
        {
            if (mp->getX() == playerPosX)
            {
                for (int i = mp->getY(); i < VIEW_HEIGHT; i++){
                    if (i == playerPosY){
                        return true;
                    }
                }
            }
            break;
        }
        case down:
        {
            if (mp->getX() == playerPosX)
            {
                for (int i = mp->getY(); i > 0; i--){
                    if (i == playerPosY){
                        return true;
                    }
                }
            }
            break;
        }
        case left:
        {
            if (mp->getY() == playerPosY)
            {
                for (int i = mp->getX(); i > 0; i--){
                    if (i == playerPosX){
                        return true;
                    }
                }
            }
            break;
        }
        case right:
        {
            if (mp->getY() == playerPosY)
            {
                for (int i = mp->getX(); i < VIEW_WIDTH; i++){
                    if (i == playerPosX){
                        return true;
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    return false;
}

void Robot::shootIfPossible(Member* pp)
{
    AngryKleptoBot* akb = static_cast<AngryKleptoBot*>(pp);
    switch (akb->getDirection()) {
        case up:
        {
            if (akb->checkY(akb) && akb->checkDirection(up, akb) && getWorld()->existsClearShotToPlayer(getX(), getY()+1, 0, 1))
            {
                robotFire();
            }
            break;
        }
        case down:
        {
            if (checkY(akb) && checkDirection(down, akb) && getWorld()->existsClearShotToPlayer(getX(), getY()-1, 0, -1))
            {
                robotFire();
            }
            break;
        }
        case left:
        {
            if (checkX(akb) && checkDirection(left, akb) && getWorld()->existsClearShotToPlayer(getX()-1, getY(), -1, 0))
            {
                robotFire();
            }
            break;
        }
        case right:
        {
            if (checkX(pp) && checkDirection(right, pp) && getWorld()->existsClearShotToPlayer(getX()+1, getY(), 1, 0))
            {
                robotFire();
            }
            break;
        }
        case none:
            break;
    }
}

void Robot::robotTryToFire(Member* mp)
{
    SnarlBot* pp = static_cast<SnarlBot*>(mp);
    switch (pp->getDirection()) {
        case up:
        {
            if (pp->checkY(pp) && pp->checkDirection(up, pp) && getWorld()->existsClearShotToPlayer(getX(), getY()+1, 0, 1))
            {
                robotFire();
            }
            else {pp->checkMove(0, 1, up, pp);}
            break;
        }
        case down:
        {
            if (checkY(pp) && checkDirection(down, pp) && getWorld()->existsClearShotToPlayer(getX(), getY()-1, 0, -1))
            {
                robotFire();
            }
            else {pp->checkMove(0, -1, down, pp);}
            break;
        }
        case left:
        {
            if (checkX(pp) && checkDirection(left, pp) && getWorld()->existsClearShotToPlayer(getX()-1, getY(), -1, 0))
            {
                robotFire();
            }
            else {pp->checkMove(-1, 0, left, pp);}
            break;
        }
        case right:
        {
            if (checkX(pp) && checkDirection(right, pp) && getWorld()->existsClearShotToPlayer(getX()+1, getY(), 1, 0))
            {
                robotFire();
            }
            else {pp->checkMove(1, 0, right, pp);}
            break;
        }
        case none:
            break;
    }
}

void SnarlBot::doSomething()
{
    if (isDead()){
        return;
    }
    int level = getWorld()->getLevel();
    int ticks = ((28 - level)/4);
    if (ticks < 3) {ticks = 3;}
    // Calculate this level's place with a check for minimum ticks
    
    if (!canItMoveThisTick(ticks)){
        incTickCount();
        return;
    }
    robotTryToFire(this);
    incTickCount();
}

void KleptoBot::resetStepsMoved()
{
    m_stepsMoved = 0;
}

void KleptoBot::damage()
{
    setHP(-2);
    getWorld()->playSound(9);
    if (getHP() <= 0)
    {
        getWorld()->playSound(1);
        setDead(true);
        getWorld()->increaseScore(10);
        dropGoodie();
    }
}

void KleptoBot::pickUpGoodie(int x, int y)
{
    Member* mp = getWorld()->findMember(x, y);
    m_stolenGoodie = mp->memberID();
    mp->setDead(true);
    getWorld()->playSound(11);
}

bool KleptoBot::isGoodieHere(int x, int y)
{
    Member* mp = getWorld()->findMember(x, y);
    if (mp != nullptr){
        string possibleGoodie = mp->memberID();
        if (possibleGoodie == "Health" || possibleGoodie == "Ammo" || possibleGoodie == "Life"){
            return true;
        }
    }
    return false;
}

void KleptoBot::dropGoodie()
{
    if (m_stolenGoodie == "Health"){
        Member* rhg = new RestoreHealthGoodie (IID_RESTORE_HEALTH, getX(), getY(), getDirection(), getWorld(), "Health");
        getWorld()->addToList(rhg);
        return;
    }
    if (m_stolenGoodie == "Ammo"){
        Member* ag = new AmmoGoodie (IID_AMMO, getX(), getY(), getDirection(), getWorld(), "Ammo");
        getWorld()->addToList(ag);
        return;
    }
    if (m_stolenGoodie == "Life"){
        Member* elg = new ExtraLifeGoodie (IID_EXTRA_LIFE, getX(), getY(), getDirection(), getWorld(), "Life");
        getWorld()->addToList(elg);
        return;
    }
}


void KleptoBot::resetDistanceBeforeTurning()
{
    m_distanceBeforeTurning = (rand()%6)+1;
}

Actor::Direction KleptoBot::getRandomDirection()
{
    int randDirectionChoice = (rand()%4)+1;
    switch (randDirectionChoice) {
        case 1:
            return up;
            break;
        case 2:
            return down;
            break;
        case 3:
            return left;
            break;
        case 4:
            return right;
            break;
    }
    return none;
}

bool KleptoBot::ifObstruction(int x, int y, Direction direc)
{
    Member* mp = getWorld()->findMember(x, y);
    switch (direc) {
        case up:
        {
            mp = getWorld()->findMember(getX(), getY()+1);
            break;
        }
        case down:
        {
            mp = getWorld()->findMember(getX(), getY()-1);
            break;
        }
        case left:
        {
            mp = getWorld()->findMember(getX()-1, getY());
            break;
        }
        case right:
        {
            mp = getWorld()->findMember(getX()+1, getY());
            break;
        }
        default:
        {
            break;
        }
    }
    if (mp != nullptr && mp->isBlocked()){
        return true;
    }
    return false;
}

void KleptoBot::checkMoveKlepto(int x, int y, Direction direc)
{
    int changeByX = 0;
    int changeByY = 0;
    Member* mp = getWorld()->findMember(getX(), getY());
    switch (direc) {
        case up:
        {
            mp = getWorld()->findMember(getX(), getY()+1);
            changeByY = 1;
            break;
        }
        case down:
        {
            mp = getWorld()->findMember(getX(), getY()-1);
            changeByY = -1;
            break;
        }
        case left:
        {
            mp = getWorld()->findMember(getX()-1, getY());
            changeByX = -1;
            break;
        }
        case right:
        {
            mp = getWorld()->findMember(getX()+1, getY());
            changeByX = 1;
            break;
        }
        default:
        {
            break;
        }
    }
    if (mp == nullptr || !(mp->isBlocked()))
    {
        setDirection(direc);
        moveTo(getX()+changeByX, getY()+changeByY);
        incStepsMoved();
        return;
    }
    if (mp == nullptr || mp->isBlocked())
    {
        checkAnotherMove(x, y, getDirection());
    }
}

void KleptoBot::incStepsMoved()
{
    m_stepsMoved++;
}

int KleptoBot::getStepsMoved()
{
    return m_stepsMoved;
}

void KleptoBot::checkAnotherMove(int x, int y, Direction direc)
{
    // base case for if all 4 directions are blocked
    if (ifObstruction(x, y, up) && ifObstruction(x, y, down) && ifObstruction(x, y, left) && ifObstruction(x, y, right)){
        setDirection(getRandomDirection());
        return;
    }
    resetDistanceBeforeTurning();
    Direction d = getRandomDirection();
    switch (d) {
        case up:
        {
            if (ifObstruction(x, y, up)){
                checkAnotherMove(x, y, getRandomDirection());
            }
            else{
                setDirection(up);
                moveTo(getX(), getY()+1);
                incStepsMoved();
                return;
            }
            break;
        }
        case down:
        {
            if (ifObstruction(x, y, down)){
                checkAnotherMove(x, y, getRandomDirection());
            }
            else{
                setDirection(down);
                moveTo(getX(), getY()-1);
                incStepsMoved();
                return;
            }
            break;
        }
        case left:
        {
            if (ifObstruction(x, y, left)){
                checkAnotherMove(x, y, getRandomDirection());
            }
            else{
                setDirection(left);
                moveTo(getX()-1, getY());
                incStepsMoved();
                return;
            }
            break;
        }
        case right:
        {
            if (ifObstruction(x, y, right)){
                checkAnotherMove(x, y, getRandomDirection());
            }
            else{
                setDirection(right);
                moveTo(getX()+1, getY());
                incStepsMoved();
                return;
            }
            break;
        }
        default:
            break;
    }
}

int KleptoBot::getDistanceBeforeTurning() {return m_distanceBeforeTurning;}

void KleptoBot::doSomething()
{
    if (isDead()){
        return;
    }
    int level = getWorld()->getLevel();
    int ticks = ((28 - level)/4);
    if (ticks < 3) {ticks = 3;}
    // Calculate this level's place with a check for minimum ticks
    
    if (!canItMoveThisTick(ticks)){
        incTickCount();
        return;
    }
    if (isGoodieHere(getX(), getY())){
        pickUpGoodie(getX(), getY());
        return;
    }
    if (getStepsMoved() < getDistanceBeforeTurning()){
        checkMoveKlepto(getX(), getY(), getDirection());
        return;
    }
    else {
        checkAnotherMove(getX(), getY(), getDirection());
        return;
    }
}

void AngryKleptoBot::damage()
{
    setHP(-2);
    getWorld()->playSound(9);
    if (getHP() == 0)
    {
        getWorld()->playSound(1);
        setDead(true);
        getWorld()->increaseScore(20);
        dropGoodie();
    }
}

void AngryKleptoBot::doSomething()
{
    if (isDead()){
        dropGoodie();
        return;
    }
    int level = getWorld()->getLevel();
    int ticks = ((28 - level)/4);
    if (ticks < 3) {ticks = 3;}
    
    if (!canItMoveThisTick(ticks)){
        incTickCount();
        return;
    }
    shootIfPossible(this);
    if (isGoodieHere(getX(), getY())){
        pickUpGoodie(getX(), getY());
        return;
    }
    if (getStepsMoved() < getDistanceBeforeTurning()){
        checkMoveKlepto(getX(), getY(), getDirection());
        return;
    }
    else {
        checkAnotherMove(getX(), getY(), getDirection());
        return;
    }
}


//////////////////

bool Factory::getIsItAnAngryFactory() {return m_isAngryFactory;}
void Factory::setIsItAnAngryFactory(bool set) {m_isAngryFactory = set;}

void Factory::doSomething()
{
    int x = getX();
    int y = getY();
    int count = 0;
    for (int i = x-3; i < (x+3); i++){
        for (int j = y-3; j < (y+3); j++){
            Member* mp = getWorld()->findSpecificMember(i, j, "KleptoBot");
            Member* mp2 = getWorld()->findSpecificMember(i, j, "AngryKleptoBot");
            if (mp != nullptr || mp2 != nullptr){
                count++;
            }
        }
    }
    Member* mp3 = getWorld()->findSpecificMember(x, y, "KleptoBot");
    Member* mp4 = getWorld()->findSpecificMember(x, y, "AngryKleptoBot");
    if (count < 3 && mp3 == nullptr && mp4 == nullptr)
    {
        int chance = (rand() % 50);
        if (chance == 5)
        {
            if (getIsItAnAngryFactory()){
                Member* newAngryKlepto = new AngryKleptoBot (IID_ANGRY_KLEPTOBOT, x, y, right, getWorld(), "AngryKleptoBot");
                getWorld()->addToList(newAngryKlepto);
                getWorld()->playSound(8);
                return;
            }
            else {
                Member* newKlepto = new KleptoBot (IID_KLEPTOBOT, x, y, right, getWorld(), "KleptoBot");
                getWorld()->addToListBack(newKlepto);
                getWorld()->playSound(8);
                return;
            }
        }
    }
    
}

// All Member isBlocked methods -- Tells a player if the player can move onto this member
bool Player::isBlocked() {return true;}
bool Boulder::isBlocked() {return true;}
bool Wall::isBlocked() {return true;}
bool Hole::isBlocked() {return true;}
bool Jewel::isBlocked() {return false;}
bool RestoreHealthGoodie::isBlocked() {return false;}
bool AmmoGoodie::isBlocked() {return false;}
bool ExtraLifeGoodie::isBlocked() {return false;}
bool Bullet::isBlocked() {return true;}
bool Exit::isBlocked() {return false;}
bool Robot::isBlocked() {return true;}
bool Factory::isBlocked() {return true;}
