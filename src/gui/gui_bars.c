/*
** EPITECH PROJECT, 2023
** B-MUL-200-TLS-2-1-myrpg-leo.wehrle [WSL: fedora]
** File description:
** gui_bars
*/

#include "gui.h"
#include "errorhandling.h"
#include "item.h"
#include "entities.h"

void edit_health_bar(gui_t *gui)
{
    static int prev_width = -1;
    stats_t *stats = (stats_t *)gui->interactor;
    float health = stats->hp / stats->max_hp;
    sfIntRect txt_rect = {0, 0, 0, 0};

    txt_rect = sfRectangleShape_getTextureRect(gui->shape);
    if (prev_width != txt_rect.width) {
        txt_rect.width *= health;
        prev_width = txt_rect.width;
    }
    sfRectangleShape_setScale(gui->shape, (sfVector2f){health * 0.7, 0.7});
    sfRectangleShape_setTextureRect(gui->shape, txt_rect);
    return;
}

void edit_exp_bar(gui_t *gui)
{
    static int prev_width = -1;
    stats_t *stats = (stats_t *)gui->interactor;
    float exp = stats->exp.current_exp / stats->exp.exp_cap;
    sfIntRect txt_rect = {0, 0, 0, 0};

    txt_rect = sfRectangleShape_getTextureRect(gui->shape);
    if (prev_width != txt_rect.width) {
        txt_rect.width *= (1 - exp);
        prev_width = txt_rect.width;
    }
    sfRectangleShape_setScale(gui->shape, (sfVector2f){exp * 0.7, 0.7});
    sfRectangleShape_setTextureRect(gui->shape, txt_rect);
    return;
}
