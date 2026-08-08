#include "headers/missile.hpp"
#include <cmath>

missile::missile(Vector2 position, float radius, const char *missile_texture) : phy_obj(position, radius, 1)
{
    this->missile_texture = LoadTexture(missile_texture);
}

missile::missile(Vector2 position, Vector2 velocity, float radius, const char *missile_texture) : phy_obj(position, velocity, radius, 1)
{
    this->missile_texture = LoadTexture(missile_texture);
}

void missile::draw()
{
    float angle = atan2f(velocity.y, velocity.x);
    angle *= -1 * 180.0 / PI; //-1 for the usual math convention

    float width = static_cast<float>(missile_texture.width);
    float height = static_cast<float>(missile_texture.height);

    // in DrawTexturePro
    // the source rect is inside the texture file
    // the dest rect gives the position and scaling on the screen
    // the vector origin is relative to dest rect
    // also the angle convention is opposite and I am going by the usual math convention
    DrawTexturePro(missile_texture, {0, 0, width, height}, {position.x, position.y, width, height}, {width / 2, height / 2}, -angle, WHITE);
}

void missile::draw_debug()
{
    phy_obj::draw_debug();
    float angle = atan2f(velocity.y, velocity.x);
    angle *= -1 * 180.0 / PI; //-1 for the usual math convention

    float width = static_cast<float>(missile_texture.width);
    float height = static_cast<float>(missile_texture.height);

    // in DrawTexturePro
    // the source rect is inside the texture file
    // the dest rect gives the position and scaling on the screen
    // the vector origin is relative to dest rect
    // also the angle convention is opposite and I am going by the usual math convention
    DrawTexturePro(missile_texture, {0, 0, width, height}, {position.x, position.y, width, height}, {width / 2, height / 2}, -angle, WHITE);
}

missile::~missile()
{
    UnloadTexture(missile_texture);
}