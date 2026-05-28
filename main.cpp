#include "header/raylib.h"
#include "header/map.h"
#include "header/dummy.h"
#include "header/debris.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "header/phy_engine.h"

void explosion(map *mapp, phy_engine *engine)
{
    Vector2 mouse_pos = GetMousePosition();
    int radius = 100; // radius in pixel values not in map coordinates
    float map_x = mouse_pos.x / 10;
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
                map_x = (x + mouse_pos.x) / 10;
                map_y = (y + mouse_pos.y) / 10;

                mapp->change_grid({map_x, map_y}, 'S');
            }
        }
    }

    for (int i = 0; i < 20; i++)
    {
        debris *created_debris = nullptr;
        created_debris = new debris({mouse_pos.x, mouse_pos.y}, 6);
        engine->insertAtTail(created_debris);
    }

    Node<phy_obj*> *tmp = engine->head;

    Vector2 blast_veloctity{};

    while (tmp!=nullptr)
    {
        phy_obj* obj = tmp->data;
        blast_veloctity.x = obj->position.x-mouse_pos.x;
        blast_veloctity.y = obj->position.y-mouse_pos.y;

        //find the distance sqrt{(x2-x1)^2 + (y2-y1)^2}
        float distance = sqrtf(blast_veloctity.x*blast_veloctity.x + blast_veloctity.y*blast_veloctity.y);

        if (distance-obj->radius<=radius && obj->radius==20)
        {
            blast_veloctity.x = blast_veloctity.x/distance *radius;
            blast_veloctity.y = blast_veloctity.y/distance *radius;

            obj->velocity = blast_veloctity;
        }
        


        tmp = tmp->next;
    }
    


}

int main()
{
    {
        constexpr int SCREEN_WIDTH = 1000;
        constexpr int SCREEN_HEIGHT = 600;

        // Initialization
        //--------------------------------------------------------------------------------------
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Worms yttihs clone");
        // WARNING NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

        //map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT, "map_input.txt");
        map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT);
        // map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT, 'G');
        //   map.load_textures("assets\\ground_20.png", "assets\\sky_20.png");
        mapp.load_textures("assets\\ground.png", "assets\\sky.png");

        phy_engine engine;
        std::srand(time(nullptr)); // TODO: implement C++ 11 random
        SetTargetFPS(60);          // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------
        // Main game loop

        // std::ofstream log("log");

        bool map_grid_toogle = false;
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

            if ((IsMouseButtonDown(MOUSE_BUTTON_RIGHT)))
            {
                Vector2 mouse_pos = GetMousePosition();

                int map_y = mouse_pos.y / 10;
                int map_x = mouse_pos.x / 10;

                mapp.map_grid[map_y][map_x] = 'S';
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                explosion(&mapp, &engine);
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
            engine.draw();

            DrawCircleLinesV(GetMousePosition(),100,BLACK);
            //  engine.draw_debug();

            EndDrawing();
            // std::cout<<GetFPS()<<std::endl;
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------

        CloseWindow(); // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
    }
    // std::cout << "exit successfull\n";
    //  system("pause");
    return 0;
}