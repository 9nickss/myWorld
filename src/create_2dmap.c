/*
** EPITECH PROJECT, 2024
** BS
** File description:
** create_2d_map.c
*/

#include "../include/my_world.h"

static void set_point_coordinates(sfVector2f *point, sfVector2f map_point,
    float center_x, float center_y)
{
    point->x = map_point.x + center_x;
    point->y = map_point.y + center_y;
}

static void create_horizontal_lines(map_create_t *map_create,
    map_lines_t *result, sfVector2f **map_2d)
{
    int index = 0;
    sfVector2f point1;
    sfVector2f point2;

    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y - 1; y++) {
            set_point_coordinates(&point1, map_2d[x][y],
                map_create->centered_x, map_create->centered_y);
            set_point_coordinates(&point2, map_2d[x][y + 1],
                map_create->centered_x, map_create->centered_y);
            result->lines[index] = create_line(&point1, &point2);
            index++;
        }
    }
}

static void create_vertical_lines(map_create_t *map_create,
    map_lines_t *result, int start_index, sfVector2f **map_2d)
{
    int index = start_index;
    sfVector2f point1;
    sfVector2f point2;

    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X - 1; x++) {
            set_point_coordinates(&point1, map_2d[x][y],
                map_create->centered_x, map_create->centered_y);
            set_point_coordinates(&point2, map_2d[x + 1][y],
                map_create->centered_x, map_create->centered_y);
            result->lines[index] = create_line(&point1, &point2);
            index++;
        }
    }
}

static void init_map_create(map_create_t *map_create, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);

    map_create->centered_x = window_size.x / 2;
    map_create->centered_y = window_size.y / 4;
}

map_lines_t *create_map_lines(sfRenderWindow *window, sfVector2f **map_2d)
{
    map_create_t *map_create = malloc(sizeof(map_create_t));
    map_lines_t *result = malloc(sizeof(map_lines_t));
    int hor_lines_count = MAP_X * (MAP_Y - 1);

    if (!map_create || !result)
        return NULL;
    init_map_create(map_create, window);
    result->count = hor_lines_count + MAP_Y * (MAP_X - 1);
    result->lines = malloc(sizeof(sfVertexArray *) * result->count);
    if (!result->lines) {
        free(result);
        return NULL;
    }
    create_horizontal_lines(map_create, result, map_2d);
    create_vertical_lines(map_create, result, hor_lines_count, map_2d);
    free(map_create);
    return result;
}

void update_map_after_modification(game_t *game, sfRenderWindow *window)
{
    sfVector2f **map_2d = game->resources->map_2d;
    map_lines_t *map_lines = game->resources->map_lines;

    cleanup(NULL, map_lines);
    regenerate_map_2d(game);
    game->resources->map_lines = create_map_lines(window, map_2d);
}
