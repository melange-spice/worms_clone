#include "headers/input_handler.hpp"
#include "headers/dummy.hpp"
#include "headers/debris.hpp"
#include "headers/missile.hpp"

void input_handler::handle_input(game *gamee)
{

    output_map_file(&gamee->mapp);
    map_grid_toggle(&gamee->mapp);
    debug_display_toggle(gamee->display_debug_toogle);
    game_pause();
    manual_explosion(&gamee->engine, &gamee->mapp);

    create_dummy(&gamee->engine);
    create_debris(&gamee->engine, 20);
    create_missile(&gamee->engine, "assets/missile1.png");

    tank* player = create_tank(&gamee->engine, "assets/tankred.png");
    
    if (player!=nullptr )
    {
        gamee->player = player;
    }
    

    if (gamee->player != nullptr)
    {
        player_movement(gamee->player);
        player_aim(gamee->player);
        player_shoot(gamee->player, &gamee->engine, gamee->buffer);
    }
}

void input_handler::output_map_file(map *mapp)
{
    const char *file_name = "map_output.txt";

    if (IsKeyDown(KEY_M) == true)
    {
        mapp->output_map(file_name);
    }
}

void input_handler::map_grid_toggle(map *mapp)
{
    static bool map_grid_toogle = false;

    if (IsKeyPressed(KEY_N))
    {
        if (!map_grid_toogle)
        {
            map_grid_toogle = true;
        }
        else
        {
            map_grid_toogle = false;
        }
    }
}

void input_handler::game_pause()
{
    if (IsKeyPressed(KEY_P))
    {
        system("pause");
    }
}

void input_handler::manual_explosion(phy_engine *engine, map *mapp)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        engine->explosion(mapp, GetMousePosition(), 50);
    }
}

void input_handler::create_dummy(phy_engine *engine)
{
    if (IsKeyPressed(KEY_ONE))
    {
        dummy *created_dummy = nullptr;
        created_dummy = new dummy(GetMousePosition(), 20);
        engine->insertAtTail(created_dummy);
    }
}

void input_handler::create_debris(phy_engine *engine, int num_debris)
{
    if (IsKeyPressed(KEY_TWO))
    {
        for (int i = 0; i < num_debris; i++)
        {
            debris *created_debris = nullptr;
            created_debris = new debris(GetMousePosition(), 6);
            engine->insertAtTail(created_debris);
        }
    }
}

void input_handler::create_missile(phy_engine *engine, const char *missile_texture)
{
    if (IsKeyPressed(KEY_THREE))
    {
        missile *created_missile = nullptr;
        created_missile = new missile(GetMousePosition(), 10, missile_texture);
        engine->insertAtTail(created_missile);
    }
}

tank *input_handler::create_tank(phy_engine *engine, const char *tank_texture)
{
    if (IsKeyPressed(KEY_FOUR))
    {
        tank *created_tank = nullptr;
        created_tank = new tank(GetMousePosition(), 18, tank_texture);
        engine->insertAtTail(created_tank);
        return created_tank;
    }
    return nullptr;
}

void input_handler::player_movement(tank *player)
{
    if (player == nullptr)
    {
        std::cerr << "Warning: player_movement called when player = nullptr\n";
        return;
    }

    if (IsKeyDown(KEY_D))
    {
        player->velocity.x += 1.0f;
        player->velocity.y -= 1.2f;
    }
    else if (IsKeyDown(KEY_A))
    {
        player->velocity.x -= 1.0f;
        player->velocity.y -= 1.2f;
    }

    if (IsKeyDown(KEY_W))
    {
        player->velocity.y -= 5.0f;
    }
    else if (IsKeyDown(KEY_S))
    {
        player->velocity.y += 5.0f;
    }
}

void input_handler::player_aim(tank *player)
{
    if (player == nullptr)
    {
        std::cerr << "Warning: player_aim called when player = nullptr\n";
        return;
    }

    if (IsKeyDown(KEY_UP))
    {
        player->shoot_angle += 0.1f;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        player->shoot_angle -= 0.1f;
    }
}

void input_handler::player_shoot(tank *player, phy_engine *engine, char *buffer)
{
    if (player == nullptr)
    {
        std::cerr << "Warning: player_shoot called when player = nullptr\n";
        return;
    }

    static Vector2 power{};
    if (IsKeyDown(KEY_SPACE))
    {
        power.x++;
        power.y++;
        sprintf(buffer, "power: %d", static_cast<int>(power.x));
    }
    if (IsKeyReleased(KEY_SPACE))
    {
        if (player != nullptr)
        {
            player->shoot_missile(engine, power);
        }

        power = {0.0f, 0.0f};
    }
}

void input_handler::debug_display_toggle(bool &display_debug_toogle)
{
    if (IsKeyPressed(KEY_TAB) == true)
    {
        if (display_debug_toogle)
        {
            display_debug_toogle = false;
        }
        else
        {
            display_debug_toogle = true;
        }
    }
}