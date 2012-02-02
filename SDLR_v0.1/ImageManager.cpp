#include "ImageManager.h"
#include "Setup.h"
#include "Dot.h"
#include "World.h"
//#include "Physics.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


ImageManager::ImageManager()
{
    //SDL_Rect clip[4];

    //vector <SDL_Surface*> surfaces;

    // images
    background = NULL;
    plants = NULL;
    dot = NULL;

    red = NULL;
    orange = NULL;
    gold = NULL;
    green = NULL;
    blue = NULL;
    purple = NULL;

    block_a = NULL;
    block_b = NULL;

    // messages

    font = NULL;

    textColor = {0, 0, 0};

    testmessage = NULL;
    //ctor
}

SDL_Surface* ImageManager::loadImage(std::string filename)
{
    // blit buffer
    SDL_Surface* buffer = NULL;

    //final image blitter to screen
    SDL_Surface* final_image = NULL;

    // load image to buffer
    buffer = IMG_Load(filename.c_str());

    // check if loaded correctly
    if(buffer != NULL)
    {
        // create final, optimised image
        final_image = SDL_DisplayFormat(buffer);

        // free buffer surface
        SDL_FreeSurface(buffer);

        // if final_image loaded correctly
        if(final_image != NULL)
        {
            // map the colour key
            Uint32 colorKey = SDL_MapRGB(final_image->format, 0xFF, 0, 0xFF);

            SDL_SetColorKey(final_image, SDL_SRCCOLORKEY, colorKey);
        }
    }

    // return final screen
    return final_image;
}

void ImageManager::applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
    // temp surface
    SDL_Rect offset;

    // give the offsets to teh rectangle
    offset.x = x - 10;
    //offset.w = 40;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset);
}

bool ImageManager::getFiles()
{
    /**
        TODO loop through files in dir and use loadImage() on each
    */
    // images and sprites
    background = loadImage("res/images/sqBG.png");
    plants = loadImage("res/images/plants.bmp");
    dot = loadImage("res/images/captainsprite.bmp");

    red = loadImage("res/images/red.bmp");
    orange = loadImage("res/images/orange.bmp");
    gold = loadImage("res/images/gold.bmp");
    green = loadImage("res/images/green.bmp");
    blue = loadImage("res/images/blue.bmp");
    purple = loadImage("res/images/purple.bmp");

    block_a = loadImage("res/images/tile_1.bmp");
    block_b = loadImage("res/images/tile_2.bmp");

    if(block_b == NULL || block_a == NULL || plants == NULL || background == NULL || dot == NULL || red == NULL || orange == NULL || gold == NULL || green == NULL || blue == NULL || purple == NULL)
    {
        return false;
    }

    surfaces.push_back(background);
    surfaces.push_back(plants);
    surfaces.push_back(dot);

    surfaces.push_back(red);
    surfaces.push_back(orange);
    surfaces.push_back(gold);
    surfaces.push_back(green);
    surfaces.push_back(blue);
    surfaces.push_back(purple);

    surfaces.push_back(block_a);
    surfaces.push_back(block_b);

    return true;
}


bool ImageManager::loadFont()
{
    //fonts
    font = TTF_OpenFont("res/fonts/Ubuntu.ttf", 30);

    if(font == NULL)
    {
        return false;
    }

    return true;
}

TTF_Font* ImageManager::getFont()
{
    return font;
}

SDL_Color ImageManager::getColour()
{
    return textColor;
}


void ImageManager::clean()
{
    // clean images
    //SDL_FreeSurface(background);
    for(int i = 0; i < surfaces.size(); i++)
    {
        SDL_FreeSurface(surfaces.at(i));
    }

    // clean messages
    SDL_FreeSurface(testmessage);

    // delete the vecot contents
    surfaces.clear();

    // close font and quit ttf
    TTF_CloseFont(font);
    TTF_Quit();
}

