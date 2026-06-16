#pragma once
#include "raylib.h"
#include <cmath>

class phy_obj
{

public:
    Vector2 position;
    Vector2 velocity = {0,0};
    Vector2 acceleration = {0,0};

    //if friction <1 then the values decrease after each iteration
    //if friction >1 then the values decrease after each iteration
    //if friction =1 then there is no friction
    float friction = 0.9f;
    float radius;
    bool is_stable = false; //do we need to perform more phy calculations on the object?
    bool is_dead = false;   //if true delete the said phy_object

    //how many bounces should a phy object do before getting deleted from the world
    // = -1 means object would keep on bouncing forever
    // == 1 means object would get flagged for deletion making is_dead = true
    // == 0 
    // > 1 means objects have that bounces remaining before being dead
    int bounce_before_death = -1;

    
public:
    phy_obj(Vector2 position, float radius, float friction, int bounce_before_death, 
        Vector2 velocity, Vector2 acceleration);
    phy_obj(Vector2 position, float radius);
    phy_obj(Vector2 position, float radius, int bounce_before_death);
    phy_obj(Vector2 position, float radius, float friction, int bounce_before_death);


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

phy_obj::phy_obj(Vector2 position, float radius,float friction,int bounce_before_death, Vector2 velocity, Vector2 acceleration)
    :   position{position}, radius{radius}, friction{friction}, bounce_before_death{bounce_before_death}, velocity{velocity},
        acceleration{acceleration}
{
}


phy_obj::phy_obj(Vector2 position, float radius)
    :   position{position}, radius{radius}
{
}

phy_obj::phy_obj(Vector2 position, float radius, int bounce_before_death)
    :   position{position}, radius{radius}, bounce_before_death{bounce_before_death}
{
}

phy_obj::phy_obj(Vector2 position, float radius, float friction, int bounce_before_death)
    :   position{position}, radius{radius}, friction{friction}, bounce_before_death{bounce_before_death}
{
}