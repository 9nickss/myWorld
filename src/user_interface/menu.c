/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** menu.c
*/

#include "../../include/my_world.h"

void destroy_menu(menu_t *menu)
{
    if (!menu)
        return;
    sfSprite_destroy(menu->background);
    sfTexture_destroy(menu->background_texture);
    destroy_button(menu->play_button);
    destroy_button(menu->quit_button);
    sfFont_destroy(menu->font);
    free(menu);
}

static int init_menu_background(menu_t *menu, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2u texture_size;
    float scale_x;
    float scale_y;

    menu->background_texture = sfTexture_createFromFile(
        "assets/images/background.png", NULL);
    if (!menu->background_texture)
        exit(84);
    texture_size = sfTexture_getSize(menu->background_texture);
    scale_x = (float)window_size.x / texture_size.x;
    scale_y = (float)window_size.y / texture_size.y;
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    sfSprite_scale(menu->background, (sfVector2f){scale_x, scale_y});
    return 0;
}

static void init_menu_buttons(menu_t *menu, sfRenderWindow *window,
    sfFont *font)
{
    float center_x = sfRenderWindow_getSize(window).x / 2;
    float center_y = sfRenderWindow_getSize(window).y / 2;
    sfVector2f button_size = {200, 60};

    menu->play_button = create_button((sfVector2f){
            center_x - button_size.x / 2,
        center_y - 50}, button_size, "PLAY", font);
    menu->quit_button = create_button((sfVector2f){
            center_x - button_size.x / 2,
        center_y + 50}, button_size, "QUIT", font);
}

static void free_menu_resources(menu_t *menu)
{
    if (menu->font)
        sfFont_destroy(menu->font);
    free(menu);
}

menu_t *init_menu(sfRenderWindow *window)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->font = sfFont_createFromFile("assets/fonts/Bleach.ttf");
    if (!menu->font) {
        free(menu);
        return NULL;
    }
    if (init_menu_background(menu, window) == 84) {
        free_menu_resources(menu);
        return NULL;
    }
    init_menu_buttons(menu, window, menu->font);
    if (!menu->play_button || !menu->quit_button) {
        free_menu_resources(menu);
        return NULL;
    }
    return menu;
}

void draw_menu(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_drawSprite(window, menu->background, NULL);
    sfRenderWindow_drawRectangleShape(window, menu->play_button->rect, NULL);
    sfRenderWindow_drawText(window, menu->play_button->text, NULL);
    sfRenderWindow_drawRectangleShape(window, menu->quit_button->rect, NULL);
    sfRenderWindow_drawText(window, menu->quit_button->text, NULL);
}
