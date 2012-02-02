#include "World.h"
#include "Setup.h"
#include "Dot.h"
#include "SDL/SDL.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


World::World()
    :TILE_W(32),
    TILE_H(32),
    TOTAL_T(768),
    TYPE_1(0),
    TYPE_2(1)
{
    level_brick_y = 32;
    level_brick_x = 24;
}

vector<SDL_Rect> World::getBoxes()
{
    return world_boxes;
}

vector<int> World::getgridval()
{
    return world_val;
}

void World::camera_box_offset(int i, int newX)
{
    //world_boxes.at(i).x -= newX;
}

bool World::set_tiles()
{
    std::stringstream map_name;
    // make a new file input stream
    std::ifstream map;
    map_name << "res/maps/" << level_brick_y << "_" << level_brick_x << ".txt";
    //string m_name = map_name.str();

    map.open(map_name.str().c_str());

    //map.open("res/maps/32_16.txt");

    // test to see if map is not exsisting
    if(!map.is_open())
    {
        cout << "file does not exist \n";
        return false;
    }
    //int ttype = -1;

    // row and column values for the 2d array of the map
    int colN, rowN, col, row;

    // temp map value
    int tmp_mval;
    // loops
    for(colN = 0; colN < level_brick_x && map.good(); colN++)
    {
        map_grid.push_back( vector<int>() );
        for (rowN = 0; rowN < level_brick_y ; rowN++)
        {
            // put the number from the file stream into the array
            map >> tmp_mval;
            map_grid[colN].push_back(tmp_mval);
        }

    }

    map.close();

    for (col = 0; col < level_brick_x ; col++ )
    {
    	for (row = 0; row < level_brick_y ; row++)
    	{
    		if(map_grid[col][rowN] == 0)
    		{
    		    //cout << " 00" << endl;
    		    world_val.push_back(0);
    		}
    		else if(map_grid[col][row] == 2)
    		{
    		    // no collision rect, but a surface still
    		    world_val.push_back(2);
    		}
    		else if(map_grid[col][row] == 1)
    		{
    		    // collision rect
                SDL_Rect r;
            	r.w = TILE_W;
            	r.h = TILE_H;
            	r.x = row * TILE_H;
            	r.y = col * TILE_W;
            	world_boxes.push_back(r);
            	world_val.push_back(1);
    		}
    	}
    }

    return true;
}

void World::addobject()
{

}

int World::getbw()
{
    return TILE_W;
}

SDL_Rect World::getwall()
{
    return collWall;
}

World::~World()
{
    //dtor
}
