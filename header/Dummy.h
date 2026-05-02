#pragma once
#include "Physics_Obj.h"
#include "raylib.h"

class Dummy : public Physics_Obj
{

public:
    Dummy(Vector2 position, float radius, float angle);

    void draw() const;
};

Dummy::Dummy(Vector2 position, float radius, float angle) : Physics_Obj(position, radius, angle)
{
}

void Dummy::draw() const
{

    // draw the circle
    DrawCircleLinesV(position, radius, BLACK);

    // draw the wireframe points on the circle
    for (int i = 0; i < num_points; i++)
    {
        DrawLineV(position, wireframe_points[i], GREEN);
    }

    // draw the arrow
    DrawLineV(position, angle_point, RED);
}
