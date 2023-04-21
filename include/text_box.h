/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** text box
*/

#include <SFML/Graphics.h>
#include "item.h"
#include "entities.h"
#include "errorhandling.h"

#ifndef TEXT_BOX_H
    #define TEXT_BOX_H

    typedef struct text_box {
        sfRectangleShape *box;
        sfText *title;
        sfText *text_line_1;
        sfText *text_line_2;
        sfFont *font;
        int text_delay;
        char **to_print;
        int index;
        int max;
    } text_box_t;

    text_box_t *text_box_create(sfFont *font, sfTexture *rect_texture);
    void text_box_modify(text_box_t *text_box, char *new_title,
                        char *new_text, int text_delay);
    void text_box_destroy(void *item);
    void text_box_update(void *item, window_t *window, UNUSED float delta);
    void text_box_print(void *item, window_t *win);
    void talk_tuto_pnj(UNUSED entity_t *player, UNUSED collider_t *col);
    void talk_combat_pnj(UNUSED entity_t *player, UNUSED collider_t *col);
    void talk_quest_pnj(UNUSED entity_t *player, UNUSED collider_t *col);
    void interact_empty_chest(UNUSED entity_t *player,
                            UNUSED collider_t *chest);
    void interact_chest(entity_t *player, collider_t *chest);

#endif
