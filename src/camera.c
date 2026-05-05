/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** camera
*/

#include "../include/my_world.h"

void handle_zoom(sfEvent event, game_t *game)
{
    if (event.type != sfEvtMouseWheelScrolled)
        return;
    if (event.mouseWheelScroll.delta > 0) {
        game->zoom *= 1.1f;
        game->zoom = (game->zoom > 2.0f) ? 2.0f : game->zoom;
    } else {
        game->zoom *= 0.9f;
        game->zoom = (game->zoom < 0.1f) ? 0.1f : game->zoom;
    }
}

void move_camera(sfEvent event, game_t *game)
{
    float move_speed = 10.0f / game->zoom;

    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        game->camera_pos.x += move_speed;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        game->camera_pos.x -= move_speed;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        game->camera_pos.y += move_speed;
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        game->camera_pos.y -= move_speed;
}
