/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** text box
*/

#include <SFML/Graphics.h>
#include "item.h"

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
    } text_box_t;

    text_box_t *text_box_create(sfFont *font, sfTexture *rect_texture);
    void text_box_modify(text_box_t *text_box, char *new_title,
                        char *new_text, int text_delay);
    void text_box_destroy(void *item);
    void text_box_update(void *item, window_t *window);
    void text_box_print(void *item, window_t *win);

#endif
