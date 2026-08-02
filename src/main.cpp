#include "game.h"

int main()
{
    int screen_width = 1000;
    int screen_height = 600;
    const char *window_title = "tank wars shitty clone";

    game g(screen_width, screen_height, window_title);
    g.game_loop(&g);

    //  system("pause");
    return 0;
}
