/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** toolbox
*/

#include "../include/my_world.h"

void init_terrain_height(game_t *game)
{
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            game->height[x][y] = 0;
        }
    }
    game->amount = 1;
    game->zoom = 1.0f;
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
}

static void height_change(game_t *game, int x, int y, float factor)
{
    int amount = game->amount;

    game->height[x][y] += (int)(factor * amount * 1.5);
    if (game->height[x][y] > 20)
        game->height[x][y] = 20;
    if (game->height[x][y] < -20)
        game->height[x][y] = -20;
}

static float calculate_factor(coord_t coords, int brush_size)
{
    float distance;
    float effective_radius = brush_size * 1.5;

    if (!(coords.x >= 0 && coords.x < MAP_X && coords.y >= 0 &&
        coords.y < MAP_Y))
        return -1.0;
    distance = sqrt(pow(coords.center_x - coords.x, 2) +
    pow(coords.center_y - coords.y, 2));
    if (distance > effective_radius)
        return -1.0;
    return 1.0 - (distance / effective_radius);
}

static void rise_tile(game_t *game, coord_t coords)
{
    float factor = calculate_factor(coords, game->brush_size);

    if (factor < 0)
        return;
    height_change(game, coords.x, coords.y, factor);
}

static void lower_tile(game_t *game, coord_t coords)
{
    float factor = calculate_factor(coords, game->brush_size);

    if (factor < 0)
        return;
    height_change(game, coords.x, coords.y, -factor);
}

static void flatten_tile(game_t *game, coord_t coords, int target_height)
{
    float factor = calculate_factor(coords, game->brush_size);

    if (factor < 0)
        return;
    game->height[coords.x][coords.y] = (int)(
        game->height[coords.x][coords.y] * (1 - factor) +
        target_height * factor);
}

void up_terrain(game_t *game, int x, int y)
{
    int brush_size = game->brush_size;
    coord_t coords;

    coords.center_x = x;
    coords.center_y = y;
    for (int i = x - brush_size; i <= x + brush_size; i++) {
        for (int j = y - brush_size; j <= y + brush_size; j++) {
            coords.x = i;
            coords.y = j;
            rise_tile(game, coords);
        }
    }
}

void lower_terrain(game_t *game, int x, int y)
{
    int brush_size = game->brush_size;
    coord_t coords;

    coords.center_x = x;
    coords.center_y = y;
    for (int i = x - brush_size; i <= x + brush_size; i++) {
        for (int j = y - brush_size; j <= y + brush_size; j++) {
            coords.x = i;
            coords.y = j;
            lower_tile(game, coords);
        }
    }
}

void flatten_terrain(game_t *game, int x, int y)
{
    int brush_size = game->brush_size;
    int target_height = game->height[x][y];
    coord_t coords;

    coords.center_x = x;
    coords.center_y = y;
    for (int i = x - brush_size; i <= x + brush_size; i++) {
        for (int j = y - brush_size; j <= y + brush_size; j++) {
            coords.x = i;
            coords.y = j;
            flatten_tile(game, coords, target_height);
        }
    }
}

void regenerate_map_2d(game_t *game)
{
    sfVector2f **map_2d = game->resources->map_2d;
    map_create_t map_create;

    map_create.zoom = game->zoom;
    map_create.centered_x = game->camera_pos.x;
    map_create.centered_y = game->camera_pos.y;
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            map_2d[x][y] = project_iso_point_with_zoom(x, y,
                game->height[x][y], &map_create);
        }
    }
}
