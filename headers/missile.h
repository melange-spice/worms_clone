#pragma once
#include "phy_obj.h"
#include "raylib.h"

class missile : public phy_obj
{
    Texture2D missile_texture{};

public:
    missile(Vector2 position, float radius, const char *missile_texture);
    ~missile();
    void draw();
    void draw_debug();
};