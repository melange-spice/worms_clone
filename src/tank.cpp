#include "tank.h"

tank::tank(Vector2 position, float radius, const char *tank_texture) : phy_obj(position, radius, 0.3, -1)
{
    this->tank_texture = LoadTexture(tank_texture);

    // rectangle with the same dimension as the given texture object
    texture_rec.width = this->tank_texture.width;
    texture_rec.height = this->tank_texture.height;
}

void tank::draw()
{
    // translate the coordinates of the rectangle
    texture_rec.x = radius * cosf((3 * PI) / 4) + position.x;
    texture_rec.y = radius * sinf((3 * PI) / 4) + position.y;

    { // change in y between texture_rec's  top left point and bottom left point of the circumscribed rectangle
        float bottom_left_y = radius * sinf((5 * PI) / 4) + position.y;
        float dy = texture_rec.y - bottom_left_y;

        // without this the rectangle was being drawn from the bottom left corner
        // cause of the inverted origin?
        texture_rec.y -= dy;
    }

    // center point of the rectangle texture_rec
    Vector2 texture_center{};
    texture_center.x = texture_rec.x + (texture_rec.width / 2.0f);
    texture_center.y = texture_rec.y + (texture_rec.height / 2.0f);

    // distance between texture_center and center of phy object
    float dx = position.x - texture_center.x;
    float dy = position.y - texture_center.y;

    texture_rec.x += dx;
    texture_rec.y += dy;

    DrawTextureEx(tank_texture, {texture_rec.x, texture_rec.y}, 0, 1, WHITE);
}

void tank::draw_debug()
{
    phy_obj::draw_debug();
    // float angle = atan2f(-1*velocity.y,velocity.x);
    // angle *= 180.0/PI;
    // std::cout<<velocity.y<<", "<<velocity.x<<"\t \t"<<angle<<"\n";

    // translate the coordinates of the rectangle
    texture_rec.x = radius * cosf((3 * PI) / 4) + position.x;
    texture_rec.y = radius * sinf((3 * PI) / 4) + position.y;

    { // change in y between top left and bottom left point
        float bottom_left_y = radius * sinf((5 * PI) / 4) + position.y;
        float dy = texture_rec.y - bottom_left_y; // essentially the height of the rectangle

        // without this the rectangle was being drawn from the bottom left corner
        // cause of the inverted origin?
        texture_rec.y -= dy;
    }

    // center point of the rectangle texture_rec
    Vector2 texture_center{};
    texture_center.x = texture_rec.x + (texture_rec.width / 2.0f);
    texture_center.y = texture_rec.y + (texture_rec.height / 2.0f);

    // distance between texture_center and center of phy object
    float dx = position.x - texture_center.x;
    float dy = position.y - texture_center.y;

    texture_rec.x += dx;
    texture_rec.y += dy;

    DrawTextureEx(tank_texture, {texture_rec.x, texture_rec.y}, 0, 1, WHITE);
    DrawRectangleLinesEx(texture_rec, 1, BLACK);
}

tank::~tank()
{
    UnloadTexture(tank_texture);
}