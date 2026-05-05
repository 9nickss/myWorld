/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** init_all.c
*/

#include "../include/my_world.h"

void free_textures(texture_t *textures)
{
    if (textures) {
        if (textures->grass_txt)
            sfTexture_destroy(textures->grass_txt);
        free(textures);
    }
}

void free_tile_selection(select_t *tile)
{
    if (!tile)
        return;
    if (tile->map_create) {
        free(tile->map_create);
        tile->map_create = NULL;
    }
    free(tile);
}

texture_t *init_textures(void)
{
    texture_t *textures = malloc(sizeof(texture_t));

    if (!textures) {
        free_textures(textures);
        return NULL;
    }
    textures->grass_txt = sfTexture_createFromFile("assets/images/grass.png",
        NULL);
    textures->states.blendMode = sfBlendAlpha;
    textures->states.shader = NULL;
    textures->states.texture = textures->grass_txt;
    textures->states.transform = sfTransform_Identity;
    return textures;
}

int init_game_resources(game_resources_t *resources, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);

    if (!resources)
        return 84;
    resources->map_2d = create_2d_map();
    resources->map_lines = create_map_lines(window, resources->map_2d);
    resources->clock = sfClock_create();
    resources->menu = init_menu(window);
    if (resources->menu)
        resources->menu->game_state = MENU;
    resources->map_create = malloc(sizeof(map_create_t));
    if (!resources->map_create)
        return 84;
    resources->map_create->centered_x = window_size.x / 2;
    resources->map_create->centered_y = window_size.y / 4;
    resources->textures = init_textures();
    resources->sounds = init_sounds();
    return check_game_environment(resources->clock, resources->map_lines,
        resources->map_2d, resources->menu);
}

void destroy_toolbar(toolbar_t *toolbar)
{
    if (!toolbar)
        return;
    destroy_button(toolbar->raise_btn);
    destroy_button(toolbar->lower_btn);
    destroy_button(toolbar->flatten_btn);
    destroy_button(toolbar->brush_size_up);
    destroy_button(toolbar->brush_size_down);
    sfText_destroy(toolbar->brush_size_text);
    sfRectangleShape_destroy(toolbar->background);
    free(toolbar);
}
