/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_specific_interaction
*/

#include "gui.h"

static void inventory_interaction(gui_t *gui, window_t *screen)
{
    if (screen->event->type == sfEvtKeyReleased &&
        screen->event->key.code == sfKeyE) {
        SWAP_VISIBILITY(((gui_t *)(gui->sub_gui_list->head->data))->state);
        screen->event->type = (sfEventType)-1;
    }
    if (!IS_INVISIBLE(((gui_t *)(gui->sub_gui_list->head->data))->state)) {
        screen->event->type = (sfEventType)-1;
    }
}

static void option_interaction(gui_t *gui, window_t *screen)
{
    if (screen->event->type == sfEvtKeyReleased &&
        screen->event->key.code == sfKeyEscape) {
        SWAP_VISIBILITY(((gui_t *)(gui->sub_gui_list->head->data))->state);
        screen->event->type = (sfEventType)-1;
    }
    if (!IS_INVISIBLE(((gui_t *)(gui->sub_gui_list->head->data))->state)) {
        screen->event->type = (sfEventType)-1;
    }
}

void special_interaction(gui_t *gui, window_t *screen)
{
    if (gui->type == GUI_OPTIONS) {
        option_interaction(gui, screen);
    }
    if (gui->type == GUI_INVENTORY) {
        inventory_interaction(gui, screen);
    }
}
