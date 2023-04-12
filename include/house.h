/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** village pos
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#ifndef VILLAGE_H_
    #define VILLAGE_H_
    #define TILE_NB_VILL 7
    #define VOID_POS ((sfIntRect){0, 0, 20, 20})
    #define FLOOR_POS ((sfIntRect){0, 231, 20, 20})
    #define ROOM_POS ((sfIntRect){0, 0, 204, 194})
    #define BED_POS ((sfIntRect){0, 231, 20, 20})
    #define CHEST_POS ((sfIntRect){218, 88, 18, 17})
    #define CABINET_POS ((sfIntRect){209, 8, 35, 53})
    #define SOLID_POS ((sfIntRect){0, 0, 0, 0})

#endif /* !VILLAGE_H_ */
