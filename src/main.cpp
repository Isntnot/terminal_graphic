
#include <thread>
#include <chrono>
#include <cmath>
#include "vec.h"
#include <array>
#include "scene.h"
int main(){
    Scene scene({80, 40});
    float gravity = 1.0; 
    int frames_per_seconds = 60;
    float toughness = 0.8;
    #ifdef GRAVITY
    gravity = GRAVITY; 
    #endif
    #ifdef FRAME
    frames_per_seconds = FRAME; 
    #endif
    #ifdef TOUGHNESS
    toughness = TOUGHNESS; 
    #endif
    int cx = 40;
    int cy = 20;
    double t = 0.0;
    Vec2 velocity = {0,0};
    Vec2 position = {10, 0};
    const std::chrono::milliseconds FrameDuration(1000/frames_per_seconds);
    while(true){

        auto start = std::chrono::steady_clock::now();
        #ifdef ROTATING_TRIANGLE
        
        // --- orbiting triangle ---
        int r = 10;
        Vec2 a {
            (int)(cx + cos(t) * r),
            (int)(cy + sin(t) * r)
        };

        Vec2 b {
            (int)(cx + cos(t + 2.09) * r),
            (int)(cy + sin(t + 2.09) * r)
        };

        Vec2 c {
            (int)(cx + cos(t + 4.18) * r),
            (int)(cy + sin(t + 4.18) * r)
        };

        scene.draw_triangle(a, b, c, 196, true);
        #endif
        #ifdef CIRCLE
        // --- pulsing circle ---
        int pulse = 6 + (int)(sin(t * 2) * 3);
        scene.draw_circle({cx, cy}, pulse, 33);

        #endif
        #ifdef BOUNCING_SQUARE
        // --- bouncing square ---
        position = position + velocity;
        velocity.y += gravity;
        if (position.y > 20){
            position.y = 20;
            velocity.y = velocity.y * -toughness;
        }
        scene.draw_square(position, {position.x + 3, position.y + 3}, 82, true);
        #endif
        // --- render frame ---
        scene.draw();
        auto end = std::chrono::steady_clock::now();
        auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapse < FrameDuration){
            std::this_thread::sleep_for(FrameDuration - elapse);
        }
        t += 0.08;
    }
}
