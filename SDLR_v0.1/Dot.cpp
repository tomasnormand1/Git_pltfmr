#include "Dot.h"
#include "SDL/SDL.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Setup.h"
#include "Particle.h"
#include "Bullet.h"
#include "World.h"
#include "physics.h"
#include "Vector2.h"

using namespace std;

Dot::Dot()
    :DOT_HEIGHT(58),
    DOT_WIDTH(50),
    GRAVITY(1),
    MAX_VEL(8),
    TOTAL_PARTICLES(1000),
    TOTAL_BULLETS(7),
    MIN_G_VAL(-20),
    MAX_G_VAL(50)
{
    //ctor
    // initialise coords
    playerX = 0;
    playerY = 0;
    cout << "dot x" << playerX << '\n';
    // init velocity
    xVel = 0;
    yVel = 0;
    // init anim frame
    anim_frame_r = 0;
    anim_frame_l = 0;
    anim_status = 0;
    frame_counter = 0;
    // button press flags
    up = false;
    left = false;
    right = false;
    space = false;
    shotcounter = 0;
    //speed of increase for jump
    jumpspeed = -20;
    //jump flag
    jumping = false;
    falling = true;
    //set collision to false
    collisionflag = 0;
    // generate the initial particles
    for(int i = 0; i < TOTAL_PARTICLES; i++)
    {
        particleArray[i] = new Particle((int)playerX, ((int)playerY + DOT_HEIGHT / 4));
        cout << "generating particle: " << i << '\n';
    }

}

void Dot::handle_input(SDL_Event &ev)
{
    // handle all possible key event presses
    if(ev.type == SDL_KEYDOWN)
    {
        cout << "keydown" << endl;
        // adjust vel
        switch(ev.key.keysym.sym)
        {
        case SDLK_w:
            up = true;
            break;
        case SDLK_a:
            left = true;
            break;//xVel -= DOT_WIDTH / 2; break;
        case SDLK_d:
            right = true;
            break;//xVel += DOT_WIDTH / 2; break;
        default:
            ;
        }
        //cout << xVel << "\n" << yVel << "\n";
        cout << ev.type << endl;
    }
    else if(ev.type == SDL_KEYUP)
    {
        cout << "keyup" << endl;
        switch(ev.key.keysym.sym)
        {
        case SDLK_w:
            up = false;
            break;//+= DOT_HEIGHT / 2; break;
        case SDLK_a:
            left = false;
            break;//xVel ++; break;//+= DOT_WIDTH / 2; break;
        case SDLK_d:
            right = false;
            break;//xVel --; break;//-= DOT_WIDTH / 2; break;
        default:
            ;
        }
    }
    else if(ev.type == SDL_MOUSEBUTTONDOWN)
    {
        space = true;
    }
    else if(ev.type == SDL_MOUSEBUTTONUP)
    {
        space = false;
    }
}


void Dot::jump()
{
    if(jumping)
    {
        falling = false;
        jumpspeed += GRAVITY;
        if(jumpspeed > 0)
        {
            jumping = false;
            falling = true;
        }
        yVel = jumpspeed;
    }

    if(falling && jumpspeed < 21)
    {
        jumpspeed += GRAVITY;
        yVel = jumpspeed;
    }

    if(jumpspeed >= 20)
    {
        falling = false;
        jumpspeed = -20;
    }
//    cout << jumpspeed << endl;
}


