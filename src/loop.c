/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** loop.c
*/

#include "../include/my_world.h"

int check_game_environment(sfClock *clock, map_lines_t *map_lines,
    sfVector2f **map_2d, menu_t *menu)
{
    if (check_init(clock, map_lines, map_2d) == 84 || !menu)
        exit(84);
    return 0;
}

void update_game_state(menu_t *menu)
{
    if (menu->game_state == MENU) {
        if (menu->play_button->is_clicked)
            menu->game_state = GAME;
    }
}

void render_menu_or_game(sfRenderWindow *window, game_t *game)
{
    menu_t *menu = game->menu;

    sfRenderWindow_clear(window, sfBlack);
    if (menu->game_state == MENU)
        draw_menu(window, menu);
    else if (game->show_help == sfTrue)
        show_help_menu(window, menu);
    else {
        render_frame(window, game);
        render_toolbar(window, game);
    }
    sfRenderWindow_display(window);
}

static void cleanup_resources(game_resources_t *resources)
{
    if (!resources)
        return;
    if (resources->menu)
        destroy_menu(resources->menu);
    cleanup(resources->map_2d, resources->map_lines);
    if (resources->clock)
        sfClock_destroy(resources->clock);
    if (resources->map_create)
        free(resources->map_create);
    if (resources->textures)
        free_textures(resources->textures);
    resources->menu = NULL;
    resources->map_2d = NULL;
    resources->map_lines = NULL;
    resources->clock = NULL;
    resources->map_create = NULL;
    resources->textures = NULL;
    resources->sounds = NULL;
}

static void process_events(sfRenderWindow *window, sfEvent event,
    game_t *game, int *running)
{
    int evt_result;

    if (!game || !game->resources || !game->resources->menu) {
        *running = 0;
        return;
    }
    evt_result = handle_events(window, event, game);
    if (evt_result == -1 || game->resources->menu->quit_button->is_clicked)
        *running = 0;
    if (evt_result == 1)
        game->resources->menu->game_state = 1;
}

static void free_game_memory(game_t *game, game_resources_t *resources)
{
    cleanup_resources(resources);
    free(resources);
    free(game->tile);
    free(game);
}

static int check_resources(game_t *game, game_resources_t *resources,
    sfRenderWindow *window)
{
    if (!game || !resources) {
        free(game);
        free(resources);
        return 84;
    }
    if (init_game_resources(resources, window) == 84) {
        free(game);
        free(resources);
        return 84;
    }
    return 0;
}

static void setup_game(game_t *game, game_resources_t *resources,
    sfRenderWindow *window)
{
    game->resources = resources;
    game->menu = resources->menu;
    game->show_help = sfFalse;
    game->tile = init_tile_selection();
    game->current_tool = NONE;
    game->brush_size = 2;
    game->zoom = 1.0f;
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    init_terrain_height(game);
    create_toolbar(game, window);
}

void update_frame(sfRenderWindow *window, game_t *game)
{
    sfBool t_key_was_pressed = sfFalse;
    sfBool t_key_is_pressed = sfFalse;

    if (t_key_is_pressed && !t_key_was_pressed)
        game->show_textures = !game->show_textures;
    t_key_was_pressed = t_key_is_pressed;
    update_game_state(game->resources->menu);
    render_menu_or_game(window, game);
    sfClock_restart(game->resources->clock);
}

int run_world(sfRenderWindow *window, sfEvent event)
{
    game_t *game = malloc(sizeof(game_t));
    game_resources_t *resources = malloc(sizeof(game_resources_t));
    int running = 1;
    float frame_limit = 1.0 / 60.0;

    game->show_textures = sfTrue;
    if (check_resources(game, resources, window) == 84)
        exit(84);
    setup_game(game, resources, window);
    while (sfRenderWindow_isOpen(window) && running) {
        process_events(window, event, game, &running);
        if (sfTime_asSeconds(sfClock_getElapsedTime(game->resources->clock))
            >= frame_limit) {
            update_frame(window, game);
        }
    }
    free_game_memory(game, resources);
    return 0;
}
