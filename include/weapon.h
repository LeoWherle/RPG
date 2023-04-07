/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** weapon
*/

#include "collision.h"

#ifndef WEAPON_H
    #define WEAPON_H

    typedef struct weapon {
        collider_t *hitbox;
        sfRectangleShape *weapon;
        bool activated;
        float cooldown;
        int strenght;
    } weapon_t;

#endif /*WEAPON_H*/
