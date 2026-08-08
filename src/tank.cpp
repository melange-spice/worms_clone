#include "headers/tank.hpp"
#include "headers/missile.hpp"
#include <cmath>

tank::tank(Vector2 position, float radius, const char *tank_texture) : phy_obj(position, radius, 0.3, -1)
{
    this->tank_texture = LoadTexture(tank_texture);
}

void tank::draw()
{
    float width = static_cast<float>(tank_texture.width);
    float height = static_cast<float>(tank_texture.height);

    // in DrawTexturePro
    // the source rect is inside the texture file
    // the dest rect gives the position and scaling on the screen
    // the vector origin is relative to dest rect
    // also the angle convention is opposite and I am going by the usual math convention
    DrawTexturePro(tank_texture, {0, 0, width, height}, {position.x, position.y, width, height}, {width / 2, height / 2}, 0, WHITE);
    draw_aimline();
}

void tank::draw_debug()
{
    phy_obj::draw_debug();

    float width = static_cast<float>(tank_texture.width);
    float height = static_cast<float>(tank_texture.height);

    // in DrawTexturePro
    // the source rect is inside the texture file
    // the dest rect gives the position and scaling on the screen
    // the vector origin is relative to dest rect
    // also the angle convention is opposite and I am going by the usual math convention
    DrawTexturePro(tank_texture, {0, 0, width, height}, {position.x, position.y, width, height}, {width / 2, height / 2}, 0, WHITE);

    // draw shooting angle
    char buffer[50] = "";
    snprintf(buffer, 50, "shooting_angle: %0.2f", shoot_angle);
    DrawText(buffer, position.x + 20, position.y + 80, 20, BLACK);
    // draw shooting position
    snprintf(buffer, 50, "shooting_position: (%.2f,%.2f)", shoot_position.x, shoot_position.y);
    DrawText(buffer, position.x + 20, position.y + 100, 20, BLACK);

    draw_aimline();
}

void tank::draw_aimline()
{
    // clamp shoot_angle
    if (shoot_angle > PI)
    {
        shoot_angle = PI;
    }
    else if (shoot_angle < 0.0f)
    {
        shoot_angle = 0.0f;
    }

    shoot_position = {radius * cosf(-1 * shoot_angle) + position.x,
                      radius * sinf(-1 * shoot_angle) + position.y};

    Vector2 aimline_endpoint{shoot_position.x + 20 * cosf(-1 * shoot_angle),
                             shoot_position.y + 20 * sinf(-1 * shoot_angle)};
    DrawLineEx(shoot_position, aimline_endpoint, 2, BLACK);
}

tank::~tank()
{
    UnloadTexture(tank_texture);
}

void tank::shoot_missile(phy_engine *engine, Vector2 power)
{
    missile *created_missile = nullptr;

    Vector2 velocity_missile = {cosf(-1 * shoot_angle)*power.x,
                                sinf(-1 * shoot_angle)*power.y};


    created_missile = new missile(shoot_position, velocity_missile, 10, "assets/missile1.png");

    engine->insertAtTail(created_missile);
}