void Dot::move(Setup &set, World &pworld, Uint32 deltaTime)
{
    /// the higher the restitution number - the lower the restitution
    /// smooth movement, maybe change this for better collision detection
    float restitution = 2;
    //keydown
    //&& yVel > (MAX_VEL *-1)

    if(up)
    {
        jumping = true;
        up = false;
    }
    double prev_xVel = xVel;
    double prev_yVel = yVel;
    if(left)
    {
        if(xVel>(MAX_VEL * -1))
        {
            xVel--;
        }


        if(frame_counter % 7== 0)
        {
            anim_frame_l = (anim_frame_l % 6) + 7;
            cout << "l: " << anim_frame_l << endl;
        }
        frame_counter++;
    }
    else if(right)
    {
        if(xVel<MAX_VEL)
        {
            xVel++;
        }

        if(frame_counter % 7 == 0)
        {
            anim_frame_r = (anim_frame_r % 6) + 1;
            cout << "r: " << anim_frame_r << endl;
        }
        frame_counter++;
    }
    //keyup
    //if(!up && yVel < 0) yVel++;
    if(!left && xVel < 0)
    {
        xVel++;
        anim_frame_l =0;
    }
    else if(!right && xVel > 0)
    {
        xVel--;
        anim_frame_r =0;
    }
    jump();

    // if the dot goes too far to the left or teh right

    ///TODO FIX ME
    //SDL_Rect r = boxLoop(pworld);

    playerX -= set.getCamera().x;
    playerX += xVel;
    if((playerX + xVel > set.getLevelW() - DOT_WIDTH) || (playerX + xVel < 0) || boxLoop(pworld))
    {
        playerX -= (int)prev_xVel;
    }


    playerX -= set.getCamera().y;
    playerY += yVel;
    if ((playerY + yVel > set.getLevelH() - DOT_HEIGHT) || (playerY + yVel < 0) || boxLoop(pworld))
    {
        playerY -= (int)prev_yVel;
    }


    /*
    if((playerX + xVel <= set.getLevelW() - DOT_WIDTH) && (playerX + xVel >= 0) && collisionflag != 1 && collisionflag != 2)
    {
        colBox.x = playerX += (int)xVel;
        //colBox.x = playerX;
    }
    else if(collisionflag == 1 || collisionflag == 2)
    {
        if(collisionflag == 1)
        {
            //cout << "case 1";
            int c = (colBox.x + colBox.w) - r.x;
            colBox.x = playerX -= (c + 1);
        }
        else if(collisionflag == 2)
        {
            //cout << "case 2";
            int c = (r.x + r.w) - colBox.x;
            colBox.x = playerX += (c - 1);
        }
    }
    else
    {
        //collisionflag = false;
        cout << "collision!x" << endl;
        //colBox.x = xVel = ((int)xVel * - 1); /// restitution;
        //playerX = 10;
    }

    // same for y axis
    if(((playerY + DOT_HEIGHT + yVel) < set.getLevelH()) && (playerY > 0) && collisionflag != 3 && collisionflag != 4)
    {
        //colBox.y = playerY += (int)yVel;
        //colBox.y = playerY;
        colBox.y = playerY += (int)yVel;
    }
    else if(collisionflag == 3 || collisionflag == 4)
    {
        falling = false;
        if(collisionflag == 3)
        {
            //cout << "case 3";
            //int c = (colBox.y + colBox.h) - r.y;
            //playerY = colBox.y -= c;
            colBox.y -= yVel;
            playerY = colBox.y;
        }
        else if(collisionflag == 4)
        {
            //cout << "case 4";
            //int c = (r.y + r.h) - colBox.y;
            //colBox.y = playerY += c;
            colBox.y += yVel;
            playerY = colBox.y;
        }
    }
    else
    {
        //collisionflag = false;
        cout << "collision!y" << endl;
        colBox.y -= yVel; //= ((int)yVel * - 1) / restitution;
        playerY = colBox.y;
    }
    */




    /// TODO
    /**
    playerX +=xVel * (deltaTime / 1000.f);
    if(playerX < 0)
    {
        playerX = 0;
    }
    else if(playerX + DOT_WIDTH >= set.getScreen()->w)
    {
        playerX = set.getScreen()->w - DOT_WIDTH;
    }

    playerY += yVel * (deltaTime / 1000.f);
    if(playerY < 0)
    {
        playerY = 0;
    }
    else if(playerY + DOT_HEIGHT >= set.getScreen()->h)
    {
        playerY = set.getScreen()->h + DOT_HEIGHT;
    }
    */
}

bool Dot::boxLoop(World &pworld)
{
    // return if no boxes collided
    Physics p;
    SDL_Rect r;
    r.x = playerX;
    r.y = playerY;
    r.w = DOT_WIDTH;
    r.h = DOT_HEIGHT;
//    collisionflag = 0;
    for (int i = 0; i < pworld.getBoxes().size(); i++)
    {
        if (p.check_collision(r, pworld.getBoxes().at(i)) == 1 && pworld.getgridval().at(i) <= 1)
        {
            collisionflag = p.check_collision(r, pworld.getBoxes().at(i));
            return true;
        }
    }
    return false;
}


