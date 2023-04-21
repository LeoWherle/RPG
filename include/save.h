/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** save
*/


#ifndef SAVE_H
    #define SAVE_H
    #include "item.h"
    #include "entities.h"

    void save(entity_t *player);
    bool load(entity_t *player);
    void load_button(void *gui, window_t *game);
    void save_button(void *gui, window_t *game);
    void play_button(UNUSED void *gui, window_t *screen);

#endif /*SAVE_H*/
