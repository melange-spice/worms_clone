#include "header/raylib.h"
#include "header/map.h"
#include "header/dummy.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

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

    phy_obj **objects_list = nullptr;
    int total_objs = 0;
    int max_size = 0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop

    // std::ofstream log("log");

    bool map_grid_toogle = false;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        //  Updates
        //----------------------------------------------------------------------------------

        if (IsKeyDown(KEY_W) == true)
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->velocity.y -= 5.0f;
            }
        }
        if (IsKeyDown(KEY_S) == true)
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->velocity.y += 5.0f;
            }
        }
        if (IsKeyDown(KEY_D) == true)
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->velocity.x += 5.0f;
            }
        }
        if (IsKeyDown(KEY_A) == true)
        {
            for (int i = 0; i < total_objs; i++)
            {
                objects_list[i]->velocity.x -= 5.0f;
            }
        }

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
            std::cout << "Added phy obj " << total_objs << std::endl;

            // log << "Added phy obj " << total_objs << std::endl;
        }
        //-------------------------------------input check end---------------

        //---------------------------apply physics start---------------------------

        // std::chrono::time_point start = std::chrono::high_resolution_clock::now();

        std::vector<Vector2> cp;
        //  10 physics iterations per frame
        for (int j = 0; j < 10; j++)
        {

            for (int i = 0; i < total_objs; i++)
            {

                // gravity
                objects_list[i]->acceleration.y += 10.0f;

                objects_list[i]->velocity.x += objects_list[i]->acceleration.x * GetFrameTime();
                objects_list[i]->velocity.y += objects_list[i]->acceleration.y * GetFrameTime();

                // don't directly modify objects position instead use a temp variable for calculations instead
                Vector2 potential_position{objects_list[i]->position.x, objects_list[i]->position.y};
                potential_position.x += objects_list[i]->velocity.x * GetFrameTime();
                potential_position.y += objects_list[i]->velocity.y * GetFrameTime();

                // reset gravity so it becomes constant
                objects_list[i]->acceleration = {0, 0};
                objects_list[i]->is_stable = false;

                // velocity angle
                float v_angle = atan2f(objects_list[i]->velocity.y, objects_list[i]->velocity.x);

                // semi-circle start and end angles
                float sc_start_angle = v_angle + (PI / 2.0);
                float sc_end_angle = v_angle - (PI / 2.0);

                Vector2 response{0, 0};

                // sc_start_angle += 10 degree each iteration
                // so 180/10 = 18 points on the semi circle?
                // TODO: VERIFY YES
                // loop will run approx 18 times?

                bool collision_occured = false;
                for (; sc_start_angle >= sc_end_angle; sc_start_angle -= 0.17453)
                {
                    Vector2 collision_point{objects_list[i]->radius * cosf(sc_start_angle), objects_list[i]->radius * sinf(sc_start_angle)};
                    // translation necessary cause currently collision_point are centered about (0,0)
                    collision_point.x += potential_position.x;
                    collision_point.y += potential_position.y;

                    cp.push_back(collision_point);

                    // now we can directly check with the map
                    // check if collision with between the collision_point and the map has occurred

                    // TODO: map out of bounds check !!!
                    int map_x = collision_point.x / 10;
                    int map_y = collision_point.y / 10;
                    bool clamp = false;
                    // clamp x
                    if (map_x < 0)
                    {

                        map_x = 0;
                        clamp = true;
                    }
                    else if (map_x > 100)
                    {

                        map_x = 100;
                        clamp = true;
                    }

                    // clamp y
                    if (map_y < 0)
                    {

                        map_y = 0;
                        clamp = true;
                    }
                    else if (map_y > 60)
                    {

                        map_y = 60;
                        clamp = true;
                    }

                    // if there is something other than 'S' in the map then yes collision has occured
                    if (mapp.map_grid[map_y][map_x] != 'S' && clamp == false)
                    {
                        // translate again before addition to center around (0,0)
                        response.x += collision_point.x - potential_position.x;
                        response.y += collision_point.y - potential_position.y;

                        collision_occured = true;
                        // system("pause");
                    }
                    else if (clamp == true)
                    {
                        // translate again before addition to center around (0,0)
                        response.x += collision_point.x - potential_position.x;
                        response.y += collision_point.y - potential_position.y;

                        collision_occured = true;
                    }
                }
                // velocity magnitude
                float velocity_mag = sqrtf((objects_list[i]->velocity.x * objects_list[i]->velocity.x) + (objects_list[i]->velocity.y * objects_list[i]->velocity.y));

                if (collision_occured == true)
                {

                    // invert the response vector
                    response.x *= -1;
                    response.y *= -1;

                    objects_list[i]->is_stable = true;

                    // calculate normal collision plane
                    float response_angle = atan2f(response.y, response.x);
                    float normal_angle = response_angle + (PI / 2.0); //+ or minus does not matter

                    // normalize the response vector
                    float response_mag = sqrtf((response.x * response.x) + (response.y * response.y));
                    response.x = response.x / response_mag;
                    response.y = response.y / response_mag;

                    // invert the velocity vector for reflection calculations
                    objects_list[i]->velocity.x *= -1;
                    objects_list[i]->velocity.y *= -1;

                    // projection of velocity to n i.e v_parallel calculation
                    // magnitude of v_parallel
                    float dot = (objects_list[i]->velocity.x * response.x) + (objects_list[i]->velocity.y * response.y);
                    // actual v_parallet calculation
                    Vector2 v_parallel{response.x * dot, response.y * dot};

                    // v_perpendicular calculation
                    //  v - v_parallel
                    Vector2 v_perpendicular;
                    v_perpendicular.x = objects_list[i]->velocity.x - v_parallel.x;
                    v_perpendicular.y = objects_list[i]->velocity.y - v_parallel.y;

                    // invert the v_parallel
                    v_perpendicular.x *= -1;
                    v_perpendicular.y *= -1;

                    // final velocity reflection calculation
                    Vector2 v_reflection;
                    v_reflection.x = v_parallel.x + v_perpendicular.x;
                    v_reflection.y = v_parallel.y + v_perpendicular.y;

                    // friction
                    v_reflection.x *= 0.8;
                    v_reflection.y *= 0.8;

                    objects_list[i]->velocity.x = v_reflection.x;
                    objects_list[i]->velocity.y = v_reflection.y;
                }
                else
                {
                    objects_list[i]->position.x = potential_position.x;
                    objects_list[i]->position.y = potential_position.y;
                }

                if (velocity_mag < 0.1f && collision_occured == true)
                {
                    std::cout << velocity_mag << std::endl;
                    objects_list[i]->is_stable = true;
                    // objects_list[i]->velocity.x = 0;
                    // objects_list[i]->velocity.y = 0;
                }
            }
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

        for (int i = 0; i < total_objs; i++)
        {
            objects_list[i]->draw();

            for (int j = 0; j < cp.size(); j++)
            {
                // draw the velocity vector

                DrawLineEx(objects_list[i]->position, cp[j], 2, BLUE);
            }
        }

        EndDrawing();
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