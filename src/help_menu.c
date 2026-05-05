/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** help_menu.c
*/

#include "../include/my_world.h"

static void show_help_text(sfRenderWindow *window, sfText *help_text,
    menu_t *menu, sfVector2u window_size)
{
    sfText_setFont(help_text, menu->font);
    sfText_setString(help_text,
        "CONTROLS\n\n"
        "ESC   TO   TOGGLE  THIS  HELP  MENU\n"
        "T   TO   TOGGLE  TEXTURES\n\n"
        "TOOLS\n\n"
        "UP   TO   RAISE  TERRAIN\n"
        "LOW   TO   LOWER  TERRAIN\n"
        "FLAT   TO   FLATTEN  TERRAIN\n"
        "- / +   TO   ADJUST  BRUSH SIZE\n\n"
        "CLICK  ON  A  TILE  TO  MODIFY IT");
    sfText_setCharacterSize(help_text, 30);
    sfText_setColor(help_text, sfWhite);
    sfText_setPosition(help_text,
        (sfVector2f){window_size.x * 0.2f, window_size.y * 0.25f});
    sfRenderWindow_drawText(window, help_text, NULL);
}

static void show_help_title(sfRenderWindow *window, sfText *help_title,
    menu_t *menu, sfVector2u window_size)
{
    sfText_setFont(help_title, menu->font);
    sfText_setString(help_title, "HELP MENU");
    sfText_setCharacterSize(help_title, 50);
    sfText_setColor(help_title, sfWhite);
    sfText_setPosition(help_title,
        (sfVector2f){window_size.x * 0.5f - 150, window_size.y * 0.15f});
    sfRenderWindow_drawText(window, help_title, NULL);
}

static void show_help_background(sfRenderWindow *window,
    sfRectangleShape *help_rect, menu_t *menu, sfVector2u window_size)
{
    sfRectangleShape_setSize(help_rect,
        (sfVector2f){window_size.x * 0.8f, window_size.y * 0.8f});
    sfRectangleShape_setFillColor(help_rect,
        sfColor_fromRGBA(30, 30, 40, 155));
    sfRectangleShape_setOutlineThickness(help_rect, 3.0f);
    sfRectangleShape_setOutlineColor(help_rect, sfWhite);
    sfRectangleShape_setPosition(help_rect,
        (sfVector2f){window_size.x * 0.1f, window_size.y * 0.1f});
    sfRenderWindow_drawRectangleShape(window, help_rect, NULL);
}

static void show_close_text(sfRenderWindow *window,
    sfText *close_text, menu_t *menu, sfVector2u window_size)
{
    sfText_setFont(close_text, menu->font);
    sfText_setString(close_text, "PRESS  ESC  TO  GO  BACK  TO  YOUR WORLD");
    sfText_setCharacterSize(close_text, 24);
    sfText_setColor(close_text, sfColor_fromRGB(200, 200, 200));
    sfText_setPosition(close_text,
        (sfVector2f){window_size.x * 0.5f, window_size.y * 0.8f});
}

int show_help_menu(sfRenderWindow *window, menu_t *menu)
{
    sfRectangleShape *help_rect = sfRectangleShape_create();
    sfText *help_title = sfText_create();
    sfText *help_text = sfText_create();
    sfText *close_text = sfText_create();
    sfVector2u window_size = sfRenderWindow_getSize(window);

    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, menu->background, NULL);
    show_help_background(window, help_rect, menu, window_size);
    show_help_title(window, help_title, menu, window_size);
    show_help_text(window, help_text, menu, window_size);
    show_close_text(window, close_text, menu, window_size);
    sfRenderWindow_drawText(window, close_text, NULL);
    return 0;
}
