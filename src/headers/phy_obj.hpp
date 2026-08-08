#pragma once
#include <raylib/raylib.h>

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
    bool is_stable = false; 
    bool is_dead = false;

    //how many bounces should a phy object do before getting deleted from the world
    // = -1 means object would keep on bouncing forever
    // == 1 means object would get flagged for deletion making is_dead = true
    // == 0 
    // > 1 means objects have that bounces remaining before being dead
    int bounce_before_death = -1;

    float start_angle = 0.0f;    
    float end_angle = 0.0f;
    
    
public:
    phy_obj(Vector2 position, float radius, float friction, int bounce_before_death, 
            Vector2 velocity, Vector2 acceleration);
    phy_obj(Vector2 position, float radius);
    phy_obj(Vector2 position, float radius, int bounce_before_death);
    phy_obj(Vector2 position, Vector2 velocity ,float radius, int bounce_before_death);
    phy_obj(Vector2 position, float radius, float friction, int bounce_before_death);

    virtual void draw() = 0;
    virtual void draw_debug();
    virtual ~phy_obj() = default;
};