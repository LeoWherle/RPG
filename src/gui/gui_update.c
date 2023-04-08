/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_update
*/

#include "gui.h"

void gui_update(gui_t *gui, window_t *game)
{
    node_t *node = NULL;

    if (gui == NULL)
        return;
    if (gui_state_is(INVISIBLE | DISABLED, gui->state))
        return;
    if (gui->sub_gui_list == NULL)
        return;
    for (node = gui->sub_gui_list->head; node != NULL; node = node->next)
        gui_update(node->data, game);
    return;
}
