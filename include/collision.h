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
        TRIGGER,
        SOLID,
        HITBOX,
        HURTBOX,
        DEATHBOX,
        INTERACTION,
        PLAYER_HITBOX,
        PLAYER_HURTBOX,
    } tag_t;

    typedef struct collider {
        sfFloatRect *hitbox;
        tag_t type;
        list_t *to_collide;
        bool activated;
        void *owner;
        void (*on_collision_entered)(struct collider *, struct collider *);
    } collider_t;

    void collision_check(collider_t *to_check);
    collider_t *collider_create(sfFloatRect *hitbox, tag_t type,
                                bool activate, void *owner);
    void collider_destroy(collider_t *collider);

    void move_trigger_enter(collider_t *main, collider_t *sub);
    void receive_enemy_damage(collider_t *main, collider_t *sub);
    void receive_player_damage(collider_t *main, collider_t *sub);

#endif /*COLLISION_H*/
