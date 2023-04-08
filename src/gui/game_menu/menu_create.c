/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_create
*/

#include "menu_values.h"
#include "entities.h"


// implement exit button
// implement item slots display <- needs player inventory
// implement background display (transparent)
// implement button
gui_t *menu_create_inventory(gui_t *gobal_menu)
{
    gui_t *inventory = NULL;

    inventory = gui_sub_create((sfVector2f){0, 0}, NULL, gobal_menu);
    ASSERT_POINTER(inventory, NULL);
    return inventory;
}

// implement inventory button
// implement settings button
// implement health display
// implement weapon display
gui_t *menu_create_hud(gui_t *global_menu)
{
    gui_t *hud = NULL;
    gui_t *inventory = NULL;
    gui_t *settings = NULL;
    gui_t *health = NULL;
    gui_t *weapon = NULL;

    hud = gui_sub_create((sfVector2f){1, 1}, NULL, global_menu);
    ASSERT_POINTER(hud, NULL);
    inventory = menu_create_inventory(hud);
    ASSERT_POINTER(inventory, NULL);
    settings = gui_sub_create(GUIPOS_SETNGS, "assets/menu/settings.png", hud);
    ASSERT_POINTER(settings, NULL);
    health = gui_sub_create(GUIPOS_HEALTH, "assets/menu/health.png", hud);
    ASSERT_POINTER(health, NULL);
    weapon = gui_sub_create(GUIPOS_WEAPON, "assets/menu/weapon.png", hud);
    ASSERT_POINTER(weapon, NULL);
    return global_menu;
}

// implement play button
// implement settings button
// implement quit button
// implement credits button
// implement background display
gui_t *menu_create_main(gui_t *gui)
{
    gui_t *main_menu = NULL;
    gui_t *play_btn = NULL;
    gui_t *settings_btn = NULL;
    gui_t *cretid_btn = NULL;
    gui_t *exit_btn = NULL;

    main_menu = gui_sub_create(GUI_TOP_LEFT, "assets/menu/bAckground", gui);
    ASSERT_POINTER(main_menu, NULL);
    main_menu->interaction = &menu_update;
    play_btn = gui_sub_create(GUIPOS_PLAY, "assets/menu/play.png", main_menu);
    ASSERT_POINTER(play_btn, NULL);
    play_btn->interaction = &close_menu;
    play_btn->interactor = main_menu;
    return NULL;
}

gui_t *menu_create_all(void *menu_data, void *player_data, window_t *window)
{
    gui_t *global_menu = (gui_t *)global_menu;
    entity_t *player = (entity_t *)player_data;

    // global_menu = menu_create_hud(global_menu);
    // ASSERT_POINTER(global_menu, NULL);
    global_menu = menu_create_main(global_menu);
    ASSERT_POINTER(global_menu, NULL)
    return global_menu;
}
