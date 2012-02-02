#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Dot.h"
#include "Setup.h"
#include "World.h"
#include <string>
#include <cstdlib>
#include <vector>

class Setup;
class Dot;
class Particle;

class ImageManager
{
    public:
        ImageManager();
        SDL_Surface* loadImage(std::string filename);
        void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
        bool getFiles();
        bool loadFont();
        TTF_Font* getFont();
        SDL_Color getColour();
        void clean();
        //SDL_Surface* getMessage();
        void drawAll(Dot &d, Setup &pSetup, World &pWorld);
        void drawPlayer(Setup &pSet, Dot &pDot);
        void drawenemies(float &x, float &y, Setup &s);
        void drawParticles(int &t, int &x, int &y, Setup &pSet);
        void drawBullets(int &bx, int &by, Setup &pSet);
        SDL_Surface* getImages(int i);
        virtual ~ImageManager();
    protected:
    private:

        std::vector <SDL_Surface*> surfaces;
        SDL_Surface *background;
        SDL_Surface *plants;
        SDL_Surface *dot;

        SDL_Surface *red;
        SDL_Surface *orange;
        SDL_Surface *gold;
        SDL_Surface *green;
        SDL_Surface *blue;
        SDL_Surface *purple;

        SDL_Surface *block_a;
        SDL_Surface *block_b;

        SDL_Surface *testmessage;
        TTF_Font *font;
        SDL_Color textColor;
        SDL_Rect clip_r[20];

        //Setup setup1;

};

#endif // IMAGEMANAGER_H
