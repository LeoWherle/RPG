/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create and delete text box
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include "text_box.h"
#include "errorhandling.h"
#include "my_str.h"

static bool text_box_create_text(text_box_t *new, sfFont *font)
{
    new->font = font;
    new->title = sfText_create();
    ASSERT_MALLOC(new->title, true);
    sfText_setFont(new->title, font);
    sfText_setCharacterSize(new->title, 32);
    new->text_line_1 = sfText_create();
    ASSERT_MALLOC(new->text_line_1, true);
    sfText_setFont(new->text_line_1, font);
    sfText_setCharacterSize(new->text_line_1, 32);
    new->text_line_2 = sfText_create();
    ASSERT_MALLOC(new->text_line_2, true);
    sfText_setFont(new->text_line_2, font);
    return false;
}

text_box_t *text_box_create(sfFont *font, sfTexture *rect_texture)
{
    text_box_t *new = NULL;

    new = malloc(sizeof(text_box_t));
    ASSERT_MALLOC(new, NULL);
    new->box = sfRectangleShape_create();
    ASSERT_MALLOC(new->box, NULL);
    sfRectangleShape_setSize(new->box, (sfVector2f){1820, 216});
    if (rect_texture)
        sfRectangleShape_setTexture(new->box, rect_texture, sfTrue);
    else
        sfRectangleShape_setFillColor(new->box, sfBlack);
    if (text_box_create_text(new, font))
        return NULL;
    new->text_delay = 0;
    new->to_print = NULL;
    new->index = 0;
    return new;
}

void text_box_destroy(void *item)
{
    text_box_t *text_box = item;

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
