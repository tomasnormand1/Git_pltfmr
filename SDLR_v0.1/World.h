#ifndef WORLD_H
#define WORLD_H
#include "SDL/SDL.h"
#include "Setup.h"

#include <vector>

using namespace std;

class World
{
    public:
        World();
        std::vector<SDL_Rect> getBoxes();
        std::vector<int> getgridval();
        bool set_tiles();
        void addobject();
        SDL_Rect getwall();
        int getbw();
        void camera_box_offset(int i, int newX);
        virtual ~World();
    protected:
    private:
        vector<SDL_Rect> world_boxes;
        vector<int> world_val;
        SDL_Rect collWall;
        vector<vector<int> > map_grid;
        int test[4];
        const int TILE_W;
        const int TILE_H;
        //total tiles
        const int TOTAL_T;
        // tile type
        const int TYPE_1;
        const int TYPE_2;
        //level brick x and y
        int level_brick_x;
        int level_brick_y;
};

#endif // WORLD_H
