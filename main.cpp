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
    // map.load_textures("assets\\ground_20.png", "assets\\sky_20.png");
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
        // if (IsKeyDown(KEY_D))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_position({5, 0});
        //     }
        // }
        // else if (IsKeyDown(KEY_A))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_position({-5, 0});
        //     }
        // }

        // if (IsKeyDown(KEY_W))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_position({0, -5});
        //     }
        // }
        // else if (IsKeyDown(KEY_S))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_position({0, +5});
        //     }
        // }

        // if (IsKeyDown(KEY_R))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_rotation(+0.1);
        //     }
        // }
        // else if (IsKeyDown(KEY_Q))
        // {
        //     for (int i = 0; i < total_objs; i++)
        //     {
        //         objects_list[i]->increment_rotation(-0.1);
        //     }
        // }

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

        // 10 physics iterations per frame
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < total_objs; i++)
            {
                // gravity
                objects_list[i]->acceleration.y += 10.0f;

                objects_list[i]->velocity.x += objects_list[i]->acceleration.x * GetFrameTime();
                objects_list[i]->velocity.y += objects_list[i]->acceleration.y * GetFrameTime();

                // std::cout << "acc.y: " << objects_list[i]->acceleration.y << std::endl;
                // std::cout << "vel.y: " << objects_list[i]->velocity.y << std::endl;

                objects_list[i]->position.x += objects_list[i]->velocity.x * GetFrameTime();
                objects_list[i]->position.y += objects_list[i]->velocity.y * GetFrameTime();

                // reset gravity so it becomes constant
                objects_list[i]->acceleration = {0, 0};
                objects_list[i]->is_stable = false;

                float v_angle = atan2f(objects_list[i]->velocity.y, objects_list[i]->velocity.x);
                float sc_start_angle = v_angle + (PI / 2.0);
                float sc_end_angle = v_angle - (PI / 2.0);

                Vector2 response{0, 0};

                // sc_start_angle += 10 degree each iteration
                // so 180/10 = 18 points on the semi circle?
                // TODO: VERIFY
                // loop will run approx 18 times?

                bool col = false;
                for (; sc_start_angle <= sc_end_angle; sc_start_angle += 0.17453)
                {
                    Vector2 collision_point{objects_list[i]->radius * cosf(sc_start_angle), objects_list[i]->radius * sinf(sc_start_angle)};
                    // translation necessary cause currently collision_point are centered about (0,0)
                    collision_point.x += objects_list[i]->position.x;
                    collision_point.y += objects_list[i]->position.y;

                    // now we can directly check with the map
                    // check if collision with between the collision_point and the map has occurred

                    // TODO: map out of bounds check !!!
                    int x = collision_point.x;
                    int y = collision_point.y;
                    // if there is something other than 'S' in the map then yes collision has occured
                    if (mapp.map_grid[x][y] != 'S')
                    {
                        response.x += collision_point.x;
                        response.y += collision_point.y;

                        col = true;
                    }
                }

                if (col == true)
                {
                    // invert the response vector
                    response.x *= -1;
                    response.y *= -1;

                    // calculate normal collision plane
                    float r_angle = atan2f(response.y, response.x);
                    float normal_angle = r_angle + (PI / 2.0);

                    objects_list[i]->is_stable = true;

                    // Calculate magnitudes of response and velocity vectors
                    float fMagVelocity = sqrtf(objects_list[i]->velocity.x * objects_list[i]->velocity.x + objects_list[i]->velocity.y * objects_list[i]->velocity.y);
                    float fMagResponse = sqrtf(response.x * response.x + response.y * response.y);

                    // Calculate reflection vector of objects velocity vector, using response vector as normal
                    float dot = objects_list[i]->velocity.x * (response.x / fMagResponse) + objects_list[i]->velocity.y * (response.y / fMagResponse);

                    // Use friction coefficient to dampen response (approximating energy loss)
                    objects_list[i]->velocity.x = (-2.0f * dot * (response.x / fMagResponse) + objects_list[i]->velocity.x);
                    objects_list[i]->velocity.y = (-2.0f * dot * (response.y / fMagResponse) + objects_list[i]->velocity.y);
                }
            }
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

        EndDrawing();

        std::cout << GetFPS() << std::endl;
        // Vector2 mouse_pos = GetMousePosition();
        // std::cout << "Mouse position: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
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