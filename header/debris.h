#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include <cmath>

class debris : public phy_obj
{
    //the center of the debri's phy_obj would be meeting point of the diagonals
    //of the rectangle of debris
    Rectangle rec;
public:
    debris(Vector2 position, float radius);

    void draw();
};


debris::debris(Vector2 position, float radius) : phy_obj(position, radius,0.7)
{
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
}

void debris::draw()
{    
    //translate the coordinates of the rectangle
    rec.x = radius*cosf((3*PI)/4)+position.x;
    rec.y = radius*sinf((3*PI)/4)+position.y;
   
    //without this the rectangle was being drawn from the bottom left corner
    //cause of the inverted origin? 
    rec.y -= rec.height;
    
    //draw the rec
    DrawRectangleRec(rec,DARKGREEN);    
}
