#pragma once
#include "phy_obj.h"
#include "raylib.h"

class dummy : public phy_obj
{

public:
    dummy(Vector2 position, float radius, float angle);

    void draw() const;
};

dummy::dummy(Vector2 position, float radius, float angle) : phy_obj(position, radius, angle)
{
}

void dummy::draw() const
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
