#include "headers/game.hpp"

int main()
{
    constexpr int screen_width = 1000;
    constexpr int screen_height = 600;
    const char *window_title = "tank wars shitty clone";

    game g(screen_width, screen_height, window_title);
    g.game_loop();

    //  system("pause");
    return 0;
}
