#include <iostream>
#include <cmath>
#include "scene.h"

/* Pixel */

Pixel::Pixel(Vec2 pos, int color) : pos(pos), color(color) {}


/* Scene */

Scene::Scene(std::array<int,2> size) : size(size) {}

void Scene::render_pixel(int c, int r, int color){
    std::cout << "\033[" << r << ";" << c << "f";
    std::cout << "\033[38;5;" << color << "m"
              << "\033[48;5;" << color << "m"
              << "_";
    std::cout << "\033[0m";
}

void Scene::clear_terminal(){
    std::cout << "\033[2J";
    std::cout << "\033[H";
}

void Scene::add_pixel(const Pixel& pixel){
    pixels.push_back(pixel);
}


/* Line Rasterization (Bresenham-style) */

void Scene::draw_line(Vec2 a, Vec2 b, int color){

    int x1 = a.x;
    int y1 = a.y;
    int x2 = b.x;
    int y2 = b.y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(true){

        add_pixel(Pixel({x1, y1}, color));

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy){
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx){
            err += dx;
            y1 += sy;
        }
    }
}


/* Edge Function */

double Scene::edge_function(Vec2 a, Vec2 b, Vec2 c){
    return (b.x - a.x) * (c.y - a.y) -
           (b.y - a.y) * (c.x - a.x);
}


/* Square */

void Scene::draw_square(Vec2 a, Vec2 b, int color, bool fill){

    int x1 = std::min(a.x, b.x);
    int x2 = std::max(a.x, b.x);
    int y1 = std::min(a.y, b.y);
    int y2 = std::max(a.y, b.y);

    Vec2 c{x1, y2};
    Vec2 d{x2, y1};

    if(!fill){

        draw_line({x1, y1}, d, color);
        draw_line(d, {x2, y2}, color);
        draw_line({x2, y2}, c, color);
        draw_line(c, {x1, y1}, color);

    } else {

        for(int y = y1; y < y2; y++)
            draw_line({x1, y}, {x2, y}, color);
    }
}


/* Triangle */

void Scene::draw_triangle(Vec2 a, Vec2 b, Vec2 c, int color, bool fill){

    draw_line(a, b, color);
    draw_line(b, c, color);
    draw_line(a, c, color);

    if(!fill)
        return;

    int max_x = std::max(std::max(a.x, b.x), c.x);
    int min_x = std::min(std::min(a.x, b.x), c.x);
    int max_y = std::max(std::max(a.y, b.y), c.y);
    int min_y = std::min(std::min(a.y, b.y), c.y);

    for(int y = min_y; y <= max_y; y++){
        for(int x = min_x; x <= max_x; x++){

            Vec2 P{x,y};

            int ABP = edge_function(a,b,P);
            int BCP = edge_function(b,c,P);
            int CAP = edge_function(c,a,P);

            if((ABP >= 0 && BCP >= 0 && CAP >= 0) ||
               (ABP <= 0 && BCP <= 0 && CAP <= 0)){

                add_pixel(Pixel(P, color));
            }
        }
    }
}


/* Midpoint Circle Algorithm */

void Scene::draw_circle(Vec2 center, int r, int color){

    auto [x_centre, y_centre] = center;

    int x = r;
    int y = 0;

    add_pixel(Pixel({x + x_centre, y + y_centre}, color));
    add_pixel(Pixel({x_centre + r, y_centre}, color));
    add_pixel(Pixel({x_centre - r, y_centre}, color));
    add_pixel(Pixel({x_centre, y_centre + r}, color));
    add_pixel(Pixel({x_centre, y_centre - r}, color));

    int P = 1 - r;

    while(x > y){

        y++;

        if(P <= 0){
            P = P + 2*y + 1;
        } else {
            x--;
            P = P + 2*y - 2*x + 1;
        }

        if(x < y)
            break;

        add_pixel(Pixel({ x + x_centre,  y + y_centre}, color));
        add_pixel(Pixel({-x + x_centre,  y + y_centre}, color));
        add_pixel(Pixel({ x + x_centre, -y + y_centre}, color));
        add_pixel(Pixel({-x + x_centre, -y + y_centre}, color));

        if(x != y){

            add_pixel(Pixel({ y + x_centre,  x + y_centre}, color));
            add_pixel(Pixel({-y + x_centre,  x + y_centre}, color));
            add_pixel(Pixel({ y + x_centre, -x + y_centre}, color));
            add_pixel(Pixel({-y + x_centre, -x + y_centre}, color));
        }
    }
}


/* Render */

void Scene::draw(){

    clear_terminal();
    std::cout << "\033[?25l";
    for(const auto& pixel : pixels){

        if(pixel.pos.x >= 0 && pixel.pos.x < size[0] &&
           pixel.pos.y >= 0 && pixel.pos.y < size[1]){

            render_pixel(pixel.pos.x, pixel.pos.y, pixel.color);
        }
    }
    std::cout << "\033[?25h";
    std::cout.flush();
    pixels.clear();
}