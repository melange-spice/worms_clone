#pragma once
#include "Physics_Obj.h"
#include "raylib.h"

class Dummy:public Physics_Obj
{

public:
    Dummy(Vector2 position, float radius, float angle);
    
    void draw() const;
    
};

Dummy::Dummy(Vector2 position, float radius, float angle):Physics_Obj(position,radius,angle)
{
}


void Dummy::draw() const{

    DrawCircleLinesV(position,radius,BLACK);

    for (int i = 0; i < num_points; i++)
    {
        DrawLineV(position,wireframe_points[i],GREEN);
    }

    DrawLineV(position,angle_point,RED);
    DrawLineV(arrow_angle[0],angle_point,RED);
    DrawLineV(arrow_angle[1],angle_point,RED);
    
    
}
