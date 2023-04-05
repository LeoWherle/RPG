/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** text box
*/

#include <SFML/Graphics.h>

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

#endif