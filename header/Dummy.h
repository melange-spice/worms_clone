#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include <cmath>


class dummy : public phy_obj
{
    Vector2 angle_point; // terminal point of the angle

    void rotate_wireframe(float rot_angle);
    void rotate_angle(float rot_angle);

public:
    dummy(Vector2 position, float radius, float angle);

    void draw();
};

// rotate the wireframe points by the given rotation
void dummy::rotate_wireframe(float rot_angle)
{
    rotate_angle(rot_angle);

    this->angle = rot_angle;
}

// rotates the terminal point of the angle plus the points of the angle head
void dummy::rotate_angle(float rot_angle)
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

dummy::dummy(Vector2 position, float radius, float angle) : phy_obj(position, radius, angle)
{
    // initialize the angle terminal point
    // essentially equal to wire_frame_point[0]
    angle_point = {position.x + radius, position.y};

    rotate_wireframe(angle);
}

void dummy::draw()
{
    float angle = atan2f(velocity.y, velocity.x);
    rotate_angle(angle);

    // draw the circle
    DrawCircleLinesV(position, radius, BLACK);

    // draw the arrow
    DrawLineV(position, angle_point, RED);

    //draw the velocity vector
    Vector2 translated_velocity{velocity.x+position.x,velocity.y+position.y};
    DrawLineEx(position, translated_velocity, 2,ORANGE);

}
