#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    string cur;
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel("level00.dat");
    if (result == Level::load_fail_file_not_found){
        cerr << "Could not find level00.dat data file\n";
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level:: load_fail_bad_format){
        cerr << "Your level was improperly formatted\n";
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level:: load_success)
    {
        cerr << "Successfully loaded level\n";
        for (int y = 0; y < VIEW_HEIGHT; y++){
            for (int x = 0; x < VIEW_WIDTH; x++)
            {
                Level::MazeEntry ge = lev.getContentsOf(y,x);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::player:
                    {
                        Player* p = new Player (IID_PLAYER, y, x, Actor::right);
                        ActorList.push_back(p);
                        break;
                    }
                    case Level::wall:
                    {
                        //Wall* w = new Wall (IID_WALL, y, x, Actor::none);
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

int StudentWorld::move()
{
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    ;
}


int StudentWorld::loadUpLevel()
{
    return 0;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
