#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include <cmath>


class debris : public phy_obj
{
    Vector2 angle_point; // terminal point of the angle

    // void transform_wireframe(Vector2 new_position);
    void rotate_wireframe(float rot_angle);
    void rotate_angle(float rot_angle);

public:
    debris(Vector2 position, float radius, float angle);

    // void set_position(Vector2 new_position);
    void draw();
};

// rotate the wireframe points by the given rotation
void debris::rotate_wireframe(float rot_angle)
{
    rotate_angle(rot_angle);

    this->angle = rot_angle;
}

// rotates the terminal point of the angle plus the points of the angle head
void debris::rotate_angle(float rot_angle)
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

debris::debris(Vector2 position, float radius, float angle) : phy_obj(position, radius, angle)
{
    // initialize the angle terminal point
    // essentially equal to wire_frame_point[0]
    angle_point = {position.x + radius, position.y};

    rotate_wireframe(angle);
}

void debris::draw()
{
    float angle = atan2f(velocity.y, velocity.x);
    rotate_angle(angle);

    //the center of the debri's phy_obj would be meeting point of the diagonals
    //of the rectangle of debris
    Rectangle rec;

    //top left corner
    rec.x = radius*cosf((3*PI)/4)+position.x;
    rec.y = radius*sinf((3*PI)/4)+position.y;
    
    //width of the rectangle = top right corner x - top left corner x
    rec.width = (radius*cosf(PI/4)+position.x)-rec.x;

    //height of the rectangle = top left corner y - bottom left corner y
    rec.height = rec.y-(radius*sinf((5*PI)/4)+position.y);

    //without this the rectangle was being drawn from the bottom left corner
    //cause of the inverted origin? 
    rec.y -= rec.height;

    //draw the rec
    DrawRectangleRec(rec,DARKGREEN);
    //DrawRectangleLinesEx(rec,2,PINK);
    //DrawRectangleLinesEx(rec,2,PINK);

    // draw the circle
    //DrawCircleLinesV(position, radius, BLACK);

    // draw the arrow
    //DrawLineV(position, angle_point, RED);

    //draw the velocity vector
    //Vector2 translated_velocity{velocity.x+position.x,velocity.y+position.y};
    //DrawLineEx(position, translated_velocity, 2,ORANGE);

    
}
