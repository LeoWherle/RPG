/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** parse the text
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "text_box.h"

static int get_line_len(char *txt)
{
    int i = 0;

    while (i < 80 && txt[i] != '\0' && txt[i] != '\n') {
        i++;
    }
    while (txt[i] != ' ' && txt[i] != '\0' && txt[i] != '\n') {
        i--;
    }
    return i + 1;
}

static int get_nb_lines(char *txt)
{
    int size = 0;
    int i = 0;

    while (txt[i] != '\0') {
        i += get_line_len(&txt[i]);
        size++;
    }
    return size;
}

static char **format_text(char *text)
{
    char **new = NULL;
    int size = 1;
    int y = 0;
    int i = 0;
    int len = 0;

    size = get_nb_lines(text);
    new = malloc(sizeof(char *) * (size + 1));
    for (int x = 0; x < size; x++) {
        len = get_line_len(&text[i]);
        new[x] = malloc(sizeof(char *) * len);
        for (y = 0; y < len; y++)
            new[x][y] = text[i + y];
        new[x][y - 1] = '\0';
        i += y;
    }
    new[size] = NULL;
    return new;
}

void text_box_modify(text_box_t *text, char *new_title,
                    char *new_text, int text_delay)
{
    static text_box_t *text_box = NULL;
    int max = 0;

    if (!text_box) {
        text_box = text;
        return;
    }
    text_box->to_print = format_text(new_text);
    for (max = 0; text_box->to_print[max]; max++);
    text_box->max = max;
    text_box->index = 0;
    text_box->text_delay = text_delay;
    sfText_setString(text_box->title, new_title);
    sfText_setString(text_box->text_line_1, text_box->to_print[0]);
    sfText_setString(text_box->text_line_2, text_box->to_print[1]);
}
