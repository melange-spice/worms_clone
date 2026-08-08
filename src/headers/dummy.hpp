#pragma once
#include "phy_obj.hpp"

class dummy : public phy_obj
{
    
public:
    dummy(Vector2 position, float radius);
    ~dummy();

    void draw() override;
};