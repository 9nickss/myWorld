/*
** EPITECH PROJECT, 2024
** ING
** File description:
** my.h
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <SFML/Audio.h>

#ifndef MY_H_
    #define MY_H_
    #define MAP_X   40
    #define MAP_Y   40

typedef enum {
    NONE = 0,
    RAISE = 1,
    LOWER = 2,
    FLAT = 3
} effect_t;

typedef enum {
    MENU = 0,
    GAME = 1,
    OPTIONS = 2
} state_t;

typedef enum {
    SELECT_NONE = 0,
    SELECT_HOVER = 1,
    SELECT_CLICK = 2
} select_mode_t;

typedef struct camera_state_s {
    float last_zoom;
    sfVector2f last_pos;
} camera_state_t;

typedef struct coord_s {
    int x;
    int y;
    int center_x;
    int center_y;
} coord_t;

typedef struct button_params_s {
    int toolbar_y;
    int btn_width;
    int btn_height;
    sfFont *font;
} button_params_t;

typedef struct sounds_s {
    sfMusic *select_sound;
    sfMusic *click_sound;
} sounds_t;

typedef struct button_s {
    sfRectangleShape *rect;
    sfText *text;
    sfBool is_hover;
    sfBool is_clicked;
} button_t;

typedef struct toolbar_s {
    button_t *raise_btn;
    button_t *lower_btn;
    button_t *flatten_btn;
    button_t *brush_size_up;
    button_t *brush_size_down;
    sfText *brush_size_text;
    sfRectangleShape *background;
} toolbar_t;

typedef struct menu_s {
    sfSprite *background;
    sfTexture *background_texture;
    button_t *play_button;
    button_t *quit_button;
    sfFont *font;
    state_t game_state;
} menu_t;

typedef struct texture_s {
    sfTexture *grass_txt;
    sfRenderStates states;
} texture_t;

typedef struct map_lines_s {
    sfVertexArray **lines;
    int count;
} map_lines_t;

typedef struct map_create_s {
    float zoom;
    float centered_x;
    float centered_y;
    sfVector2f centered_point1;
    sfVector2f centered_point2;
} map_create_t;

typedef struct tile_data_s {
    sfVector2f **map_2D;
    map_create_t *create_map;
    sfVector2i mouse_pos;
} tile_data_t;

typedef struct game_resources_s {
    sfVector2f **map_2d;
    map_lines_t *map_lines;
    sfClock *clock;
    menu_t *menu;
    texture_t *textures;
    map_create_t *map_create;
    sounds_t *sounds;
} game_resources_t;

typedef struct select_s {
    int x;
    int y;
    sfBool is_clicked;
    float min_distance;
    sfVector2i selected;
    map_create_t *map_create;
    select_mode_t mode;
    sfBool is_hovering;
    sfVector2i hover_pos;
} select_t;

typedef struct multi_select_s {
    sfVector2i *tiles;
    int count;
    int capacity;
} multi_select_t;

typedef struct game_s {
    menu_t *menu;
    select_t *tile;
    game_resources_t *resources;
    effect_t current_tool;
    sfBool show_textures;
    int height[MAP_X][MAP_Y];
    multi_select_t *multi_selection;
    toolbar_t *toolbar;
    float zoom;
    sfVector2f camera_pos;
    int x;
    int y;
    int i;
    int j;
    int brush_size;
    int target_height;
    int amount;
    sfBool show_help;
} game_t;

extern int map[MAP_X][MAP_Y];

sfVector2f project_iso_point(int x, int y, int z);

map_lines_t *create_map_lines(sfRenderWindow *window, sfVector2f **map_2d);
sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2);
int check_map_and_clock(sfClock *clock, map_lines_t *map_lines,
    sfVector2f **map_2d);
sfVector2f **create_2d_map(void);
void regenerate_map_2d(game_t *game);
sfVector2f project_iso_point_with_zoom(int x, int y, int z,
    map_create_t *map_create);
int render_textured_map(sfRenderWindow *window, sfVector2f **map_2d,
    map_create_t *map_create);

int run_world(sfRenderWindow *window, sfEvent event);
void render_frame(sfRenderWindow *window, game_t *game);
void update_game_state(menu_t *menu);
void render_menu_or_game(sfRenderWindow *window, game_t *game);
int handle_events(sfRenderWindow *window, sfEvent event, game_t *game);

void cleanup(sfVector2f **map_2d, map_lines_t *map_lines);

int check_init(sfClock *clock, map_lines_t *map_lines,
    sfVector2f **map_2d);
texture_t *init_textures(void);

button_t *create_button(sfVector2f position, sfVector2f size,
    char *text, sfFont *font);
void destroy_button(button_t *button);
void draw_menu(sfRenderWindow *window, menu_t *menu);
void update_button_state(button_t *button, sfVector2i mouse_pos, game_t *game);
void destroy_button(button_t *button);
void destroy_menu(menu_t *menu);
menu_t *init_menu(sfRenderWindow *window);
void free_textures(texture_t *textures);
void free_tile_selection(select_t *tile);

select_t *init_tile_selection(void);
int init_game_resources(game_resources_t *resources, sfRenderWindow *window);
int check_game_environment(sfClock *clock, map_lines_t *map_lines,
    sfVector2f **map_2d, menu_t *menu);

float compute_distance(sfVector2f point, sfVector2i mouse_pos);
void update_tile(int x, int y, float dist, select_t *tile);
sfVector2i get_tile_pos(sfVector2i mouse_pos, sfVector2f **map_2D,
    map_create_t *create_map);

int handle_map_events(sfRenderWindow *window, sfEvent event, game_t *game);

void init_terrain_height(game_t *game);
void up_terrain(game_t *game, int x, int y);
void lower_terrain(game_t *game, int x, int y);
void flatten_terrain(game_t *game, int x, int y);
void update_map_after_modification(game_t *game, sfRenderWindow *window);
void create_toolbar(game_t *game, sfRenderWindow *window);
void render_toolbar(sfRenderWindow *window, game_t *game);
void handle_toolbar_events(sfRenderWindow *window, sfEvent event,
    game_t *game);

void create_toolbar(game_t *game, sfRenderWindow *window);
void destroy_toolbar(toolbar_t *toolbar);
void render_toolbar(sfRenderWindow *window, game_t *game);
void handle_toolbar_events(sfRenderWindow *window, sfEvent event,
    game_t *game);

void handle_zoom(sfEvent event, game_t *game);
void move_camera(sfEvent event, game_t *game);
int show_help_menu(sfRenderWindow *window, menu_t *menu);

sounds_t *init_sounds(void);
void free_sounds(sounds_t *sounds);

#endif /*MY_H_*/
