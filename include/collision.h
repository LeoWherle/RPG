/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** collision
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "chained_list.h"

#ifndef COLLISION_H
    #define COLLISION_H

    typedef enum tag {
        NONE,
        SOLID,
        HITBOX,
        HURTBOX,
        DEATHBOX,
        INTERACTION,
    } tag_t;

    typedef struct collider {
        sfFloatRect *hitbox;
        tag_t type;
        list_t *to_collide;
        bool activated;
        void *owner;
    } collider_t;

    collider_t *collision_check(collider_t *to_check, tag_t tag);
    collider_t *collider_create(sfFloatRect *hitbox, tag_t type,
                                bool activate, void *owner);
    void collider_destroy(collider_t *collider);

#endif /*COLLISION_H*/
