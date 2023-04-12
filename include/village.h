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
    #define TILE_NB_VILL 35
    #define VOID_POS ((sfIntRect){0, 0, 20, 20})
    #define FLOOR_POS ((sfIntRect){20, 120, 20, 20})
    #define WALL_FRONT_POS ((sfIntRect){0, 60, 20, 20})
    #define WALL_BACK_POS ((sfIntRect){120, 60, 20, 20})
    #define WALL_LEFT_POS ((sfIntRect){80, 40, 20, 20})
    #define WALL_RIGHT_POS ((sfIntRect){60, 60, 20, 20})
    #define TOP_LEFT_POS ((sfIntRect){40, 20, 20, 20})
    #define TOP_RIGHT_POS ((sfIntRect){60, 20, 20, 20})
    #define BOT_LEFT_POS ((sfIntRect){20, 20, 20, 20})
    #define BOT_RIGHT_POS ((sfIntRect){80, 20, 20, 20})
    #define UNDER_GRASS_POS ((sfIntRect){260, 40, 20, 20})
    #define UNDER_GRASS_LEFT ((sfIntRect){240, 20, 20, 20})
    #define UNDER_GRASS_RIGHT ((sfIntRect){260, 20, 20, 20})
    #define INTERN_TOP_LEFT ((sfIntRect){80, 100, 20, 20})
    #define INTERN_TOP_RIGHT ((sfIntRect){0, 120, 20, 20})
    #define INTERN_BOT_LEFT ((sfIntRect){100, 100, 20, 20})
    #define INTERN_BOT_RIGHT ((sfIntRect){120, 100, 20, 20})
    #define TREE_HOUSE ((sfIntRect){0, 140, 210, 200})
    #define TREE_TRUNK ((sfIntRect){191, 80, 36, 32})
    #define TREE ((sfIntRect){229, 69, 16, 38})
    #define FRUIT_MERCHANT ((sfIntRect){338, 307, 70, 60})
    #define FLOWER_POT ((sfIntRect){223, 109, 21, 24})
    #define OBSERVATORY ((sfIntRect){380, 3, 110, 171})
    #define TUTORIAL_MAN ((sfIntRect){292, 279, 16, 23})
    #define BIG_HOLE ((sfIntRect){501, 0, 499, 508})
    #define HOLE_ISL ((sfIntRect){140, 119, 20, 20})
    #define BARRIER ((sfIntRect){191, 436, 9, 31})
    #define RED_FLOWER ((sfIntRect){215, 451, 9, 13})
    #define WHITE_FLOWER ((sfIntRect){228, 451, 9, 13})
    #define BLUE_FLOWER ((sfIntRect){249, 450, 9, 13})
    #define BUSH ((sfIntRect){263, 449, 14, 14})
    #define ROCK ((sfIntRect){295, 448, 14, 15})
    #define CAVE_TOWER ((sfIntRect){414, 179, 85, 202})
    #define MAN_BIRD ((sfIntRect){285, 80, 21, 25})
    #define SHOP ((sfIntRect){342, 243, 67, 61})

#endif /* !VILLAGE_H_ */
