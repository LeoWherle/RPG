/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu
*/


#ifndef MENU_H_
    #define MENU_H_
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include "chained_list.h"
    #include "item.h"

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
        INVISIBLE = 1 << 5,
        // Make the button focused | on or off switch
        SELECTED = 1 << 6,
    } gui_state_t;

    typedef enum gui_type_e {
        GUI_BASIC = 0,
        GUI_HEALTH_BAR,
        GUI_WEAPON,
    } gui_type_t;

    struct gui_assets {
        sfTexture *select;
        sfSound *click;
    };

    typedef struct gui_s {
        gui_type_t type;
        gui_state_t state;
        /**
         * @param relative_pos relative position of the gui from the sfView
         * (-0.5 to 0.5)
         */
        sfVector2f rel_pos;
        sfRectangleShape *shape;
        sfText *text;
        sfFont *font;
        sfSound *sound;
        sfTexture *texture;
        /**
         * @param interactors list of items from the ecs
         */
        list_t *sub_gui_list;
        /**
         * @brief object that the gui depends on to make the interaction
         */
        void *interactor;
        struct gui_assets assets;
        void (*interaction)(void *self);
    } gui_t;

    ///////////////////////////// INIT /////////////////////////////
    gui_t *gui_init(void);
    gui_t *gui_create_default(void);

    void gui_destroy(void *gui);
    /**
     * @brief inintialize a basic gui with a texture and a relative position
     *
     * @param rel_pos the relative position of the gui from the sfView
     * (-0.5 to 0.5)
     * @param text_path the path to the texture to load for the gui
     * @return gui_t* the gui created or NULL if an error occured
     */
    gui_t *gui_create(sfVector2f rel_pos, char *text_path);

    /**
     * @brief create a gui with a texture and a relative position and a parent
     *
     * @param rel_pos the relative position of the gui from the sfView
     * (-0.5 to 0.5)
     * @param texture the path to the texture to load for the gui
     * @param parent the parent gui of the gui
     * @return gui_t* the gui created or NULL if an error occured
     */
    gui_t *gui_sub_create(sfVector2f rel_pos, char *texture, gui_t *parent);

    ///////////////////////////// STATES /////////////////////////////

    int gui_state_is(gui_state_t status, gui_state_t state);
    gui_state_t gui_state_set(gui_state_t status, gui_state_t state);
    gui_state_t gui_state_unset(gui_state_t status, gui_state_t state);

    ///////////////////////////// SETTERS /////////////////////////////
    gui_t *gui_set_texture(gui_t *gui, char *texture_path);

    ///////////////////////////// DRAWING /////////////////////////////

    /**
     * @brief iterate through the gui and draw all the items trough the list of items
     *
     * @param gui the gui to draw and it's sub gui's
     * @param window the window to draw the gui on
     */
    void gui_draw(void *gui, window_t *window);

    ///////////////////////////// INTERACTION /////////////////////////////

    // calls the function that makes the interactions (recursive)
    void gui_update(void *gui, window_t *window);

    ///// EMPTY INTERACTION /////
    void gui_empty_interaction(void *self, window_t *window);

    ///// HOVER /////
    void gui_hover(gui_t *gui, window_t *window);

    void gui_pressed(gui_t *gui, window_t *window);

    ///// S¨PECIFIC INTERACTION //////

    // absorb clicks, and allows to select a button
    void menu_update(gui_t *self, window_t *);

    void close_menu(gui_t *self, window_t *, gui_t *menu);
#endif /* !MENU_H_ */
