#ifndef VEC_H
#define VEC_H
#include <ostream>
struct Vec2 {
    int x;
    int y;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(const Vec2& other) const;
    Vec2 operator*(float other) const;
    Vec2 operator/(float other) const;
    Vec2 operator/(const Vec2& other) const;

    
};
struct Vec3{
    int x;
    int y;
    int z;
    Vec3(float x, float y, float z): x(x), y(y), z(z) {};
};
std::ostream& operator<<(std::ostream& os, const Vec2& v);
#endif
