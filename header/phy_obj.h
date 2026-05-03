#pragma once
#include "raylib.h"
#include "cmath"
#include "raymath.h"
#include <iostream>

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

    //void set_position(Vector2 new_position);
    //void increment_position(Vector2 inc_amount);

    //void set_angle(float rot_angle);
    //void increment_rotation(float inc_amount);

    virtual void draw() = 0;
    //virtual void rotate_wireframe(rot_angle)
    virtual ~phy_obj() = default;
};



phy_obj::phy_obj(Vector2 position, float radius, float angle, Vector2 velocity, Vector2 acceleration) : position{position}, radius{radius},
    velocity{velocity}, acceleration{acceleration}, is_stable{false}, angle{angle}
{
    
}

// // increment the current position by the given x,y amount
// void phy_obj::increment_position(Vector2 inc_amount)
// {

//     Vector2 new_position = {position.x + inc_amount.x, position.y + inc_amount.y};
//     set_position(new_position);
// }

// // directly set the angle of the phy obj
// void phy_obj::set_angle(float rot_angle)
// {
//     rotate_wireframe(rot_angle);
// }



// // rotate the phy obj by adding to the current rotation
// void phy_obj::increment_rotation(float inc_amount)
// {
//     rotate_wireframe(this->angle + inc_amount);
// }