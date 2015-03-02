#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    m_levelFinish = false;
    jewelCount = 0;
    m_bonus = 1000;
    Level lev(assetDirectory());
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss.fill('0');
    oss << "level" << setw(2) << getLevel() << ".dat";
    cerr << getLevel() << endl;
    string s = oss.str();
    cerr << s << endl;
    //Level::LoadResult result = lev.loadLevel("level01.dat");
    Level::LoadResult result = lev.loadLevel(s);
    if (result == Level::load_fail_file_not_found || getLevel() > 99){;
        return GWSTATUS_PLAYER_WON;
    }
    else if (result == Level:: load_fail_bad_format){
        cerr << "Your level was improperly formatted\n";
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level:: load_success)
    {
        cerr << "Successfully loaded level\n";
        for (int x = 0; x < VIEW_WIDTH; x++){
            for (int y = 0; y < VIEW_HEIGHT; y++)
            {
                Level::MazeEntry ge = lev.getContentsOf(x,y);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::player:
                    {
                        Member* p = new Player (IID_PLAYER, x, y, Member::right, this, "Player");
                        MemberList.push_front(p);
                        break;
                    }
                    case Level::wall:
                    {
                        Member* w = new Wall (IID_WALL, x, y, Member::none, this, "Wall");
                        MemberList.push_front(w); //was back
                        break;
                    }
                    case Level::boulder:
                    {
                        Member* b = new Boulder (IID_BOULDER, x, y, Member::none, this, "Boulder");
                        MemberList.push_front(b);
                        break;
                    }
                    case Level::hole:
                    {
                        Member* h = new Hole (IID_HOLE, x, y, Member::none, this, "Hole");
                        MemberList.push_front(h); // was back
                        break;
                    }
                    case Level::jewel:
                    {
                        Member* j = new Jewel(IID_JEWEL, x, y, Member::none, this, "Jewel");
                        MemberList.push_front(j); //was back
                        jewelCount++;
                        break;
                    }
                    case Level::restore_health:
                    {
                        Member* rh = new RestoreHealthGoodie(IID_RESTORE_HEALTH, x, y, Member::none, this, "Health");
                        MemberList.push_front(rh); //was back
                        break;
                    }
                    case Level::ammo:
                    {
                        Member* a = new AmmoGoodie(IID_AMMO, x, y, Member::none, this, "Ammo");
                        MemberList.push_front(a); //was back
                        break;
                    }
                    case Level::extra_life:
                    {
                        Member* el = new ExtraLifeGoodie(IID_EXTRA_LIFE, x, y, Member::none, this, "Life");
                        MemberList.push_front(el); //was back
                        break;
                    }
                    case Level::exit:
                    {
                        Member* ex = new Exit(IID_EXIT, x, y, Member::none, this, "Exit");
                        MemberList.push_front(ex);
                        break;
                    }
                    case Level::horiz_snarlbot:
                    {
                        Member* hsb = new SnarlBot (IID_SNARLBOT, x, y, Member::right, this, "HorizontalSnarlBot");
                        MemberList.push_front(hsb);
                        break;
                    }
                    case Level::vert_snarlbot:
                    {
                        Member* vsb = new SnarlBot (IID_SNARLBOT, x, y, Member::down, this, "VerticalSnarlBot");
                        MemberList.push_front(vsb);
                        break;
                    }
                    case Level::angry_kleptobot_factory:
                    {
                        Member* akfp = new Factory (IID_ROBOT_FACTORY, x, y, Member::none, this, "Factory", true);
                        MemberList.push_front(akfp);
                        break;
                    }
                    case Level::kleptobot_factory:
                    {
                        Member* kfp = new Factory (IID_ROBOT_FACTORY, x, y, Member::none, this, "Factory", false);
                        MemberList.push_front(kfp);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

Member* StudentWorld::findMember (int x, int y)
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    while (iter != MemberList.end())
    {
        if ((*iter)->getX() == x && (*iter)->getY() == y){
            return (*iter);
        }
        iter++;
    }
    return nullptr;
}

Member* StudentWorld::findSpecificMember (int x, int y, string ID)
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    while (iter != MemberList.end())
    {
        if ((*iter)->getX() == x && (*iter)->getY() == y && (*iter)->memberID() == ID){
            return (*iter);
        }
        iter++;
    }
    return nullptr;
}

Member* StudentWorld::isPlayerInCol(int y)
{
    Member* pp = findPlayer();
    if (y == pp->getY()){
        return pp;
    }
    return nullptr;
}

Member* StudentWorld::isPlayerInRow(int x)
{
    Member* pp = findPlayer();
    if (x == pp->getX()){
        return pp;
    }
    return nullptr;
}

Member* StudentWorld::findPlayer()
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    while (iter != MemberList.end())
    {
        if ((*iter)->memberID() == "Player"){
            return (*iter);
        }
        iter++;
    }
    return nullptr;
}

bool StudentWorld::isObstacle(Member* mp)
{
    if (mp->memberID() == "Boulder" || mp->memberID() == "Wall" || mp->memberID() == "Factory" || mp->memberID() == "HorizontalSnarlBot" || mp->memberID() == "VerticalSnarlBot")
    {
        return true;
    }
    return false;
}

bool StudentWorld::existsClearShotToPlayer(int x, int y, int dirX, int dirY)
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    
    Member* pp = findPlayer();
    int destinationX = pp->getX();
    int destinationY = pp->getY();
    
    
    if (dirY == -1) // Bullet would be travelling down (i.e. to the bottom of screen)
    {
        for (int i = y; i > 0; i--)
        {
            iter = MemberList.begin();
            while (iter != MemberList.end())
            {
                if (x == (*iter)->getX() && i == (*iter)->getY())
                {
                    if (isObstacle(*iter)){
                        return false;
                    }
                }
                iter++;
            }
        }
        return true;
    }
    if (dirY == 1)
    {
        for (int i = y; i < destinationY; i++) // Bullet would be travelling up (same column)
        {
            iter = MemberList.begin();
            while (iter != MemberList.end())
            {
                if (x == (*iter)->getX() && i == (*iter)->getY())
                {
                    if (isObstacle(*iter)){
                        return false;
                    }
                }
                iter++;
            }
        }
        return true;
    }
    if (dirX == -1) // Bullet would be travelling to the left
    {
        for (int i = x; i > destinationX; i--)
        {
            iter = MemberList.begin();
            while (iter != MemberList.end())
            {
                if ((*iter)->getY() == y)
                {
                    if ((*iter)->getX() == i)
                    {
                        if (isObstacle(*iter)){
                            return false;
                        }
                    }
                }
                iter++;
            }
        }
        return true;
    }
    if (dirX == 1)
    {
        for (int i = x; i < destinationX; i++) // Bullet would be travelling to the right
        {
            iter = MemberList.begin();
            while (iter != MemberList.end())
            {
                if (i == (*iter)->getX() && y == (*iter)->getY())
                {
                    if (isObstacle(*iter)){
                        return false;
                    }
                }
                iter++;
            }
        }
        return true;
    }
    return true;
}

