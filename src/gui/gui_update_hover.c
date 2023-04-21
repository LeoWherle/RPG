/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_update_hover
*/

#include "gui.h"

void update_events(gui_t *gui, window_t *screen)
{
    if (screen->event->type == sfEvtMouseMoved) {
        gui->state = gui_state_set(HOVER, gui->state);
    }
    if (screen->event->type == sfEvtMouseButtonPressed) {
        gui->state = gui_state_set(PRESSED, gui->state);
    }
    if (screen->event->type == sfEvtMouseButtonReleased) {
        gui->state = gui_state_unset(PRESSED, gui->state);
        if (gui->interaction != NULL) {
            gui->interaction(gui, screen);
        }
    }
}
