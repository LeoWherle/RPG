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
    #include "weapon.h"

    #define IS_SELECTED(gui_state) gui_state_is(gui_state, SELECTED)
    #define IS_INVISIBLE(gui_state) gui_state_is(INVISIBLE, gui_state)
    #define SWAP_VISIBILITY(gui_state) gui_state ^= INVISIBLE

    #define SHADOW_COLOR ((sfColor){30, 30, 30, 120})

    #define INV_SPACING 100

    #define INV_POS_X INV_SPACING * INV_HEIGHT
    #define INV_POS_Y INV_SPACING * INV_WIDTH
    #define INV_POS ((sfVector2f){INV_POS_X, INV_POS_Y})

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
        GUI_EXP_BAR,
        GUI_WEAPON,
        GUI_INVENTORY,
        GUI_ITEM_DISPLAY,
        GUI_INV_STATS,
        GU_SLOT,
        GUI_OPTIONS,
        GUI_OPTIONS_HUD,
        GUI_HUD,
        GUI_INV_DISPLAY,
    } gui_type_t;

    typedef struct inventory_slot_s {
        int slot_id;
        inventory_t *inventory;
    } inventory_slot_t;

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
        void (*interaction)(void *self, window_t *screen);
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
     * @brief iterate through the gui and draw all the items trough the list of
     * items
     *
     * @param gui the gui to draw and it's sub gui's
     * @param window the window to draw the gui on
     */
    void gui_draw(void *gui, window_t *window);

    void draw_inventory_items(gui_t *gui, window_t *screen);
    ///////////////////////////// INTERACTION /////////////////////////////

    // calls the function that makes the interactions (recursive)
    void gui_update(void *gui_void, window_t *game, UNUSED float dt);
    void title_screen_update(void *gui_void, window_t *game, UNUSED float dt);
    void update_one(gui_t *gui, window_t *screen);

    ///// EMPTY INTERACTION /////
    void gui_empty_interaction(void *self, window_t *window);

    void update_events(gui_t *gui, window_t *screen);

    ///// HOVER /////
    void gui_hover(gui_t *gui, window_t *window);

    void gui_pressed(gui_t *gui, window_t *window);

    ///// S¨PECIFIC INTERACTION //////

    void special_interaction(gui_t *gui, window_t *screen);

    // absorb clicks, and allows to select a button
    void menu_update(gui_t *self, window_t *);

    void close_menu(gui_t *self, window_t *, gui_t *menu);

    //// SPECIFIC MENU CREATION ////

    gui_t *create_gui(window_t *screen);

    gui_t *bars_init(gui_t *hud, item_t *player_item);
    void edit_health_bar(gui_t *gui);

    gui_t *exp_init(gui_t *hud, item_t *player_item);
    void edit_exp_bar(gui_t *gui);
    void edit_inventory(gui_t *gui);
    gui_t *create_stats(gui_t *inventory, window_t *screen);

    void volume_0(UNUSED void *self, UNUSED window_t *screen);
    void volume_25(UNUSED void *self, UNUSED window_t *screen);
    void volume_50(UNUSED void *self, UNUSED window_t *screen);
    void volume_75(UNUSED void *self, UNUSED window_t *screen);
    void volume_100(UNUSED void *self, UNUSED window_t *screen);

    void set_fullscreen(UNUSED void *self, window_t *screen);
    void set_normal_screen(UNUSED void *self, window_t *screen);
    void set_1920_1080(UNUSED void *self, window_t *screen);
    void set_960_540(UNUSED void *self, window_t *screen);

    void save_button(UNUSED void *self, window_t *screen);
    void load_button(UNUSED void *self, window_t *screen);
    void exit_button(UNUSED void *self, window_t *screen);
#endif /* !MENU_H_ */
