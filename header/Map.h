#pragma once
#include "raylib.h"
#include <iostream>
#include <fstream>

class map
{
public:
    int tile_width;

    // if tile_width = 10 then 100x60 map
    // if tile_width = 20 then 50x30  map
    int map_width;
    int map_height;
    char **map_grid;

    Texture2D ground;
    Texture2D sky;

public:
    map(int tile_width, int width, int height, char fill);
    map(int tile_width, int width, int height, const char *input_map_file);
    map(int tile_width, int width, int height);

    void load_textures(const char *ground_texture, const char *sky_texture);
    void draw(bool with_lines) const;
    void change_grid(Vector2 coordinate, char value);

    // given pixel position and radius replace all the map tiles within
    // the circle with the given replace char
    void make_circle(Vector2 position, int radius, char replace = 'S');

    // dumps the map_grid to the file given
    void output_map(const char *file_name);
    ~map();
};

void map::make_circle(Vector2 position, int radius, char replace)
{
    float map_x = position.x / tile_width;
    float map_y = 0;

    for (int y = radius * -1; y <= radius; y++)
    {
        for (int x = radius * -1; x <= radius; x++)
        {
            // x^2+y^2 = r^2 check equation of circle
            if ((x * x) + (y * y) <= (radius * radius))
            {
                // transform the pixel coordinates according to the mouse pos
                // and then convert the pixel coordinates to map_coordinates
                map_x = (x + position.x) / 10;
                map_y = (y + position.y) / 10;

                change_grid({map_x,map_y},replace);
            }
        }
    }
}

// initialize the map with level ground
map::map(int tile_width, int width, int height) : tile_width{tile_width}, map_width{width / tile_width}, map_height{height / tile_width}
{
    map_grid = new char *[map_height]{0};
    for (int i = 0; i < map_height; i++)
    {
        map_grid[i] = new char[map_width]{0};
    }

    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {
            if (y > 40)
            {
                map_grid[y][x] = 'G';
            }
            else
            {
                map_grid[y][x] = 'S';
            }
        }
    }
}

// given the coordinate put the value in map_grid
// automatically clamp the coordinate if out of bound
// assuming coordinate is already in map coordinate format and not in pixel coordinates
void map::change_grid(Vector2 coordinate, char value)
{
    // check for out of bound
    //  x coordinate check
    if (coordinate.x < 0)
    {
        coordinate.x = 0;
    }
    else if (coordinate.x >= map_width)
    {
        coordinate.x = map_width - 1; // 0 based indexing in map_grid
    }

    // y coordinate check
    if (coordinate.y < 0)
    {
        coordinate.y = 0;
    }
    else if (coordinate.y >= map_height)
    {
        coordinate.y = map_height - 1; // 0 based indexing in map_grid
    }

    map_grid[int(coordinate.y)][int(coordinate.x)] = value;
}

void map::output_map(const char *file_name)
{

    std::ofstream output_file(file_name);

    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {
            output_file << map_grid[y][x];
        }
        output_file << std::endl;
    }
}

map::map(int tile_width, int screen_width, int screen_height, const char *input_map_file) : tile_width{tile_width}, map_width{screen_width / tile_width}, map_height{screen_height / tile_width}
{

    map_grid = new char *[map_height]{0};
    for (int i = 0; i < map_height; i++)
    {
        map_grid[i] = new char[map_width]{0};
    }

    std::ifstream map_file(input_map_file);
    char terrain = '\0';

    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {
            // TODO: terrain generations perlin noise?
            // 50x30 keep in mind the x,y are in map coordinates not pixel coordinates
            map_file >> terrain;
            map_grid[y][x] = terrain;
        }
    }

    map_file.close();
}

void map::load_textures(const char *ground_texture, const char *sky_texture)
{
    ground = LoadTexture(ground_texture);
    sky = LoadTexture(sky_texture);
}

// if with_lines ==true then draw map_grid
void map::draw(bool with_lines) const
{
    for (int map_y = 0; map_y < map_height; map_y++)
    {
        for (int map_x = 0; map_x < map_width; map_x++)
        {
            int x = map_x * tile_width;
            int y = map_y * tile_width;

            if (map_grid[map_y][map_x] == 'G')
            {
                DrawTexture(ground, x, y, WHITE);
            }
            else if (map_grid[map_y][map_x] == 'S')
            {
                DrawTexture(sky, x, y, WHITE);
            }

            if (with_lines) // map grid
            {
                DrawRectangleLines(x, y, tile_width, tile_width, BLACK);
            }
        }
    }
}

// initialize the map with the given fill character
map::map(int tile_width, int screen_width, int screen_height, char fill) : tile_width{tile_width}, map_width{screen_width / tile_width}, map_height{screen_height / tile_width}
{
    map_grid = new char *[map_height]{0};
    for (int i = 0; i < map_height; i++)
    {
        map_grid[i] = new char[map_width]{0};
    }

    for (int y = 0; y < map_height; y++)
    {
        for (int x = 0; x < map_width; x++)
        {

            map_grid[y][x] = fill;
        }
    }
}

map::~map()
{
    UnloadTexture(ground);
    UnloadTexture(sky);

    // deallocate map 2D array first delete the inner most memory then then outermost
    for (int i = 0; i < map_height; i++)
    {
        delete[] map_grid[i];
    }
    delete[] map_grid;
}
