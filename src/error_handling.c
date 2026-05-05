/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** error_handling.c
*/

#include "../include/my_world.h"

int check_init(sfClock *clock, map_lines_t *map_lines,
    sfVector2f **map_2d)
{
    if (!map_2d || !clock)
        exit(84);
    if (!map_lines) {
        cleanup(map_2d, NULL);
        sfClock_destroy(clock);
        exit(84);
    }
    return 0;
}

void cleanup(sfVector2f **map_2d, map_lines_t *map_lines)
{
    if (map_lines) {
        for (int i = 0; i < map_lines->count; i++)
            sfVertexArray_destroy(map_lines->lines[i]);
        free(map_lines->lines);
        free(map_lines);
    }
    if (map_2d) {
        for (int x = 0; x < MAP_X; x++)
            free(map_2d[x]);
        free(map_2d);
    }
}
