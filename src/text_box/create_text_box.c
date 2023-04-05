/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create and delete text box
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "text_box.h"
#include "errorhandling.h"
#include "my_str.h"

text_box_t *text_box_create(sfFont *font, sfTexture *rect_texture)
{
    text_box_t *new = NULL;

    new = malloc(sizeof(text_box_t));
    ASSERT_MALLOC(new, NULL);
    new->box = sfRectangleShape_create();
    ASSERT_MALLOC(new->box, NULL);
    sfRectangleShape_setSize(new->box, (sfVector2f){1820, 216});
    sfRectangleShape_setPosition(new->box, (sfVector2f){50, 814});
    new->font = font;
    new->title = sfText_create();
    ASSERT_MALLOC(new->title, NULL);
    sfText_setFont(new->title, font);
    sfText_setCharacterSize(new->title, 32);
    sfText_setPosition(new->title, (sfVector2f){50, 864});
    new->text_line_1 = sfText_create();
    ASSERT_MALLOC(new->text_line_1, NULL);
    sfText_setFont(new->text_line_1, font);
    sfText_setCharacterSize(new->text_line_1, 32);
    sfText_setPosition(new->text_line_1, (sfVector2f){50, 936});
    new->text_line_2 = sfText_create();
    ASSERT_MALLOC(new->text_line_2, NULL);
    sfText_setFont(new->text_line_2, font);
    sfText_setCharacterSize(new->text_line_2, 32);
    sfText_setPosition(new->text_line_2, (sfVector2f){50, 1008});
    new->text_delay = 0;
    new->to_print = NULL;
    new->index = 0;
    return new;
}

char **format_text(char *text)
{
    char **new = NULL;
    int len = 0;
    int size = 1;

    len = my_strlen(text);
    while (len > 0) {
        len -= 50;
        size++;
    }
    new = malloc(sizeof(char *) * size);
    for (int x = 0; x < size - 1; x++) {
        malloc(sizeof(char) * 51);
        for (int y = 0; y < 50; y++) {
            new[x][y] = text[x * 50 + y];
        }
        new[x][50] = '\0';
    }
    new[size - 1] = NULL;
    return new;
}

void text_box_modify(text_box_t *text_box, char *new_title, char *new_text, int text_delay)
{
    text_box->to_print = format_text(new_text);
    text_box->index = 0;
    text_box->text_delay = text_delay;
    sfText_setString(text_box->title, new_title);
    sfText_setString(text_box->text_line_1, text_box->to_print[0]);
    sfText_setString(text_box->text_line_2, text_box->to_print[1]);
}

void text_box_destroy(text_box_t *text_box)
{
    sfRectangleShape_destroy(text_box->box);
    sfFont_destroy(text_box->font);
    sfText_destroy(text_box->title);
    sfText_destroy(text_box->text_line_1);
    sfText_destroy(text_box->text_line_2);
    if (text_box->to_print) {
        for (int i = 0; text_box->to_print[i]; i++) {
            free(text_box->to_print[i]);
        }
        free(text_box->to_print);
    }
    free(text_box);
}
