#include "header/raylib.h"
#include "header/map.h"
#include "header/dummy.h"
#include <iostream>

int main()
{

    constexpr int SCREEN_WIDTH = 1000;
    constexpr int SCREEN_HEIGHT = 600;

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Worms shitty clone");
    // WARNING NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    map mapp(10, SCREEN_WIDTH, SCREEN_HEIGHT);
    //map.load_textures("assets\\ground_20.png", "assets\\sky_20.png");
    mapp.load_textures("assets\\ground.png", "assets\\sky.png");

    phy_obj **objects_list = nullptr;
    int total_objs = 0;
    int max_size = 0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
        //  Updates
        //----------------------------------------------------------------------------------

        //-------------------------------------input checks start
        if (IsKeyDown(KEY_D))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_position({5, 0});
            }
        }
        else if (IsKeyDown(KEY_A))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_position({-5, 0});
            }
        }

        if (IsKeyDown(KEY_W))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_position({0, -5});
            }
        }
        else if (IsKeyDown(KEY_S))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_position({0, +5});
            }
        }

        if (IsKeyDown(KEY_R))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_rotation(+0.1);
            }
        }
        else if (IsKeyDown(KEY_Q))
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->increment_rotation(-0.1);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // float rot = 0;
            // std::cout<<"Enter rotation angle in degree: ";
            // std::cin>>rot;

            dummy *created_dummy = new dummy(GetMousePosition(), 30, 0.0);
            std::cout << "Created dummy object\n";

            if (total_objs + 1 > max_size)
            {
                if (max_size == 0)
                {
                    max_size = 1;
                }

                // make a new list greater that is double the previous size
                phy_obj **obj_list_new = new phy_obj *[max_size * 2]
                { nullptr };

                // copy the old list
                for (int i = 0; i < total_objs; i++)
                {
                    obj_list_new[i] = objects_list[i];
                }
                obj_list_new[total_objs] = created_dummy;

                // delete the dynamic pointers of old list
                if (objects_list != nullptr)
                {
                    delete[] objects_list;
                }

                // update the old list
                max_size *= 2;
                total_objs++;
                objects_list = obj_list_new;

                std::cout << "Allocated new list of size " << max_size << std::endl;
            }
            else
            {
                // no need to increment the list directly append the list
                objects_list[total_objs] = created_dummy;
                total_objs++;

                std::cout << "Only appended the list new index = " << total_objs << std::endl;
            }
        }
        //-------------------------------------input check end---------------

        //---------------------------apply physics start---------------------------

        for (int i = 0; i < total_objs; i++)
        {
            //apply forces to acceleration
            objects_list[i]->acceleration.y += 2.0f;

            objects_list[i]->velocity.x += objects_list[i]->acceleration.x *GetFrameTime();
            objects_list[i]->velocity.y += objects_list[i]->acceleration.y *GetFrameTime();

            objects_list[i]->position.x += objects_list[i]->velocity.x *GetFrameTime();
            objects_list[i]->position.y += objects_list[i]->velocity.y *GetFrameTime();

        }
        

        //---------------------------apply physics end---------------------------
    
        //  Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapp.draw();

    

        for (int i = 0; i < total_objs; i++)
        {
            objects_list[i]->draw();
        }

        //DrawPolyLinesEx({504,503},6,30,2,4,BLACK);
        

        EndDrawing();

        //std::cout << GetFPS() << std::endl;
        Vector2 mouse_pos = GetMousePosition();
        std::cout << "Mouse position: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
    }

    if (objects_list != nullptr)
    {
        // WARNING DON'T do delete[] *objects_list;
        // cause dummy obj were made with new not new[]
        for (int i = 0; i < total_objs; i++)
        {
            delete objects_list[i];
        }

        // now delete the dynamic pointer array
        delete[] objects_list;
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    // system("pause");
    return 0;
}