/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** ecs function for text box
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "item.h"
#include "text_box.h"
#include "errorhandling.h"

void text_box_update(void *item, window_t *window)
{
    text_box_t *text_box = item;

    if (!text_box->to_print)
        return;
    if (window->event->type == sfEvtMouseButtonReleased)
        text_box->index += 2;
    window->event->type = -1;
    if (!text_box->to_print[text_box->index]) {
        for (int i = 0; text_box->to_print[i]; i++)
            free(text_box->to_print[i]);
        free(text_box->to_print);
        text_box->to_print = NULL;
        return;
    }
    sfText_setString(text_box->text_line_1,
                        text_box->to_print[text_box->index]);
    sfText_setString(text_box->text_line_2,
                    text_box->to_print[text_box->index + 1]);
}

void text_box_print(void *item, window_t *win)
{
    text_box_t *text_box = item;
    sfVector2f pos = {0};

    if (text_box->to_print) {
        pos = sfView_getCenter(win->view);
        sfRectangleShape_setPosition(text_box->box,
                                    (sfVector2f){pos.x - 910, pos.y + 274});
        sfRenderWindow_drawRectangleShape(win->window, text_box->box, NULL);
        sfText_setPosition(text_box->title,
                            (sfVector2f){pos.x - 910, pos.y + 288});
        sfRenderWindow_drawText(win->window, text_box->title, NULL);
        sfText_setPosition(text_box->text_line_1,
                            (sfVector2f){pos.x - 910, pos.y + 360});
        sfRenderWindow_drawText(win->window, text_box->text_line_1, NULL);
        sfText_setPosition(text_box->text_line_2,
                            (sfVector2f){pos.x - 910, pos.y + 432});
        sfRenderWindow_drawText(win->window, text_box->text_line_2, NULL);
    }
}
