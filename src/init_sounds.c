/*
** EPITECH PROJECT, 2024
** G-ING-200-NCE-2-1-myworld-aryan.bhotey
** File description:
** init_sounds.c
*/

#include "../include/my_world.h"

void free_sounds(sounds_t *sounds)
{
    if (sounds) {
        if (sounds->select_sound)
            sfMusic_destroy(sounds->select_sound);
        if (sounds->click_sound)
            sfMusic_destroy(sounds->click_sound);
        free(sounds);
    }
}

sounds_t *init_sounds(void)
{
    sounds_t *sounds = malloc(sizeof(sounds_t));

    if (!sounds)
        return NULL;
    sounds->select_sound = sfMusic_createFromFile
        ("assets/sounds/select_sound.mp3");
    sounds->click_sound = sfMusic_createFromFile
        ("assets/sounds/click_sound.mp3");
    if (!sounds->select_sound || !sounds->click_sound) {
        free(sounds);
        return NULL;
    }
    return sounds;
}
