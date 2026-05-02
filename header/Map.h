#pragma once
#include "raylib.h"

class map
{
private:
    int tile_width;

    //if map width = 10 then 100x60 map 
    //if map width = 20 then 50x30  map
    int map_width; 
    int map_height;
    char **map_grid;

    Texture2D ground;
    Texture2D sky;

public:
    map(int tile_width, int width, int height);
    void load_textures(const char *ground_texture, const char *sky_texture);
    void draw() const;
    ~map();
};

void map::load_textures(const char *ground_texture, const char *sky_texture)
{
    ground = LoadTexture(ground_texture);
    sky = LoadTexture(sky_texture);
}

void map::draw() const
{
    for (int map_x = 0; map_x < map_width; map_x++)
    {
        for (int map_y = 0; map_y < map_height; map_y++)
        {
            int x = map_x * tile_width;
            int y = map_y * tile_width;

            //DrawRectangleLines(x, y, tile_width, tile_width, BLACK);

            if (map_grid[map_x][map_y] == 'G')
            {
                DrawTexture(ground, x, y, WHITE);
            }
            else if (map_grid[map_x][map_y] == 'S')
            {
                DrawTexture(sky, x, y, WHITE);
            }
        }
    }
}

map::map(int tile_width, int screen_width, int screen_height) : tile_width{tile_width}, map_width{screen_width / tile_width}, map_height{screen_height / tile_width}
{
    // allocate map 2D array dynamically
    // map [x][y] where x = horizontal point, y =vertical point
    map_grid = new char *[map_width]{0};
    for (int i = 0; i < map_width; i++)
    {
        map_grid[i] = new char[map_height]{0};
    }

    for (int x = 0; x < map_width; x++)
    {
        for (int y = 0; y < map_height; y++)
        {
            // TODO: terrain generations perlin noise?
            //50x30 keep in mind the x,y are in map coordinates not pixel coordinates
            if (y <= 20)
                map_grid[x][y] = 'S'; // S for sky
            else
                map_grid[x][y] = 'G'; // G for ground
        }
    }
}

map::~map()
{
    UnloadTexture(ground);
    UnloadTexture(sky);
    
    // deallocate map 2D array first delete the inner most memory then then outermost
    for (int i = 0; i < map_width; i++)
    {
        delete[] map_grid[i];
    }
    delete[] map_grid;

}
