#pragma once
#include "raylib.h"
#include <cmath>

class phy_obj
{

public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float radius;
    bool is_stable; //do we need to perform more phy calculations on the object?

public:
    phy_obj(Vector2 position, float radius, Vector2 velocity = {0, 0}, Vector2 acceleration = {0, 0});


    virtual void draw() = 0;
    virtual void draw_debug();
    virtual ~phy_obj() = default;
};


//every physics object would have a circle that is used for physics calculations
//call this function to draw that circle along with the velocity vector
void phy_obj::draw_debug(){
    
    // draw the circle
    DrawCircleLinesV(position, radius, BLACK);

    //draw the velocity vector
    Vector2 translated_velocity{velocity.x+position.x,velocity.y+position.y};
    DrawLineEx(position, translated_velocity, 2,ORANGE);
}

phy_obj::phy_obj(Vector2 position, float radius, Vector2 velocity, Vector2 acceleration) : position{position}, radius{radius},
    velocity{velocity}, acceleration{acceleration}, is_stable{false}
{
    
}
