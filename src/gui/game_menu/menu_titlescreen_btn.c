/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_titlescreen_btn
*/

#include "gui.h"
#include "menu_values.h"
#include "music_player.h"
#include "save.h"

void play_button(UNUSED void *gui, window_t *screen)
{
    if (screen->event->type == sfEvtMouseButtonReleased &&
        screen->event->mouseButton.button == sfMouseLeft) {
        screen->state = GAME;
        screen->event->type = (sfEventType)-1;
        change_music(NULL, VILLAGE_M);
    }
}

static void quit_button_interaction(UNUSED void *gui, window_t *screen)
{
    if (screen->event->type == sfEvtMouseButtonReleased &&
        screen->event->mouseButton.button == sfMouseLeft) {
        screen->exit = true;
    }
}

static gui_t *menu_add_game_play(gui_t *title_screen)
{
    gui_t *play_btn = NULL;
    gui_t *new_btn = NULL;

    play_btn = gui_sub_create(GUIPOS_PLAY, PLAY, title_screen);
    ASSERT_POINTER(play_btn, NULL);
    sfRectangleShape_setScale(play_btn->shape, (sfVector2f){2, 2});
    play_btn->interaction = &load_button;
    new_btn = gui_sub_create(GUIPOS_NEW, NEW, title_screen);
    ASSERT_POINTER(new_btn, NULL);
    sfRectangleShape_setScale(new_btn->shape, (sfVector2f){2.3, 2.3});
    new_btn->interaction = &play_button;
    return title_screen;
}

static gui_t *menu_add_game_options(gui_t *title_screen, window_t *screen)
{
    gui_t *settings_btn = NULL;
    gui_t *settings_hud = NULL;
    gui_t *quit_btn = NULL;

    quit_btn = gui_sub_create(GUIPOS_EXIT, EXIT, title_screen);
    ASSERT_POINTER(quit_btn, NULL);
    sfRectangleShape_setScale(quit_btn->shape, (sfVector2f){2.3, 2.3});
    quit_btn->interaction = &quit_button_interaction;
    settings_btn = gui_sub_create(GUIPOS_SETTINGS, OPTION, title_screen);
    ASSERT_POINTER(settings_btn, NULL);
    sfRectangleShape_setScale(settings_btn->shape, (sfVector2f){2.3, 2.3});
    settings_btn->type = GUI_OPTIONS;
    settings_hud = gui_sub_create(GUIPOS_CENTER, NULL, settings_btn);
    ASSERT_POINTER(settings_hud, NULL);
    SWAP_VISIBILITY(settings_hud->state);
    settings_btn->interactor = settings_hud;
    settings_btn->interaction = &open_menu;
    settings_hud->type = GUI_OPTIONS_HUD;
    settings_hud = menu_create_opt_tt_buttons(settings_hud, screen);
    return title_screen;
}

gui_t *menu_create_titlescrn_btn(gui_t *title_screen, window_t *window)
{
    title_screen = menu_add_game_play(title_screen);
    ASSERT_POINTER(title_screen, NULL);
    title_screen = menu_add_game_options(title_screen, window);
    ASSERT_POINTER(title_screen, NULL);
    return title_screen;
}
