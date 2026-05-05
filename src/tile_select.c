/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** tile_select
*/

#include "../include/my_world.h"

select_t *init_tile_selection(void)
{
    select_t *selected_tile = malloc(sizeof(select_t));

    if (!selected_tile)
        exit(84);
    selected_tile->x = -1;
    selected_tile->y = -1;
    selected_tile->is_clicked = sfFalse;
    selected_tile->map_create = NULL;
    return selected_tile;
}

float compute_distance(sfVector2f point, sfVector2i mouse_pos)
{
    float dx = point.x - mouse_pos.x;
    float dy = point.y - mouse_pos.y;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

void update_tile(int x, int y, float dist, select_t *tile)
{
    if (dist < tile->min_distance) {
        tile->min_distance = dist;
        tile->selected.x = x;
        tile->selected.y = y;
    }
}

static void init_tile_selection_struct(select_t *tile)
{
    tile->min_distance = INFINITY;
    tile->selected.x = -1;
    tile->selected.y = -1;
}

static void process_tile_point(select_t *tile, tile_data_t *data,
    int x, int y)
{
    sfVector2f point;
    float dist;

    if (!data->map_2D[x])
        return;
    point.x = data->map_2D[x][y].x + data->create_map->centered_x;
    point.y = data->map_2D[x][y].y + data->create_map->centered_y;
    dist = compute_distance(point, data->mouse_pos);
    if (dist < tile->min_distance) {
        tile->min_distance = dist;
        tile->selected.x = x;
        tile->selected.y = y;
    }
}

sfVector2i get_tile_pos(sfVector2i mouse_pos, sfVector2f **map_2D,
    map_create_t *create_map)
{
    select_t tile;
    tile_data_t data;

    if (!create_map || !map_2D)
        return (sfVector2i){-1, -1};
    init_tile_selection_struct(&tile);
    data.map_2D = map_2D;
    data.create_map = create_map;
    data.mouse_pos = mouse_pos;
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            process_tile_point(&tile, &data, x, y);
        }
    }
    if (tile.min_distance > 50)
        return (sfVector2i){-1, -1};
    return tile.selected;
}
