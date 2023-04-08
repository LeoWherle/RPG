/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_draw
*/

#include <SFML/Graphics.h>
#include "gui.h"
#include "errorhandling.h"
#include "item.h"
#include "entities.h"

static void edit_health_bar(gui_t *gui)
{
    static int prev_width = -1;
    stats_t *stats = (stats_t *)gui->interactor;
    float health = stats->hp / PLAYER_HP;
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

void gui_draw_one(void *gui_item, window_t *screen)
{
    gui_t *gui = (gui_t *)gui_item;
    if (gui->shape == NULL)
        return;
    sfVector2f hudsize = sfRectangleShape_getSize(gui->shape);
    sfVector2f viewsize = sfView_getSize(screen->view);
    sfVector2f viewcenter = sfView_getCenter(screen->view);
    float hudx = viewcenter.x + (viewsize.x * gui->rel_pos.x) - (hudsize.x / 2);
    float hudy = viewcenter.y + (viewsize.y * gui->rel_pos.y) - (hudsize.y / 2);

    if (gui->type == GUI_HEALTH_BAR)
        edit_health_bar(gui);
    sfRectangleShape_setPosition(gui->shape, (sfVector2f){hudx, hudy});
    sfRenderWindow_drawRectangleShape(screen->window, gui->shape, NULL);
}

void gui_draw(void *gui_item, window_t *screen)
{
    gui_t *gui = (gui_t *)gui_item;
    node_t *node = NULL;

    if (gui == NULL)
        return;
    if (gui_state_is(INVISIBLE, gui->state))
        return;
    gui_draw_one(gui, screen);
    if (gui->sub_gui_list == NULL)
        return;
    for (node = gui->sub_gui_list->head; node != NULL; node = node->next)
        gui_draw(node->data, screen);
    return;
}
