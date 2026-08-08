#pragma once
#include "phy_engine.hpp"
#include "tank.hpp"


class game
{
public:
    map mapp;
    phy_engine engine;

    // temporary junk
    bool map_grid_toogle = false;
    bool display_debug_toogle = false;

    tank *player = nullptr;

    char buffer[50] = "";
    //-------------------------------------------------

    enum class state
    {
        initial,
        input,
        physics,
        draw

    };

    state current_state = state::initial;
    state next_state = state::input;


    void draw_handler();

public:
    // game initialization
    game(int screen_width, int screen_height, const char *window_title);

    void game_loop();

    ~game();
};
