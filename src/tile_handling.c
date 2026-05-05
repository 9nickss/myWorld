/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** tile_handling
*/

#include "../include/my_world.h"

void update_selected_tile(select_t *tile, sfVector2i pos)
{
    if (pos.x != -1 && pos.y != -1) {
        tile->x = pos.x;
        tile->y = pos.y;
        tile->is_clicked = sfTrue;
    } else
        tile->is_clicked = sfFalse;
}

int handle_mouse(sfEvent event, select_t *tile)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft && tile->is_clicked)
        return 1;
    return 0;
}

static map_create_t *init_map_create(sfRenderWindow *window)
{
    map_create_t *map_create = malloc(sizeof(map_create_t));
    sfVector2u window_size;

    if (!map_create)
        return NULL;
    window_size = sfRenderWindow_getSize(window);
    map_create->centered_x = window_size.x / 2;
    map_create->centered_y = window_size.y / 4;
    return map_create;
}

static void apply_terrain_modification(game_t *game, sfVector2i tile_pos)
{
    switch (game->current_tool) {
        case RAISE:
            up_terrain(game, tile_pos.x, tile_pos.y);
            break;
        case LOWER:
            lower_terrain(game, tile_pos.x, tile_pos.y);
            break;
        case FLAT:
            flatten_terrain(game, tile_pos.x, tile_pos.y);
            break;
        default:
            break;
    }
}

static void update_mouse_state(sfEvent event, sfBool *pressed)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft)
        *pressed = sfTrue;
    if (event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft)
        *pressed = sfFalse;
}

static void process_terrain_edit(game_t *game, sfVector2i tile_pos,
    sfBool mouse_pressed, sfRenderWindow *window)
{
    if (mouse_pressed && tile_pos.x >= 0 && tile_pos.y >= 0 &&
        game->current_tool != NONE) {
        apply_terrain_modification(game, tile_pos);
        update_map_after_modification(game, window);
    }
}

int handle_map_events(sfRenderWindow *window, sfEvent event, game_t *game)
{
    static sfBool mouse_pressed = sfFalse;
    map_create_t *map_create = init_map_create(window);
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2i tile_pos;

    if (!map_create)
        return 84;
    tile_pos = get_tile_pos(mouse_pos, game->resources->map_2d,
        game->resources->map_create);
    handle_toolbar_events(window, event, game);
    update_mouse_state(event, &mouse_pressed);
    process_terrain_edit(game, tile_pos, mouse_pressed, window);
    free(map_create);
    return 0;
}
