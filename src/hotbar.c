/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** hotbar
*/

#include "../include/my_world.h"

static sfRectangleShape *create_toolbar_background(int toolbar_y,
    sfVector2u window_size)
{
    sfRectangleShape *background = sfRectangleShape_create();

    sfRectangleShape_setPosition(background, (sfVector2f){0, toolbar_y - 10});
    sfRectangleShape_setSize(background, (sfVector2f){window_size.x, 60});
    sfRectangleShape_setFillColor(background, sfColor_fromRGBA(50, 50, 50,
        200));
    return background;
}

static sfText *init_brush_size_text(sfFont *font, int toolbar_y,
    int btn_width)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 20);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, (sfVector2f){
        30 + (btn_width + 20) * 3 + 100, toolbar_y + 10});
    sfText_setString(text, "SIZE: 1");
    return text;
}

static void create_tool_buttons(toolbar_t *toolbar, button_params_t params)
{
    toolbar->raise_btn = create_button(
        (sfVector2f){20, params.toolbar_y},
        (sfVector2f){params.btn_width, params.btn_height},
        "UP", params.font);
    toolbar->lower_btn = create_button(
        (sfVector2f){20 + params.btn_width + 10, params.toolbar_y},
        (sfVector2f){params.btn_width, params.btn_height},
        "LOW", params.font);
    toolbar->flatten_btn = create_button(
        (sfVector2f){20 + (params.btn_width + 10) * 2, params.toolbar_y},
        (sfVector2f){params.btn_width, params.btn_height},
        "FLAT", params.font);
}

static void create_size_controls(toolbar_t *toolbar, button_params_t params)
{
    toolbar->brush_size_up = create_button(
        (sfVector2f){20 + (params.btn_width + 10) * 3 + 50, params.toolbar_y},
        (sfVector2f){40, params.btn_height}, "+", params.font);
    toolbar->brush_size_down = create_button(
        (sfVector2f){20 + (params.btn_width + 10) * 3, params.toolbar_y},
        (sfVector2f){40, params.btn_height}, "-", params.font);
    toolbar->brush_size_text = init_brush_size_text(params.font,
        params.toolbar_y, params.btn_width);
}

static toolbar_t *create_toolbar_buttons_back(sfRenderWindow *window,
    sfFont *font)
{
    toolbar_t *toolbar = malloc(sizeof(toolbar_t));
    sfVector2u window_size = sfRenderWindow_getSize(window);
    int btn_width = 120;
    int btn_height = 40;
    int toolbar_y = window_size.y - 60;
    button_params_t params;

    if (!toolbar)
        return NULL;
    toolbar->background = create_toolbar_background(toolbar_y, window_size);
    params.toolbar_y = toolbar_y;
    params.btn_width = btn_width;
    params.btn_height = btn_height;
    params.font = font;
    create_tool_buttons(toolbar, params);
    create_size_controls(toolbar, params);
    return toolbar;
}

void create_toolbar(game_t *game, sfRenderWindow *window)
{
    toolbar_t *toolbar = create_toolbar_buttons_back(window,
        game->menu->font);

    if (!toolbar)
        exit(84);
    game->toolbar = toolbar;
    game->current_tool = NONE;
    game->brush_size = 1;
}
