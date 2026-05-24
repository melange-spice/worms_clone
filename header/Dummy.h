#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include <cmath>

class dummy : public phy_obj
{
    
public:
    dummy(Vector2 position, float radius);
    ~dummy();
    void draw();
};



dummy::dummy(Vector2 position, float radius) : phy_obj(position, radius)
{
}

void dummy::draw()
{
    this->draw_debug();
}


dummy::~dummy(){
}