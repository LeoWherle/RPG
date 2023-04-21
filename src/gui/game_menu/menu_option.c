/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_option
*/

#include "gui.h"
#include "menu_values.h"

static gui_t *menu_create_option_buttons(gui_t *option_hud, window_t *screen)
{
    gui_t *fonctionnality = NULL;
    gui_t *background = NULL;

    background = gui_sub_create((sfVector2f){0, 0}, NULL, option_hud);
    sfRectangleShape_setSize(background->shape, (sfVector2f){1920, 1080});
    sfRectangleShape_setFillColor(background->shape, SHADOW_COLOR);
    fonctionnality = create_option_volume(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_fullscreen(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_save(option_hud, screen);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_winsize(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    fonctionnality = create_option_tutorial(option_hud);
    ASSERT_POINTER(fonctionnality, NULL)
    return option_hud;
}

gui_t *menu_create_option(gui_t *hud, window_t *screen)
{
    gui_t *option = NULL;
    gui_t *option_hud = NULL;

    option = gui_sub_create(GUIPOS_SETNGS, NULL, hud);
    ASSERT_POINTER(option, NULL);
    option->type = GUI_OPTIONS;
    option_hud = gui_sub_create((sfVector2f){1, 1}, NULL, option);
    ASSERT_POINTER(option_hud, NULL);
    SWAP_VISIBILITY(option_hud->state);
    option_hud->type = GUI_OPTIONS_HUD;
    option_hud->interactor = screen;
    option_hud = menu_create_option_buttons(option_hud, screen);
    ASSERT_POINTER(option_hud, NULL);
    return hud;
}