void ImageManager::drawAll(Dot &d, Setup &pSetup, World &pWorld)
{
    // background stars
    applySurface(0, 0, background, pSetup.getScreen());
    applySurface(0, 0, plants, pSetup.getScreen());
    //applySurface((d.getPlayerX() * -0.1) + background->w *2, d.getPlayerY()* -0.1, background, pSetup.getScreen());

    //uncomment to print size of world vector
    //cout << pWorld.getBoxes().size();
    for (int i = 0; i < pWorld.getBoxes().size(); i++ )
    {
        //cout << "camera x: " << pSetup.getCamera().x << endl;
        //int rx = pWorld.getBoxes.at(i).x;
        //pWorld.camera_box_offset(i, d.getPlayerX() - pSetup.getCamera().x);
//        if(!(d.getPlayerX() < (pSetup.getCamera().x + pSetup.getCamera().w) /2))
//        {
//            pWorld.camera_box_offset(i, d.getxvel());
//            //pWorld.camera_box_offset(i, d.getxvel() - pSetup.getCamera().x);
//            SDL_FillRect(pSetup.getScreen(), &pWorld.getBoxes().at(i), SDL_MapRGB(pSetup.getScreen()->format, 0x63, 0x63, 0x63));
//        }
//        else
//        {
//            block_a->w = 32;
//            block_a->h = 32;
//        if(pWorld.getgridval()[i] == 0)
            applySurface(pWorld.getBoxes().at(i).x, pWorld.getBoxes().at(i).y, block_a, pSetup.getScreen());
//        else if(pWorld.getgridval()[i] == 2)
//            applySurface(pWorld.getBoxes().at(i).x, pWorld.getBoxes().at(i).y, block_a, pSetup.getScreen());
            //applySurface(&pWorld.getBoxes().at(i))
            //pWorld.camera_box_offset(i, d.getxvel());
            //SDL_FillRect(pSetup.getScreen(), &pWorld.getBoxes().at(i), SDL_MapRGB(pSetup.getScreen()->format, 0x63, 0x63, 0x63));
//        }

    }

    // loop through all bodies in world and draw them
    //SDL_FillRect(setup1.getScreen(), &collWall, SDL_MapRGB(setup1.getScreen()->format, 0x88, 0x24, 0xF7));
}

void ImageManager::drawPlayer(Setup &pSet, Dot &pDot)
{
    // top right sprite
    clip_r[0].x = 64;
    clip_r[0].y = 0;
    clip_r[0].w = 64;
    clip_r[0].h = 64;
    //1st
    clip_r[1].x = 64;
    clip_r[1].y = 128;
    clip_r[1].w = 64;
    clip_r[1].h = 64;
    // 2nd
    clip_r[2].x = 128;
    clip_r[2].y = 128;
    clip_r[2].w = 64;
    clip_r[2].h = 64;
    // 3rd
    clip_r[3].x = 192;
    clip_r[3].y = 128;
    clip_r[3].w = 64;
    clip_r[3].h = 64;
    //4th
    clip_r[4].x = 256;
    clip_r[4].y = 128;
    clip_r[4].w = 64;
    clip_r[4].h = 64;
    //5th
    clip_r[5].x = 329;
    clip_r[5].y = 128;
    clip_r[5].w = 64;
    clip_r[5].h = 64;
    //6th
    clip_r[6].x = 384;
    clip_r[6].y = 128;
    clip_r[6].w = 64;
    clip_r[6].h = 64;
    //left sprites
    //second frame move right
    clip_r[7].x = 64;
    clip_r[7].y = 192;
    clip_r[7].w = 64;
    clip_r[7].h = 64;
    // third frame move right
    clip_r[8].x = 128;
    clip_r[8].y = 192;
    clip_r[8].w = 64;
    clip_r[8].h = 64;
    //fourth
    clip_r[9].x = 192;
    clip_r[9].y = 192;
    clip_r[9].w = 64;
    clip_r[9].h = 64;
    //fifth
    clip_r[10].x = 256;
    clip_r[10].y = 192;
    clip_r[10].w = 64;
    clip_r[10].h = 64;
    //fifth
    clip_r[11].x = 320;
    clip_r[11].y = 192;
    clip_r[11].w = 64;
    clip_r[11].h = 64;
    //fifth
    clip_r[12].x = 384;
    clip_r[12].y = 192;
    clip_r[12].w = 64;
    clip_r[12].h = 64;
    /// make this into frame * width and frame * height;

    applySurface(pDot.getPlayerX() - pSet.getCamera().x,
                 pDot.getPlayerY() - pSet.getCamera().y,
                 dot,
                 pSet.getScreen(),
                 &clip_r[pDot.get_anim_frame()]);
}


void ImageManager::drawenemies(float &x, float &y, Setup &s)
{
    applySurface(x, y, dot, s.getScreen());
}


void ImageManager::drawParticles(int &t, int &x, int &y, Setup &pSet)
{
    int cx = pSet.getCamera().x;
    int cy = pSet.getCamera().y;
    switch(t)
    {
        case 1: applySurface(x - cx, (y - 12.5f) - cy, red, pSet.getScreen()); break;
        case 2: applySurface(x - cx, (y - 7.5f) - cy, orange, pSet.getScreen()); break;
        case 3: applySurface(x - cx, (y - 2.5f) - cy, gold, pSet.getScreen()); break;
        case 4: applySurface(x - cx, (y + 2.5f) - cy, green, pSet.getScreen()); break;
        case 5: applySurface(x - cx, (y + 7.5f) - cy, blue, pSet.getScreen()); break;
        case 6: applySurface(x - cx, (y + 12.5f) - cy, purple, pSet.getScreen()); break;
    }
}

void ImageManager::drawBullets(int &bx, int &by, Setup &pSet)
{
    applySurface(bx, by, red, pSet.getScreen());
}

// get images
SDL_Surface* ImageManager::getImages(int i)
{
    return surfaces.at(i);
}

ImageManager::~ImageManager()
{
    //dtor
}
