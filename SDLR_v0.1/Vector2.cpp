#include "Vector2.h"

#include "math.h"

Vector2::Vector2()
{
    // null vector;
    vx=0;
    vy=0;
}

Vector2::Vector2(float x, float y)
{
    vx = x;
    vy = y;
}

Vector2& Vector2::operator+ (const Vector2 &v)
{
    float tmpx, tmpy;
    tmpx = v.vx + vx;
    tmpy = v.vy + vy;

    Vector2 _v(tmpx, tmpy);
    return _v;
}

float Vector2::magnitude() const
{
    float mag = sqrtf((vx * vx) + (vy * vy));
    return mag;
}

void Vector2::normalise()
{
    float mag = magnitude();
    if(mag != 0)
    {
        vx /= mag;
        vy /= mag;
    }
}

void Vector2::scale(float scalar)
{
    vx *= scalar;
    vy *= scalar;
}

const float Vector2::getanglexy(const Vector2 & v) const
{
    // get the heading angle given a vector on the x/y axis
    float heading_angle;

    heading_angle = (float)atan2f(v.vx, v.vy);
    return heading_angle;
}

float Vector2::get_x() const
{
    return vx;
}

float Vector2::get_y() const
{
    return vy;
}

Vector2::~Vector2()
{
    //dtor
}
