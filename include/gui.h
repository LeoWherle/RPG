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
        // Make the button focused on or off switch
        SELECTED = 1 << 6,
    } gui_state_t;

    typedef struct gui_s {
        gui_state_t state;
        /**
         * @param relative_pos relative position of the gui from the sfView
         * (-0.5 to 0.5)
         */
        sfVector2f relative_pos;
        /**
         * @brief 
         */
        sfRectangleShape *shape;
        /**
         * @param interactors list of items from the ecs
         */
        list_t *interactors;
        /**
         * @brief object that the gui depends on to make the interaction
         */
        void *dependency;
    } gui_t;


    ///////////////////////////// INIT /////////////////////////////
    gui_t *gui_init(void);
    gui_t *gui_create_default(void);

    void gui_destroy(void *gui);


    ///////////////////////////// STATES /////////////////////////////
    int gui_state_is(gui_state_t status, gui_state_t state);
    void gui_state_set(gui_state_t status, gui_state_t *state);
    void gui_state_unset(gui_state_t status, gui_state_t *state);

    ///////////////////////////// SETTERS /////////////////////////////
    void gui_set_texture(gui_t *gui, char *texture_path);

    /**
     * @brief inintialize a basic gui with a texture and a relative position
     *
     * @param rel_pos the relative position of the gui from the sfView (-0.5 to 0.5)
     * @param text_path the path to the texture to load for the gui
     * @return gui_t* the gui created or NULL if an error occured
     */
    gui_t *gui_create_basic(sfVector2f rel_pos, char *text_path);

    ///////////////////////////// DRAWING /////////////////////////////

    /**
     * @brief iterate through the gui and draw all the items trough the list of items
     * 
     * @param gui 
     * @param window 
     */
    void gui_draw(gui_t *gui, window_t *window);

#endif /* !MENU_H_ */
