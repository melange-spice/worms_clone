#pragma once
#include "phy_engine.hpp"


class tank : public phy_obj
{
    Texture2D tank_texture{};
    
    void draw_aimline();
    

public:
    float shoot_angle = 0.0f;
    Vector2 shoot_position{};

    void shoot_missile(phy_engine* engine,Vector2 power);

    tank(Vector2 position, float radius, const char *tank_texture);
    ~tank();
    void draw() override;
    void draw_debug() override;
    
};