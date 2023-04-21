/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_option_volume
*/

#include "gui.h"
#include "menu_values.h"

gui_t *create_option_volume(gui_t *option)
{
    gui_t *volume = NULL;

    volume = gui_sub_create(OPOS_VOL1, VOLUME_0, option);
    ASSERT_POINTER(volume, NULL)
    volume->interaction = &volume_0;
    volume = gui_sub_create(OPOS_VOL2, VOLUME_25, option);
    ASSERT_POINTER(volume, NULL)
    volume->interaction = &volume_25;
    volume = gui_sub_create(OPOS_VOL3, VOLUME_50, option);
    ASSERT_POINTER(volume, NULL)
    volume->interaction = &volume_50;
    volume = gui_sub_create(OPOS_VOL4, VOLUME_75, option);
    ASSERT_POINTER(volume, NULL)
    volume->interaction = &volume_75;
    volume = gui_sub_create(OPOS_VOL5, VOLUME_100, option);
    ASSERT_POINTER(volume, NULL)
    volume->interaction = &volume_100;
    volume = create_option_text(option, "Volume %:", OPOS_VOLTXT);
    return option;
}

gui_t *create_option_fullscreen(gui_t *option_hud)
{
    gui_t *fullscreen = NULL;

    fullscreen = gui_sub_create(OPOS_FULLSCRN, ON, option_hud);
    ASSERT_POINTER(fullscreen, NULL)
    fullscreen->interaction = &set_fullscreen;
    fullscreen = gui_sub_create(OPOS_WINDOW, OFF, option_hud);
    ASSERT_POINTER(fullscreen, NULL)
    fullscreen->interaction = &set_normal_screen;
    fullscreen = create_option_text(option_hud, "Fullscreen  :",
                                    OPOS_FULLTXT);
    ASSERT_MALLOC(fullscreen, NULL);
    return option_hud;
}

gui_t *create_option_save(gui_t *option_hud, UNUSED window_t *screen)
{
    gui_t *save_b = NULL;
    gui_t *load_b = NULL;
    gui_t *exit_b = NULL;

    save_b = gui_sub_create(OPOS_SAVE, SAVE, option_hud);
    ASSERT_POINTER(save_b, NULL)
    save_b->interaction = &save_button;
    load_b = gui_sub_create(OPOS_LOAD, LOAD, option_hud);
    ASSERT_POINTER(load_b, NULL)
    load_b->interaction = &load_button;
    exit_b = gui_sub_create(OPOS_EXIT, EXIT_B, option_hud);
    ASSERT_POINTER(exit_b, NULL)
    exit_b->interaction = &exit_button;
    return option_hud;
}

gui_t *create_option_winsize(gui_t *option_hud)
{
    gui_t *win_size = NULL;

    win_size = gui_sub_create(OPOS_RES1, RES_1920, option_hud);
    ASSERT_POINTER(win_size, NULL)
    win_size->interaction = &set_1920_1080 ;
    win_size = gui_sub_create(OPOS_RES2, RES_1600, option_hud);
    ASSERT_POINTER(win_size, NULL)
    win_size->interaction = &set_960_540;
    win_size = create_option_text(option_hud, "Window size  :",
                                    OPOS_RESTXT);
    ASSERT_MALLOC(win_size, NULL)
    return option_hud;
}

gui_t *create_option_tutorial(gui_t *option_hud)
{
    gui_t *tutorial = NULL;

    tutorial = gui_sub_create(OPOS_TUTO, TUTORIAL, option_hud);
    ASSERT_POINTER(tutorial, NULL);
    sfRectangleShape_setScale(tutorial->shape, (sfVector2f){0.4, 0.4});
    tutorial->state = DISABLED;
    tutorial->interaction = NULL;
    return option_hud;
}
