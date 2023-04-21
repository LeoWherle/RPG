/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** cave pos
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "room.h"

#ifndef CAVE_H_
    #define CAVE_H_
    #define TILE_NB_CAVE 32
    #define VOID_POS ((sfIntRect){2, 2, 20, 20})
    #define FLOOR_POS ((sfIntRect){142, 2, 20, 20})
    #define WALL_FRONT_POS ((sfIntRect){162, 42, 20, 20})
    #define WALL_BACK_POS ((sfIntRect){42, 2, 20, 20})
    #define WALL_LEFT_POS ((sfIntRect){122, 22, 20, 20})
    #define WALL_RIGHT_POS ((sfIntRect){82, 22, 20, 20})
    #define TOP_LEFT_POS ((sfIntRect){82, 2, 20, 20})
    #define TOP_RIGHT_POS ((sfIntRect){102, 2, 20, 20})
    #define BOT_LEFT_POS ((sfIntRect){142, 22, 20, 20})
    #define BOT_RIGHT_POS ((sfIntRect){162, 22, 20, 20})
    #define DOOR_TOP_OP ((sfIntRect){2, 42, 40, 20})
    #define DOOR_BOT_OP ((sfIntRect){62, 62, 40, 20})
    #define DOOR_TOP_CL ((sfIntRect){42, 42, 40, 20})
    #define DOOR_BOT_CL ((sfIntRect){102, 62, 40, 20})
    #define LITTLE_CRIS_BL ((sfIntRect){62, 82, 20, 20})
    #define LITTLE_CRIS_PI ((sfIntRect){102, 82, 20, 20})
    #define LITTLE_ROCK ((sfIntRect){222, 22, 20, 20})
    #define LITTLE_STICK ((sfIntRect){142, 102, 20, 20})
    #define CHEST ((sfIntRect){162, 2, 20, 20})
    #define INTERN_TOP_LEFT ((sfIntRect){22, 2, 20, 20})
    #define INTERN_TOP_RIGHT ((sfIntRect){62, 2, 20, 20})
    #define INTERN_BOT_LEFT ((sfIntRect){142, 42, 20, 20})
    #define INTERN_BOT_RIGHT ((sfIntRect){182, 42, 20, 20})
    #define ENT_TOP_OP ((sfIntRect){122, 242, 40, 20})
    #define ENT_BOT_OP ((sfIntRect){62, 222, 40, 20})
    #define ENT_TOP_CL ((sfIntRect){162, 242, 40, 20})
    #define ENT_BOT_CL ((sfIntRect){102, 222, 40, 20})
    #define SAVE_PILLAR ((sfIntRect){208, 62, 28, 45})
    #define SAVED_PILLAR ((sfIntRect){236, 62, 28, 45})
    #define TORCH ((sfIntRect){182, 0, 20, 22})
    #define MINERAL ((sfIntRect){0, 122, 28, 29})
    #define EXIT ((sfIntRect){0, 153, 34, 12})

#endif /* !CAVE_H_ */