int const Dot::getPlayerX()
{
    return (int)playerX;
}

int const Dot::getPlayerY()
{
    return (int)playerY;
}

int const Dot::get_anim_frame()
{
    if(right)
        return anim_frame_r;
    else if(left)
        return anim_frame_l;
    else
        return 0;
}

int const Dot::getxvel()
{
    return xVel;
}

int const Dot::getyvel()
{
    return yVel;
}

void Dot::change_heading(SDL_Event &ev)
{
    // x and y coords of mouse
    float x, y;
    if(ev.type == SDL_MOUSEMOTION)
    {
        x = ev.motion.x;
        y = ev.motion.y;

        aim_vector.vx = x;
        aim_vector.vy = y;
    }
}

void Dot::shoot(Setup &pSet)
{
    //cout << shotcounter << endl;
//    if(space == true && (shotcounter +1) % TOTAL_BULLETS != 0)

    if(space == true)
    {
        if(bulletArray.size() <= TOTAL_BULLETS)
        {
            Vector2 v2(aim_vector.vx - (playerX + (DOT_WIDTH/2)), aim_vector.vy - (playerY + (DOT_HEIGHT/2)) );
            v2.normalise();
            v2.scale(15);
            Bullet b((int)playerX + (DOT_WIDTH/2), (int)playerY + (DOT_HEIGHT/2), v2.vx, v2.vy);

            cout << "x: " << aim_vector.vx - playerX << endl;
            cout << "y: " << aim_vector.vy - playerY << endl;
            bulletArray.push_back(b);
            /// fix me
            //bulletArray.push_back(new Bullet(((int)playerX + DOT_WIDTH /2), ((int)playerY + DOT_HEIGHT /2), 10, 0));
            //cout << "array size: " << bulletArray.size() << endl;
            space = false;
            //bulletArray.push_back(b);

        }
    }
    //cout << "size " << bulletArray.size() << endl;
}

void Dot::showBulletD(ImageManager &pIm1, Setup &pSet)
{
    //int bullet_size = bulletArray.size();
    if(bulletArray.size() > 0)
    {
        //reverse(bulletArray.begin(), bulletArray.end());
        for (int i = 0; i < bulletArray.size(); i++)
        {
            if(bulletArray[i].isDeadB() == true)
            {
                //delete bulletArray[i];
                //cout << bulletArray.size() << endl;
                bulletArray.pop_front();
            }

        }

        for(int i = 0; i < bulletArray.size(); i++)
        {
            bulletArray[i].showBullet(pIm1, pSet);
        }
    }
}

void Dot::showParticleD(ImageManager &pIm1, Setup &pSet)
{
    for(int i = 0; i < TOTAL_PARTICLES; i++)
    {
        if(particleArray[i]->isDead() == true)
        {
            //cout << "dead";
            delete particleArray[i];

            particleArray[i] = new Particle((int)playerX , ((int)playerY + DOT_HEIGHT / 4));
            //particleArray[i]->setCoords(x, y);
        }
    }

    for (int i = 0; i < TOTAL_PARTICLES ; i++ )
    {
        particleArray[i]->showParticle(pIm1, pSet);
    }
}

void Dot::setCamera(Setup &s)
{
    s.setCameraX((playerX - DOT_HEIGHT /2) - (s.getScreen()->w /2));
    s.setCameraY((playerY - DOT_HEIGHT /2) - (s.getScreen()->h /2));
    if(s.getCamera().x < 0)
        s.setCameraX(0);
    if(s.getCamera().y < 0)
        s.setCameraY(0);
    if(s.getCamera().x > s.getLevelW() - s.getCamera().w)
        s.setCameraX(s.getLevelW() - s.getCamera().w);
    if(s.getCamera().y > s.getLevelH() - s.getCamera().h)
        s.setCameraY(s.getLevelH() - s.getCamera().h);
}

Dot::~Dot()
{
    //delete particleArray[];

    for(int i = 0; i < TOTAL_PARTICLES; i++)
    {
        delete particleArray[i];
    }
}
