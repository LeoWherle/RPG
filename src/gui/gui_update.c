/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_update
*/

#include "gui.h"
#include "errorhandling.h"

static void mouse_pos_get(sfVector2i *gmouse_pos, sfEvent const *event)
{
    if (event->type == sfEvtMouseMoved) {
        gmouse_pos->x = event->mouseMove.x;
        gmouse_pos->y = event->mouseMove.y;
    }
    if (event->type == sfEvtMouseButtonPressed ||
event->type == sfEvtMouseButtonReleased) {
        gmouse_pos->x = event->mouseButton.x;
        gmouse_pos->y = event->mouseButton.y;
    }
}

INLINE_STATIC void reset_state(gui_t *gui, window_t *screen)
{
    if (screen->event->type == sfEvtMouseMoved) {
        gui->state = gui_state_unset(HOVER | PRESSED, gui->state);
    }
}

void update_one(gui_t *gui, window_t *screen)
{
    sfFloatRect box = {0, 0, 0, 0};
    sfVector2f mouse_pos = {0, 0};
    sfVector2i evnt_mouse_pos = {0, 0};

    mouse_pos_get(&evnt_mouse_pos, screen->event);
    box = sfRectangleShape_getGlobalBounds(gui->shape);
    mouse_pos = sfRenderWindow_mapPixelToCoords(screen->window, evnt_mouse_pos,
                                                screen->view);
    if (sfFloatRect_contains(&box, mouse_pos.x, mouse_pos.y)) {
        update_events(gui, screen);
    } else {
        reset_state(gui, screen);
    }
    special_interaction(gui, screen);
}

static void recursive_update(gui_t *gui, node_t *node, window_t *screen)
{
    if (node == NULL)
        return;
    recursive_update(gui, node->next, screen);
    gui_update(node->data, screen, 0);
}

void gui_update(void *gui_void, window_t *game, UNUSED float dt)
{
    gui_t *gui = (gui_t *)gui_void;

    if (gui == NULL)
        return;
    if (gui_state_is(INVISIBLE | DISABLED, gui->state))
        return;
    if (gui->sub_gui_list != NULL) {
        recursive_update(gui, gui->sub_gui_list->head, game);
    }
    update_one(gui, game);
    return;
}
