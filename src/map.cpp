#include "headers/map.hpp"
#include <fstream>

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

                change_grid({map_x, map_y}, replace);
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
    clamp(coordinate);
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

int map::get_tile_width()
{
    return tile_width;
}

// return the map character present at the given coordinate
// return 0 if coordinate out of bound
char map::access_grid(Vector2 coordinate)
{
    clamp(coordinate);
    return map_grid[int(coordinate.y)][int(coordinate.x)];
}

// clamp the coordinate within the dimensions of the map, i.e., map_width, map_height
void map::clamp(Vector2 &coordinate)
{
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
}