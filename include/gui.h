/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu
*/

#include <SFML/Graphics.h>
#include "chained_list.h"
#include "item.h"

#ifndef MENU_H_
    #define MENU_H_

    // bitfield of the button state
    typedef enum gui_state_e {
        GUI_DEFAULT = 0,
        // default state
        GUI_ERROR = 1 << 0,
        // change the color of the button lightly
        HOVER = 1 << 1,
        // change the color of the button
        PRESSED = 1 << 2,
        // Make an interaction
        RELEASED = 1 << 3,
        // Disable the button
        DISABLED = 1 << 4,
        // Make the button visible/hidden
        VISIBLE = 1 << 5,
        // Make the button focused
        FOCUSED = 1 << 6,
    } gui_state_t;

    typedef struct gui_s {
        gui_state_t state;
        sfRectangleShape *shape;
        sfText *text;
        sfFont *font;
        list_t *interactors;
        list_t *items;
    } gui_t;

    gui_t *gui_init(void);
    gui_t *gui_create_default(void);

    void gui_destroy(void *gui);

    int gui_state_is(gui_state_t status, gui_state_t state);
    void gui_state_set(gui_state_t status, gui_state_t *state);
    void gui_state_unset(gui_state_t status, gui_state_t *state);

#endif /* !MENU_H_ */
