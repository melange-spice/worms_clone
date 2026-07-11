#include "header/raylib.h"
#include "header/map.h"
#include "header/dummy.h"
#include "header/debris.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "header/phy_engine.h"
#include "header/missile.h"
#include "header/tank.h"

int RADIUS = 0;
int DEBUG_DISPLAY = 0;
int main()
{
    {
        constexpr int SCREEN_WIDTH = 1000;
        constexpr int SCREEN_HEIGHT = 600;

        // Initialization
        //--------------------------------------------------------------------------------------
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Worms yttihs clone");
        // WARNING NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

        map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT, "map_input.txt");
        // map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT);
        //  map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT, 'G');
        //    map.load_textures("assets\\ground_20.png", "assets\\sky_20.png");
        mapp.load_textures("assets\\ground.png", "assets\\sky.png");

        

        phy_engine engine;
        std::srand(time(nullptr)); // TODO: implement C++ 11 rcandom
        SetTargetFPS(60);          // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------
        // Main game loop

        // std::ofstream log("log");
        bool map_grid_toogle = false;
        bool display_debug_toogle = false;
        while (!WindowShouldClose()) // Detect window close button or ESC key
        {

            //  Updates
            //----------------------------------------------------------------------------------
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
            if (IsKeyPressed(KEY_P) == true)
            {
                system("pause");
            }

            if ((IsMouseButtonDown(MOUSE_BUTTON_RIGHT)))
            {
                Vector2 mouse_pos = GetMousePosition();

                int map_y = mouse_pos.y / 10;
                int map_x = mouse_pos.x / 10;

                mapp.map_grid[map_y][map_x] = 'S';
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                engine.explosion(&mapp, GetMousePosition(), RADIUS);
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
                    engine.insertAtTail(created_debris);
                }
            }

            if (IsKeyPressed(KEY_THREE))
            {
                missile *created_missile = nullptr;
                created_missile = new missile(GetMousePosition(), 10, "assets\\missile1.png");
                engine.insertAtTail(created_missile);
            }
            if (IsKeyPressed(KEY_FOUR))
            {
                tank *created_tank = nullptr;
                created_tank = new tank(GetMousePosition(), 18, "assets\\tankred.png");
                engine.insertAtTail(created_tank);
            }

            RADIUS += GetMouseWheelMove();

            if (RADIUS < 1)
            {
                RADIUS = 1;
            }

            if (IsKeyPressed(KEY_TAB) == true)
            {
                if (display_debug_toogle == true)
                {
                    display_debug_toogle = false;
                }
                else
                {
                    display_debug_toogle = true;
                }
            }

            //-------------------------------------input check end---------------
            //---------------------------apply physics start---------------------------

            // std::chrono::time_point start = std::chrono::high_resolution_clock::now();

            //   10 physics iterations per frame

            // std::cout << "total objs: " << engine.get_num_objects() << "\n";
            for (int j = 0; j < 10; j++)
            {
                engine.apply_physics(&mapp);
            }

            // std::chrono::time_point end = std::chrono::high_resolution_clock::now();
            // std::chrono::duration d = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            // std::cout << d.count() << std::endl;
            //  log << d.count() << std::endl;

            //---------------------------apply physics end---------------------------

            //  Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(RAYWHITE);

            mapp.draw(map_grid_toogle);

            if (display_debug_toogle == false)
            {
                engine.draw();
            }
            else
            {
                engine.draw_debug();
            }

            Vector2 pos = GetMousePosition();
            DrawCircleLinesV(pos, RADIUS, YELLOW);

           
           
           
            Node<phy_obj *> *tmp = engine.head;
            Vector2 dist_vec{};
            float dist = 0.0f;
            char d[60] = "this is the distance";
            while (tmp != nullptr)
            {
                phy_obj *obj = tmp->data;

                if (obj->radius >= 10)
                {
                    DrawLineEx(pos, obj->position, 1, PINK);
                    dist_vec.x = obj->position.x - pos.x;
                    dist_vec.y = obj->position.y - pos.y;

                    dist = sqrt((dist_vec.x * dist_vec.x) + (dist_vec.y * dist_vec.y));
                    snprintf(d, 60, "%f", dist);

                    DrawText(d, obj->position.x + 20, obj->position.y + 20, 15, YELLOW);
                }

                if (obj->radius == 10)
                {
                    DrawCircleLinesV(obj->position, 50, YELLOW);
                }

                tmp = tmp->next;
            }

            snprintf(d, 60, "%i", RADIUS);
            DrawText(d, pos.x + 20, pos.y, 20, YELLOW);

            EndDrawing();

            // std::cout <<"total phy_objs: "<< engine.get_num_objects() << "\n";
            //   std::cout<<GetFPS()<<std::endl;
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------

        CloseWindow(); // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
    }
    std::cout << "exit successfull\n";
    //  system("pause");
    return 0;
}