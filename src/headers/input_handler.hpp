class game;   // forward declartion so compiler can stop bitching

#pragma once
#include "game.hpp"


class input_handler
{
    void output_map_file(map *mapp);
    void map_grid_toggle(map *mapp);
    void debug_display_toggle(bool& display_debug_toogle);
    void game_pause();
    void manual_explosion(phy_engine* engine,map *mapp);
    
    void create_dummy(phy_engine* engine);
    void create_debris(phy_engine* engine, int num_debris);
    void create_missile(phy_engine* engine, const char* missile_texture);
    tank* create_tank(phy_engine *engine, const char *tank_texture);
    
    void player_movement(tank* player);
    void player_aim(tank* player);
    void player_shoot(tank *player, phy_engine *engine, char *buffer);

public:
    void handle_input(game* gamee);
};
