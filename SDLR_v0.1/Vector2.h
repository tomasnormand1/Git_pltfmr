#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2
{
    public:
        Vector2();
        Vector2(float x, float y);
        Vector2 & operator+ (const Vector2 &v);
        const float getvector();
        float magnitude() const;
        void normalise();
        void scale(float scalar);
        const float getanglexy(const Vector2 & v) const;
        float get_x() const;
        float get_y() const;
        virtual ~Vector2();
        float vx, vy;
    protected:
    private:
    //x and y of vector within class
};

#endif // VECTOR2_H
