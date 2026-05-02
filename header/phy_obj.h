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

    // each physics object is made up of 10 points
    static const int num_points = 10;
    Vector2 wireframe_points[num_points];

    Vector2 angle_point; // terminal point of the angle

    float angle; 
    float radius;
    bool is_stable;

    void transform_wireframe(Vector2 new_position);
    void rotate_wireframe(float rot_angle);
    void rotate_angle(float rot_angle);

public:
    phy_obj(Vector2 position, float radius, float angle, Vector2 velocity = {0, 0}, Vector2 acceleration = {0, 0});

    void set_position(Vector2 new_position);
    void increment_position(Vector2 inc_amount);

    void set_angle(float rot_angle);
    void increment_rotation(float inc_amount);

    virtual void draw() const = 0;
    virtual ~phy_obj() = default;
};

// rotates the terminal point of the angle plus the points of the angle head
void phy_obj::rotate_angle(float rot_angle)
{
    // workout the terminal point of the angle for the current rotation
    int x = radius * cosf(rot_angle);
    int y = radius * sinf(rot_angle);

    // translate according to the current pos
    x += position.x;
    y += position.y;

    angle_point.x = x;
    angle_point.y = y;
}

// update all the wireframe points along with the angle terminal point
void phy_obj::transform_wireframe(Vector2 new_position)
{

    // how much difference in x,y direction from the previous pos and the new pos
    int diff_x = new_position.x - position.x;
    int diff_y = new_position.y - position.y;

    for (int i = 0; i < num_points; i++)
    {
        wireframe_points[i].x += diff_x;
        wireframe_points[i].y += diff_y;
    }

    angle_point.x += diff_x;
    angle_point.y += diff_y;
}

phy_obj::phy_obj(Vector2 position, float radius, float angle, Vector2 velocity, Vector2 acceleration) : position{position}, radius{radius},
    velocity{velocity}, acceleration{acceleration}, is_stable{false}, angle{angle}
{
    // initialize the angle terminal point
    // essentially equal to wire_frame_point[0]
    angle_point = {position.x + radius, position.y};

    rotate_wireframe(angle);
}

// set a new center for the phy object directly
void phy_obj::set_position(Vector2 new_position)
{
    transform_wireframe(new_position);
    this->position = new_position;
}

// increment the current position by the given x,y amount
void phy_obj::increment_position(Vector2 inc_amount)
{

    Vector2 new_position = {position.x + inc_amount.x, position.y + inc_amount.y};
    set_position(new_position);
}

// directly set the angle of the phy obj
void phy_obj::set_angle(float rot_angle)
{
    rotate_wireframe(rot_angle);
}

// rotate the wireframe points by the given rotation
void phy_obj::rotate_wireframe(float rot_angle)
{
    // Given the center and the radius compute 10 wireframe points on the circle
    float partition_angle = 2.0 * PI / (float(num_points));
    for (int i = 0; i < num_points; i++)
    {
        // essentially implementing the formula (2pi/n)*i+theta = partition_angle*i+theta where theta is the rotation angle
        int x = radius * cosf(partition_angle * i + rot_angle);
        int y = radius * sinf(partition_angle * i + rot_angle);

        // now compute the coordinate transformation
        x += position.x;
        y += position.y;

        wireframe_points[i].x = x;
        wireframe_points[i].y = y;
    }

    rotate_angle(rot_angle);

    this->angle = rot_angle;
}

// rotate the phy obj by adding to the current rotation
void phy_obj::increment_rotation(float inc_amount)
{
    rotate_wireframe(this->angle + inc_amount);
}