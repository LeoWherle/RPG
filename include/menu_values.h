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

    #define GUI_TOP_LEFT ((sfVector2f){-0.5, -0.5})
    #define GUIPOS_INVTRY ((sfVector2f){-0.48, 0.4})
    #define GUIPOS_SETNGS ((sfVector2f){-0.48, 0.45})
    #define GUIPOS_HEALTH ((sfVector2f){-0.26, -0.47})
    #define GUIPOS_WEAPON ((sfVector2f){0.45, 0.45})

    #define GUIPOS_PLAY ((sfVector2f){-.1, -2.5})
    #define GUIPOS_SETTINGS ((sfVector2f){-.1, -.1})
    #define GUIPOS_CREDIT ((sfVector2f){-.1, .1})
    #define GUIPOS_EXIT ((sfVector2f){-.1, 2.5})

    gui_t *menu_create_all( void *menu_data,
                            void *player_data,
                            window_t *window);

#endif /* !MENU_VALUES_H_ */
