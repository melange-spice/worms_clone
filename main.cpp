#include "header/raylib.h"
#include "header/map.h"
#include "header/dummy.h"
#include "header/debris.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "header/phy_engine.h"

int main()
{

    constexpr int SCREEN_WIDTH = 1000;
    constexpr int SCREEN_HEIGHT = 600;

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Worms shitty clone");
    // WARNING NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT);
    map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT, "map_input.txt");
    // map.load_textures("assets\\ground_20.png", "assets\\sky_20.png");
    mapp.load_textures("assets\\ground.png", "assets\\sky.png");

    // TODO: from here
    // myLL<phy_obj*> objects_list;

    phy_engine engine;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop

    // std::ofstream log("log");

    bool map_grid_toogle = false;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        //  Updates
        //----------------------------------------------------------------------------------

        // if (IsKeyDown(KEY_W) == true)
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->velocity.y -= 5.0f;
        //     }
        // }
        // if (IsKeyDown(KEY_S) == true)
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->velocity.y += 5.0f;
        //     }
        // }
        // if (IsKeyDown(KEY_D) == true)
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->velocity.x += 5.0f;
        //     }
        // }
        // if (IsKeyDown(KEY_A) == true)
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->velocity.x -= 5.0f;
        //     }
        // }

        if (IsKeyDown(KEY_M) == true)
        {
            mapp.output_map("map_output.txt");
        }
        if (IsKeyPressed(KEY_N) == true)
        {
            if (map_grid_toogle == false)
            {
                map_grid_toogle = true;
            }
            else
            {
                map_grid_toogle = false;
            }
        }

        if ((IsMouseButtonDown(MOUSE_BUTTON_RIGHT)))
        {
            Vector2 mouse_pos = GetMousePosition();

            int map_y = mouse_pos.y / 10;
            int map_x = mouse_pos.x / 10;

            mapp.map_grid[map_y][map_x] = 'S';
        }

        if (IsKeyPressed(KEY_ONE))
        {
            dummy *created_dummy = nullptr;
            created_dummy = new dummy(GetMousePosition(), 20);
            engine.insertAtTail(created_dummy);
        }

        if (IsKeyPressed(KEY_TWO))
        {
            for (int i = 0; i < 20; i++)
            {
                debris *created_debris = nullptr;

                created_debris = new debris(GetMousePosition(), 6);

                std::time_t result = std::time(nullptr);

                int rx = rand() % 30;
                int ry = rand() % 30;

                if (rx < 15)
                {
                    rx *= -1;
                }

                if (ry < 15)
                {
                    ry *= -1;
                }

                float x = rx;
                float y = ry;

                created_debris->velocity.x = x;
                created_debris->velocity.y = y;

                std::cout << "->\tx,y: " << x << ", " << y << std::endl;
                engine.insertAtTail(created_debris);
            }
        }
        //-------------------------------------input check end---------------
        std::cout << "total number of phy objects: " << engine.get_num_objects() << std::endl;
        //---------------------------apply physics start---------------------------

        //std::chrono::time_point start = std::chrono::high_resolution_clock::now();

        //   10 physics iterations per frame
        for (int j = 0; j < 10; j++)
        {
            engine.apply_physics(&mapp);
        }

        // std::chrono::time_point end = std::chrono::high_resolution_clock::now();
        // std::chrono::duration d = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        // std::cout << d.count() << std::endl;
        // log << d.count() << std::endl;

        //---------------------------apply physics end---------------------------

        //  Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapp.draw(map_grid_toogle);

        engine.draw();
        //engine.draw_debug();

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}