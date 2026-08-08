#include "dummy.hpp"

dummy::dummy(Vector2 position, float radius) : phy_obj(position, radius)
{    
}

void dummy::draw()
{
    this->draw_debug();
}


dummy::~dummy(){
}