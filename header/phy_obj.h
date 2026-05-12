#pragma once
#include "raylib.h"


class phy_obj
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float angle; 
    float radius;
    bool is_stable; //do we need to perform more phy calculations on the object?

public:
    phy_obj(Vector2 position, float radius, float angle, Vector2 velocity = {0, 0}, Vector2 acceleration = {0, 0});


    virtual void draw() = 0;
    virtual ~phy_obj() = default;
};


phy_obj::phy_obj(Vector2 position, float radius, float angle, Vector2 velocity, Vector2 acceleration) : position{position}, radius{radius},
    velocity{velocity}, acceleration{acceleration}, is_stable{false}, angle{angle}
{
    
}
