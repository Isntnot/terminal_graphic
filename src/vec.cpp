#include <iostream>
#include "vec.h"
#include <ostream>

Vec2 Vec2::operator+(const Vec2& other) const {
    return {x + other.x, y + other.y};
}
Vec2 Vec2::operator-(const Vec2& other) const {
    return {x - other.x, y - other.y};
}
Vec2 Vec2::operator*(const Vec2& other) const {
    return {x * other.x, y * other.y};
}
Vec2 Vec2::operator*(float other) const {
    return {x * other, y * other};
}
Vec2 Vec2::operator/(float other) const {
    return {x / other, y / other};
}
Vec2 Vec2::operator/(const Vec2& other) const {
    return {x / other.x, y / other.y};
}
std::ostream& operator<<(std::ostream& os, const Vec2& v){
    os << "(" << v.x << "," << v.y << ")";
    return os;
};