void StudentWorld::setLevelFinished()
{
    m_levelFinish = true;
}

bool StudentWorld::isLevelDone()
{
    return m_levelFinish;
}

bool StudentWorld::decJewels()
{
    if (jewelCount == 0){
        return false;
    }
    jewelCount--;
    cerr << "One jewel gone" << endl;
    return true;
}

bool StudentWorld::anyJewels() const
{
    if (jewelCount == 0){
        cerr << "No more Jewels!" << endl;
        return false;
    }
    return true;
}

void StudentWorld::giveBonus()
{
    increaseScore(m_bonus);
}

void StudentWorld::changeBonus(int bonusAddition)
{
    m_bonus += bonusAddition;
}

int StudentWorld::getBonus()
{
    return m_bonus;
}

string StudentWorld::formatDisplay(int score, int level, int lives, int health, int ammo, unsigned int bonus)
{
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(2);
    oss.fill('0');
    oss << "Score: " << setw(7) << score << "  ";
    oss << "Level: " << setw(2) << level << "  ";
    oss << "Lives: " << setw(2) << lives << "  ";
    oss << "Health: " << setw(3) << health << "%  ";
    oss.fill(' ');
    oss << "Ammo: " << setw(3) << ammo << "  ";
    oss.fill('0');
    oss << "Bonus: " << setw(3) << bonus << "  ";
    
    return oss.str();
}
// This is the place for all the stringstream stuff

double StudentWorld::playerHP(Member* mp)
{
    Player* p = static_cast<Player*>(mp);
    return p->getHealthPercentage();
}

int StudentWorld::playerAmmo(Member* mp)
{
    Player* p = static_cast<Player*>(mp);
    return p->getAmmo();
}

void StudentWorld::setDisplayText()
{
    Member* mp = findPlayer();
    
    int score = getScore();
    int level = getLevel();
    unsigned int bonus = getBonus();
    int livesLeft = getLives();
    int health = playerHP(mp);
    int ammo = playerAmmo(mp);
    
    string s = formatDisplay(score, level, livesLeft, health, ammo, bonus);
    
    setGameStatText(s);
}

int StudentWorld::move()
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    
    setDisplayText();
    
    while (iter != MemberList.end())
    {
        Member* memb = *iter;
        if (memb->isDead() == false){
            memb->doSomething();
        }
        if (memb->isDead() == true)
        {
            if (memb->memberID() == "Player"){
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            delete *iter;
            iter = MemberList.erase(iter);
        }
        iter++;
    }
    
    changeBonus(-1);
    
//    Member* playerPtr = findPlayer();
//    if (playerPtr->isDead()){
//        decLives();
//        return GWSTATUS_PLAYER_DIED;
//    }
    
    if (isLevelDone() == true){
        giveBonus();
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Member*>::iterator iter;
    iter = MemberList.begin();
    
    Member* temp = (*iter);
    while (iter != MemberList.end())
    {
        temp = (*iter);
        delete temp;
        iter = MemberList.erase(iter);
    }
}

void StudentWorld::addToList(Member* mp)
{
    MemberList.push_front(mp);
}

void StudentWorld::addToListBack(Member* mp)
{
    MemberList.push_back(mp);
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
