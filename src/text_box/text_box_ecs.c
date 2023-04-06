/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** ecs function for text box
*/

#include <stdlib.h>
#include "item.h"
#include "text_box.h"
#include "errorhandling.h"

void text_box_update(void *item, window_t *window)
{
    text_box_t *text_box = item;

    if (!text_box->to_print) {
        text_box_modify(text_box, "Nathanael Kimbembe Croissant\0", "Bonjour, je suis Nathanael Kimbembe Croissant.\nJe suis actuellement etudiant en premiere annee a Epitech une ecole d'informatique.\nJ'etais anciennement major de promotion mais ce satane Theodore m'as depasse, pourrait tu s'il te plait te debarraser de lui pour que je puisse retrouver ma grandeur passe?\0", 0);
        return;
    }
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

    if (text_box->to_print) {
        sfRenderWindow_drawRectangleShape(win->window, text_box->box, NULL);
        sfRenderWindow_drawText(win->window, text_box->title, NULL);
        sfRenderWindow_drawText(win->window, text_box->text_line_1, NULL);
        sfRenderWindow_drawText(win->window, text_box->text_line_2, NULL);
    }
}
