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