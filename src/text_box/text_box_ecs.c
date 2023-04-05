/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** ecs function for text box
*/

#include "item.h"
#include "text_box.h"

void text_box_update(void *item, window_t *window)
{
    text_box_t *text_box = item;
    sfEvent *event = NULL;

    if (event->type == -1 || !text_box->to_print ||
        !text_box->to_print[text_box->index]) {
        return;
    }
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        text_box->index += 2;
        sfText_setString(text_box->text_line_1,
                        text_box->to_print[text_box->index]);
        sfText_setString(text_box->text_line_2,
                        text_box->to_print[text_box->index + 1]);
    }
    event->type = -1;
}

void text_box_print(void *item, window_t *win)
{
    text_box_t *text_box = item;

    if (text_box->to_print && text_box->to_print[text_box->index]) {
        sfRenderWindow_drawRectangleShape(win->window, text_box->box, NULL);
        sfRenderWindow_drawText(win->window, text_box->title, NULL);
        sfRenderWindow_drawText(win->window, text_box->text_line_1, NULL);
        sfRenderWindow_drawText(win->window, text_box->text_line_2, NULL);
    }
}
