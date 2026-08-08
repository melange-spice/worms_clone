#include "headers/game.hpp"
#include "headers/input_handler.hpp"

game::game(int screen_width, int screen_height, const char *window_title) : mapp(10, screen_width, screen_height, "assets/map_input.txt")
{
    InitWindow(screen_width, screen_height, window_title);

    // WARNING NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    mapp.load_textures("assets/ground.png", "assets/sky.png");

    std::srand(time(nullptr)); // TODO: implement C++ 11 rcandom
    SetTargetFPS(60);          // Set our game to run at 60 frames-per-second
}

void game::game_loop()
{
    input_handler inp_handler;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        inp_handler.handle_input(this);

        for (int j = 0; j < 10; j++)
        {
            engine.apply_physics(&mapp);
        }

        draw_handler();
    }
}

void game::draw_handler()
{
    BeginDrawing();
    ClearBackground(WHITE);

    mapp.draw(map_grid_toogle);
    if (display_debug_toogle == false)
    {
        engine.draw();
    }
    else
    {
        engine.draw_debug();
    }

    DrawText(buffer, 0, 0, 20, BLACK);

    EndDrawing();
}

game::~game(){

    CloseWindow(); // Close window and OpenGL context
    std::cout << "exit successfull\n";
}