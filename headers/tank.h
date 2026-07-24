#pragma once
#include "phy_obj.h"
#include "raylib.h"

class tank : public phy_obj
{
    Texture2D tank_texture{};
    Rectangle texture_rec{}; 

public:
    tank(Vector2 position, float radius, const char *tank_texture);
    ~tank();
    void draw();
    void draw_debug();
};