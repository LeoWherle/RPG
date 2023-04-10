/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** weapon
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include "collision.h"
#include "item.h"

#ifndef WEAPON_H
    #define WEAPON_H

    typedef struct weapon {
        sfRectangleShape *weapon;
        sfTexture *texture;
        collider_t *hitbox;
        sfFloatRect rect;
        float angle;
        sfVector2f pos;
        bool activated;
        bool imobilisation;
        int strenght;
        float cooldown;
        void (*use)(struct weapon *, window_t *);
    } weapon_t;

    weapon_t *weapon_create_lance(float cooldown, int strenght, sfVector2f size,
                        sfTexture *texture);
    void weapon_destroy(weapon_t *weapon);
    void weapon_use(weapon_t *weapon, window_t *win);
    void lance_use(weapon_t *lance, window_t *win);

#endif /*WEAPON_H*/
