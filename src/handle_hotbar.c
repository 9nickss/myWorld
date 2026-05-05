/*
** EPITECH PROJECT, 2025
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** hotbar
*/

#include "../include/my_world.h"

static void draw_button(sfRenderWindow *window, button_t *button)
{
    sfRenderWindow_drawRectangleShape(window, button->rect, NULL);
    sfRenderWindow_drawText(window, button->text, NULL);
}

static void draw_buttons(sfRenderWindow *window, toolbar_t *toolbar)
{
    sfRenderWindow_drawRectangleShape(window, toolbar->background, NULL);
    draw_button(window, toolbar->raise_btn);
    draw_button(window, toolbar->lower_btn);
    draw_button(window, toolbar->flatten_btn);
    draw_button(window, toolbar->brush_size_up);
    draw_button(window, toolbar->brush_size_down);
    sfRenderWindow_drawText(window, toolbar->brush_size_text, NULL);
}

static void update_selected_tool_color(toolbar_t *toolbar,
    effect_t current_tool)
{
    sfRectangleShape_setFillColor(toolbar->raise_btn->rect, sfBlack);
    sfRectangleShape_setFillColor(toolbar->lower_btn->rect, sfBlack);
    sfRectangleShape_setFillColor(toolbar->flatten_btn->rect, sfBlack);
    switch (current_tool) {
        case RAISE:
            sfRectangleShape_setFillColor(toolbar->raise_btn->rect,
                sfColor_fromRGB(100, 200, 100));
            break;
        case LOWER:
            sfRectangleShape_setFillColor(toolbar->lower_btn->rect,
                sfColor_fromRGB(100, 200, 100));
            break;
        case FLAT:
            sfRectangleShape_setFillColor(toolbar->flatten_btn->rect,
                sfColor_fromRGB(100, 200, 100));
            break;
        default:
            break;
    }
}

void render_toolbar(sfRenderWindow *window, game_t *game)
{
    toolbar_t *toolbar = game->toolbar;
    char size_text[20];

    if (!toolbar)
        return;
    snprintf(size_text, sizeof(size_text), "SIZE: %d", game->brush_size);
    sfText_setString(toolbar->brush_size_text, size_text);
    draw_buttons(window, toolbar);
    update_selected_tool_color(toolbar, game->current_tool);
}

static void handle_tool_selection(game_t *game, toolbar_t *toolbar)
{
    button_t *buttons[3] = {
        toolbar->raise_btn,
        toolbar->lower_btn,
        toolbar->flatten_btn
    };
    effect_t tools[3] = {RAISE, LOWER, FLAT};

    for (int i = 0; i < 3; i++) {
        if (buttons[i]->is_hover) {
            game->current_tool = tools[i];
            return;
        }
    }
}

static void handle_brush_size_adjustment(game_t *game, toolbar_t *toolbar)
{
    if (toolbar->brush_size_up->is_hover && game->brush_size < 5)
        game->brush_size += 1;
    if (toolbar->brush_size_down->is_hover && game->brush_size > 1)
        game->brush_size -= 1;
}

void handle_toolbar_events(sfRenderWindow *window, sfEvent event,
    game_t *game)
{
    toolbar_t *toolbar = game->toolbar;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    if (!toolbar)
        return;
    update_button_state(toolbar->raise_btn, mouse_pos, game);
    update_button_state(toolbar->lower_btn, mouse_pos, game);
    update_button_state(toolbar->flatten_btn, mouse_pos, game);
    update_button_state(toolbar->brush_size_up, mouse_pos, game);
    update_button_state(toolbar->brush_size_down, mouse_pos, game);
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        handle_tool_selection(game, toolbar);
        handle_brush_size_adjustment(game, toolbar);
    }
}
