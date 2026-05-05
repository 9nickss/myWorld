/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** main
*/

#include "../include/my_world.h"

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_world [OPTIONS]\n\n");
    printf("DESCRIPTION\n");
    printf("    A terraformer program allowing you to edit a 3D map.\n\n");
    printf("OPTIONS\n");
    printf("    -h                  Display this help message\n\n");
    printf("CONTROLS\n");
    printf("    ESC                 Toggle help menu / Exit program\n");
    printf("    T                   Toggle textures on/off\n");
    printf("    Arrow Keys          Move camera around the map\n");
    printf("    Mouse Wheel         Zoom in/out\n\n");
    printf("TOOLS\n");
    printf("    UP                  Raise terrain\n");
    printf("    LOW                 Lower terrain\n");
    printf("    FLAT                Flatten terrain\n");
    printf("    +/-                 Adjust brush size\n");
}

int main(int argc, char **argv)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;
    sfEvent event;
    int result = 0;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    window = sfRenderWindow_create(mode, "MyWorld",
        sfDefaultStyle, NULL);
    if (!window)
        return 84;
    result = run_world(window, event);
    sfRenderWindow_destroy(window);
    return result;
}
