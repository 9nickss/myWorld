/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** event_handling.c
*/

#include "../include/my_world.h"

int handle_menu_events(sfRenderWindow *window, menu_t *menu, sfEvent event,
    game_t *game)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    update_button_state(menu->play_button, mouse_pos, game);
    update_button_state(menu->quit_button, mouse_pos, game);
    if (event.type == sfEvtMouseButtonPressed &&
    event.mouseButton.button == sfMouseLeft) {
        if (menu->play_button->is_hover == sfTrue) {
            menu->play_button->is_clicked = sfTrue;
            sfMusic_play(game->resources->sounds->click_sound);
            return 1;
        }
        if (menu->quit_button->is_hover == sfTrue) {
            menu->quit_button->is_clicked = sfTrue;
            sfMusic_play(game->resources->sounds->click_sound);
            return 2;
        }
    }
    return 0;
}

static int check_help_key(sfRenderWindow *window, sfEvent event, game_t *game)
{
    if (event.key.code == sfKeyEscape && game->menu->game_state == GAME) {
        game->show_help = (game->show_help == sfFalse) ? sfTrue : sfFalse;
        return 1;
    }
    return 0;
}

static int handle_key_press(sfRenderWindow *window, sfEvent event,
    game_t *game)
{
    int state = 0;

    if (event.key.code == sfKeyT && game->menu->game_state == GAME)
        game->show_textures = (game->show_textures == sfTrue) ? sfFalse :
        sfTrue;
    state = check_help_key(window, event, game);
    return state;
}

static int check_game_state(sfRenderWindow *window, sfEvent event,
    game_t *game)
{
    int state = 0;
    sfVector2i mouse_pos;

    if (game->menu->game_state == MENU) {
        state = handle_menu_events(window, game->menu, event, game);
        if (state != 0)
            return state;
    } else if (game->menu->game_state == GAME) {
        mouse_pos = sfMouse_getPositionRenderWindow(window);
        state = handle_map_events(window, event, game);
    }
    return state;
}

static void handle_camera_updates(game_t *game, sfRenderWindow *window,
    sfEvent event, camera_state_t *camera_state)
{
    handle_zoom(event, game);
    move_camera(event, game);
    if (camera_state->last_zoom != game->zoom ||
        camera_state->last_pos.x != game->camera_pos.x ||
        camera_state->last_pos.y != game->camera_pos.y) {
        update_map_after_modification(game, window);
        camera_state->last_zoom = game->zoom;
        camera_state->last_pos = game->camera_pos;
    }
}

static int check_event_type(sfRenderWindow *window, sfEvent event,
    game_t *game)
{
    int state = 0;

    if (event.type == sfEvtClosed || game->menu->game_state ==
        MENU && sfKeyboard_isKeyPressed(sfKeyEscape))
            return -1;
    if (event.type == sfEvtKeyPressed) {
        state = handle_key_press(window, event, game);
        if (state != 0)
            return state;
    }
    return check_game_state(window, event, game);
}

int handle_events(sfRenderWindow *window, sfEvent event, game_t *game)
{
    int state = 0;
    camera_state_t camera_state = {1.0f, {0.0f, 0.0f}};

    while (sfRenderWindow_pollEvent(window, &event)) {
        state = check_event_type(window, event, game);
        if (game->menu->game_state == GAME) {
            handle_camera_updates(game, window, event, &camera_state);
        }
    }
    return state;
}
