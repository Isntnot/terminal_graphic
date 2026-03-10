#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <array>
#include "vec.h"

class Pixel {
public:
    Vec2 pos{};
    int color{};

    Pixel(Vec2 pos, int color);
};

class Scene {
private:
    std::array<int,2> size;

    void render_pixel(int c, int r, int color);
    void clear_terminal();

public:
    std::vector<Pixel> pixels;

    Scene(std::array<int,2> size);

    void add_pixel(const Pixel& pixel);

    void draw_line(Vec2 a, Vec2 b, int color);

    double edge_function(Vec2 a, Vec2 b, Vec2 c);

    void draw_square(Vec2 a, Vec2 b, int color, bool fill);

    void draw_triangle(Vec2 a, Vec2 b, Vec2 c, int color, bool fill);

    void draw_circle(Vec2 center, int r, int color);

    void draw();
};

#endif