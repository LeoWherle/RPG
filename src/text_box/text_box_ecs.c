/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** ecs function for text box
*/

#include "item.h"
#include "text_box.h"
#include "errorhandling.h"

void text_box_update(void *item, window_t *window)
{
    text_box_t *text_box = item;

    if (!text_box->to_print || !text_box->to_print[text_box->index]) {
        text_box_modify(text_box, "Nathanael Kimbembe Croissant", "Bonjour, je suis Nathanael Kimbembe Croissant. Je suis actuellement etudiant en premiere annee a Epitech une ecole d'informatique, j'etais anciennement major de promotion mais ce satane Theodore m'as depasse, pourrait tu s'il te plait te debarraser de lui pour que je puisse retrouver ma grandeur passe?", 0);
        return;
    }
    if (window->event->type == sfEvtMouseButtonReleased) {
        text_box->index += 2;
        if (text_box->to_print[text_box->index]) {
            sfText_setString(text_box->text_line_1,
                            text_box->to_print[text_box->index]);
        } 
        if (text_box->to_print[text_box->index] &&
            text_box->to_print[text_box->index + 1]) {
            sfText_setString(text_box->text_line_2,
                            text_box->to_print[text_box->index + 1]);
        } else
            sfText_setString(text_box->text_line_2, "\0");
    }
    window->event->type = -1;
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
