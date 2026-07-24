#include "debris.h"

// assign random velocity components to a debris object
void debris::random_velocity()
{
    // TODO: implement C++ 11 random
    constexpr int x_limit = 30;
    constexpr int y_limit = 30;

    int rx = rand() % x_limit;
    int ry = rand() % y_limit;

    // distribute over -ve and +ve
    if (rx < 15)
    {
        rx *= -1;
    }

    if (ry < 15)
    {
        ry *= -1;
    }

    this->velocity.x = rx;
    this->velocity.y = ry;
}

debris::~debris()
{
}

debris::debris(Vector2 position, float radius) : phy_obj(position, radius, 0.7f, 10)
{
    // top left corner
    rec.x = radius * cosf((3 * PI) / 4) + position.x;
    rec.y = radius * sinf((3 * PI) / 4) + position.y;

    // width of the rectangle = top right corner x - top left corner x
    rec.width = (radius * cosf(PI / 4) + position.x) - rec.x;

    // height of the rectangle = top left corner y - bottom left corner y
    rec.height = rec.y - (radius * sinf((5 * PI) / 4) + position.y);

    // without this the rectangle was being drawn from the bottom left corner
    // cause of the inverted origin?
    rec.y -= rec.height;

    random_velocity();
}

void debris::draw()
{
    // translate the coordinates of the rectangle
    rec.x = radius * cosf((3 * PI) / 4) + position.x;
    rec.y = radius * sinf((3 * PI) / 4) + position.y;

    // without this the rectangle was being drawn from the bottom left corner
    // cause of the inverted origin?
    rec.y -= rec.height;

    // draw the rec
    DrawRectangleRec(rec, DARKGREEN);
}

void debris::draw_debug()
{
    phy_obj::draw_debug();

    // translate the coordinates of the rectangle
    rec.x = radius * cosf((3 * PI) / 4) + position.x;
    rec.y = radius * sinf((3 * PI) / 4) + position.y;

    // without this the rectangle was being drawn from the bottom left corner
    // cause of the inverted origin?
    rec.y -= rec.height;

    // draw the rec
    DrawRectangleRec(rec, DARKGREEN);
}