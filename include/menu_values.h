/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** menu_values
*/

#ifndef MENU_VALUES_H_
    #define MENU_VALUES_H_

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include "gui.h"
    #include "item.h"

    #define GUI_TOP_LEFT ((sfVector2f){-0.4, -0.4})
    #define GUIPOS_CENTER ((sfVector2f){0, 0})
    #define GUIPOS_BACKGROUND ((sfVector2f){0.3, 0.4})
    #define GUIPOS_INVTRY ((sfVector2f){-0.48, 0.4})
    #define GUIPOS_SETNGS ((sfVector2f){-0.48, 0.45})
    #define GUIPOS_HEALTH ((sfVector2f){-0.26, -0.47})
    #define GUIPOS_EXP ((sfVector2f){-0.26, -0.42})
    #define GUIPOS_WEAPON ((sfVector2f){0.45, 0.45})

    #define GUIPOS_PLAY ((sfVector2f){-0.3, -0.2})
    #define GUIPOS_NEW ((sfVector2f){-0.32, -0.065})
    #define GUIPOS_SETTINGS ((sfVector2f){-0.32, 0.065})
    #define GUIPOS_EXIT ((sfVector2f){-0.325, 0.2})
    #define GUIPOS_CREDIT ((sfVector2f){-.1, .1})

    #define MENU_B "assets/menu/"
    #define BACKGRN MENU_B "background_and_text.png"
    #define PLAY MENU_B "play.png"
    #define EXIT MENU_B "exit.png"
    #define NEW MENU_B "new.png"
    #define OPTION MENU_B "options.png"


/////////////////////////OPTION/////////////////////////

    #define OPOS_VOL1 ((sfVector2f){-0.08, -0.2})
    #define OPOS_VOL2 ((sfVector2f){-0.04, -0.2})
    #define OPOS_VOL3 ((sfVector2f){0, -0.2})
    #define OPOS_VOL4 ((sfVector2f){0.04, -0.2})
    #define OPOS_VOL5 ((sfVector2f){0.08, -0.2})
    #define OPOS_VOLTXT ((sfVector2f){-0.26, -0.236})

    #define VOLUME_0 MENU_B "0_vol.png"
    #define VOLUME_25 MENU_B "25_vol.png"
    #define VOLUME_50 MENU_B "50_vol.png"
    #define VOLUME_75 MENU_B "75_vol.png"
    #define VOLUME_100 MENU_B "100_vol.png"

    #define OPOS_FULLSCRN ((sfVector2f){-0.08, -0.1})
    #define OPOS_WINDOW ((sfVector2f){-0.04, -0.1})
    #define OPOS_FULLTXT ((sfVector2f){-0.33, -0.136})

    #define ON MENU_B "on.png"
    #define OFF MENU_B "off.png"

    #define OPOS_RES1 ((sfVector2f){-0.064, 0})
    #define OPOS_RES2 ((sfVector2f){0, 0})
    #define OPOS_RESTXT ((sfVector2f){-0.35, -0.036})

    #define RES_1920 MENU_B "1920_size.png"
    #define RES_1600 MENU_B "960_size.png"

    #define OPOS_SAVE ((sfVector2f){-0.12, -0.45})
    #define OPOS_LOAD ((sfVector2f){0, -0.45})
    #define OPOS_EXIT ((sfVector2f){0.12, -0.45})
    #define OPOS_SAVETXT ((sfVector2f){-0.325, 0.264})

    #define SAVE MENU_B "save.png"
    #define LOAD MENU_B "load.png"
    #define EXIT_B MENU_B "exit.png"

    #define OPOS_TUTO ((sfVector2f){0.4, 0.5})
    #define TUTORIAL MENU_B "commands2.png"

    gui_t *menu_create_all( void *menu_data,
                            void *player_data,
                            window_t *window);


    /////////////////////////INVENTORY MENU/////////////////////////
    gui_t *menu_create_inventory(gui_t *gobal_menu,
                                window_t *screen,
                                item_t *player_item);


    /////////////////////////TITLESCREEN/////////////////////////
    gui_t *menu_create_titlescreen(window_t *window, gui_t *title_screen);
    gui_t *menu_create_titlescrn_btn(gui_t *title_screen, window_t *window);

    /////////////////////////OPTION/////////////////////////
    gui_t *menu_create_option(gui_t *hud, window_t *screen);
    gui_t *create_option_volume(gui_t *option_hud);
    gui_t *create_option_fullscreen(gui_t *option_hud);
    gui_t *create_option_save(gui_t *option_hud, window_t *screen);
    gui_t *create_option_winsize(gui_t *option_hud);
    gui_t *create_option_tutorial(gui_t *option_hud);

    gui_t *menu_create_opt_tt_buttons(gui_t *option_hud, window_t *screen);

    void open_menu(void *data, window_t *gui);
    /////////////////////////TEXT/////////////////////////
    gui_t *create_option_text(gui_t *inv,
                            char *str,
                            sfVector2f pos);

#endif /* !MENU_VALUES_H_ */
