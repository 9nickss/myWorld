/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** menu_button.c
*/

#include "../../include/my_world.h"

void update_button_state(button_t *button, sfVector2i mouse_pos, game_t *game)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(button->rect);
    sfBool is_hover = sfFloatRect_contains(&bounds, mouse_pos.x, mouse_pos.y);

    if (is_hover && !button->is_hover) {
        if (game && game->resources && game->resources->sounds &&
            game->resources->sounds->select_sound) {
            sfMusic_setVolume(game->resources->sounds->select_sound, 50);
            sfMusic_play(game->resources->sounds->select_sound);
        }
    }
    if (is_hover) {
        sfRectangleShape_setFillColor(button->rect,
            sfColor_fromRGB(100, 100, 100));
    } else
        sfRectangleShape_setFillColor(button->rect, sfBlack);
    button->is_hover = is_hover;
}

void destroy_button(button_t *button)
{
    if (!button)
        return;
    sfRectangleShape_destroy(button->rect);
    sfText_destroy(button->text);
    free(button);
}

static sfText *create_button_text(sfText *button_text, char *text,
    sfFont *font)
{
    sfFloatRect textRect;

    sfText_setString(button_text, text);
    sfText_setFont(button_text, font);
    sfText_setCharacterSize(button_text, 30);
    sfText_setColor(button_text, sfWhite);
    textRect = sfText_getLocalBounds(button_text);
    if (strlen(text) == 1 && (text[0] == '+' || text[0] == '-'))
        sfText_setOrigin(button_text,
            (sfVector2f){textRect.width / 2, textRect.height / 5});
    else
        sfText_setOrigin(button_text,
            (sfVector2f){textRect.width / 2, textRect.height / 2});
    return button_text;
}

button_t *init_button(sfRectangleShape *button_rect, button_t *button)
{
    button->rect = button_rect;
    button->is_hover = sfFalse;
    button->is_clicked = sfFalse;
    return button;
}

button_t *create_button(sfVector2f position, sfVector2f size,
    char *text, sfFont *font)
{
    button_t *button = malloc(sizeof(button_t));
    sfText *button_text = sfText_create();
    sfRectangleShape *button_rect = sfRectangleShape_create();

    if (!button || !button_text || !button_rect)
        return NULL;
    sfRectangleShape_setPosition(button_rect, position);
    sfRectangleShape_setSize(button_rect, size);
    sfRectangleShape_setFillColor(button_rect, sfBlack);
    sfRectangleShape_setOutlineThickness(button_rect, 2);
    sfRectangleShape_setOutlineColor(button_rect, sfBlack);
    button->text = create_button_text(button_text, text, font);
    if (strlen(text) == 1 && (text[0] == '+' || text[0] == '-'))
        sfText_setPosition(button->text,
            (sfVector2f){position.x + size.x / 2, position.y + size.y / 10});
    else
        sfText_setPosition(button->text,
            (sfVector2f){position.x + size.x / 2, position.y + size.y / 3});
    button = init_button(button_rect, button);
    return button;
}
