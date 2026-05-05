/*
** EPITECH PROJECT, 2024
** ING
** File description:
** bs_myworld.c
*/

#include "../include/my_world.h"

static const int MAP_DATA[MAP_X][MAP_Y] = {
    {00, 00, 00, 00, 00, 00},
    {00, 00, 00, 00, 00, 00},
    {00, 00, 00, 00, 00, 00},
    {00, 00, 00, 00, 00, 00},
    {00, 00, 00, 00, 00, 00},
    {00, 00, 00, 00, 00, 00}
};

sfVector2f project_iso_point(int x, int y, int z)
{
    sfVector2f point_2d;
    float angle_x = 45.0 * M_PI / 180.0;
    float angle_y = 35.0 * M_PI / 180.0;

    x = x * 64;
    y = y * 64;
    z = z * 10;
    point_2d.x = cos(angle_x) * x - cos(angle_x) * y;
    point_2d.y = sin(angle_y) * y + sin(angle_y) * x - z;
    return point_2d;
}

sfVector2f project_iso_point_with_zoom(int x, int y, int z,
    map_create_t *map_create)
{
    sfVector2f point_2d;
    float angle_x = 45.0 * M_PI / 180.0;
    float angle_y = 35.0 * M_PI / 180.0;

    x = x * 64;
    y = y * 64;
    z = z * 10;
    point_2d.x = (cos(angle_x) * x - cos(angle_x) * y) * map_create->zoom +
        map_create->centered_x;
    point_2d.y = (sin(angle_y) * y + sin(angle_y) * x - z) * map_create->zoom
        + map_create->centered_y;
    return point_2d;
}

sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    return vertex_array;
}

static void check_map_x(sfVector2f **map_2d, int y, int x)
{
    if (!map_2d[x]) {
        for (y = 0; y < x; y++)
            free(map_2d[y]);
        free(map_2d);
        exit(84);
    }
    return;
}

sfVector2f **create_2d_map(void)
{
    sfVector2f **map_2d = malloc(sizeof(sfVector2f *) * MAP_X);
    int y = 0;

    if (!map_2d)
        return NULL;
    for (int x = 0; x < MAP_X; x++) {
        map_2d[x] = malloc(sizeof(sfVector2f) * MAP_Y);
        check_map_x(map_2d, y, x);
    }
    for (int x = 0; x < MAP_X; x++) {
        for (y = 0; y < MAP_Y; y++)
            map_2d[x][y] = project_iso_point(x, y, MAP_DATA[x][y]);
    }
    return map_2d;
}

void render_frame(sfRenderWindow *window, game_t *game)
{
    map_create_t map_create;
    map_lines_t *map_lines = game->resources->map_lines;
    sfVector2f **map_2d = game->resources->map_2d;

    map_create.centered_x = sfRenderWindow_getSize(window).x / 2;
    map_create.centered_y = sfRenderWindow_getSize(window).y / 4;
    sfRenderWindow_clear(window, sfBlack);
    if (game->show_textures == sfTrue)
        render_textured_map(window, map_2d, &map_create);
    for (int i = 0; i < map_lines->count; i++)
        sfRenderWindow_drawVertexArray(window, map_lines->lines[i], NULL);
}
