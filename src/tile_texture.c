/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** tile_texture.c
*/

#include "../include/my_world.h"

sfVertexArray *create_textured_tile(sfVector2f *corners)
{
    sfVertexArray *quad = sfVertexArray_create();
    sfVertex vertices[4];

    vertices[0].position = corners[0];
    vertices[0].color = sfWhite;
    vertices[0].texCoords = (sfVector2f){0, 0};
    vertices[1].position = corners[1];
    vertices[1].color = sfWhite;
    vertices[1].texCoords = (sfVector2f){256, 0};
    vertices[2].position = corners[2];
    vertices[2].color = sfWhite;
    vertices[2].texCoords = (sfVector2f){256, 256};
    vertices[3].position = corners[3];
    vertices[3].color = sfWhite;
    vertices[3].texCoords = (sfVector2f){0, 256};
    for (int i = 0; i < 4; i++)
        sfVertexArray_append(quad, vertices[i]);
    sfVertexArray_setPrimitiveType(quad, sfQuads);
    return quad;
}

sfVector2f *get_tile_corners(sfVector2f **map_2d,
    map_create_t *map_create, int x, int y)
{
    sfVector2f *corners = malloc(sizeof(sfVector2f) * 4);

    if (!corners)
        return NULL;
    corners[0].x = map_2d[x][y].x + map_create->centered_x;
    corners[0].y = map_2d[x][y].y + map_create->centered_y;
    corners[1].x = map_2d[x + 1][y].x + map_create->centered_x;
    corners[1].y = map_2d[x + 1][y].y + map_create->centered_y;
    corners[2].x = map_2d[x + 1][y + 1].x + map_create->centered_x;
    corners[2].y = map_2d[x + 1][y + 1].y + map_create->centered_y;
    corners[3].x = map_2d[x][y + 1].x + map_create->centered_x;
    corners[3].y = map_2d[x][y + 1].y + map_create->centered_y;
    return corners;
}

int render_textured_map(sfRenderWindow *window, sfVector2f **map_2d,
    map_create_t *map_create)
{
    sfVector2f *corners = NULL;
    sfVertexArray *quad = NULL;
    static texture_t *textures = NULL;

    if (!textures) {
        textures = init_textures();
        if (!textures)
            exit(84);
    }
    for (int x = 0; x < MAP_X - 1; x++) {
        for (int y = 0; y < MAP_Y - 1; y++) {
            corners = get_tile_corners(map_2d, map_create, x, y);
            quad = create_textured_tile(corners);
            sfRenderWindow_drawVertexArray(window, quad, &textures->states);
            sfVertexArray_destroy(quad);
            free(corners);
        }
    }
    return 0;
}
