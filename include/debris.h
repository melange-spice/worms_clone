#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include <cmath>
#include <random>

class debris : public phy_obj
{
    // the center of the debri's phy_obj would be meeting point of the diagonals
    // of the rectangle of debris
    Rectangle rec;

    void random_velocity();

public:
    debris(Vector2 position, float radius);

    void draw();
    void draw_debug();

    ~debris();
};