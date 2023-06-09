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
        PROJECTILE,
        TELEPORTER_VILLAGE,
        TELEPORTER_CAVE,
        TELEPORTER_ROOM,
        TELEPORTER_BOSS,
    } tag_t;

    typedef struct collider {
        sfFloatRect *hitbox;
        tag_t type;
        list_t *to_collide;
        bool activated;
        void *owner;
        bool (*on_collision_entered)(struct collider *, struct collider *);
    } collider_t;

    void collision_check(collider_t *to_check);
    collider_t *collider_create(sfFloatRect *hitbox, tag_t type,
                                bool activate, void *owner);
    void collider_destroy(collider_t *collider);

    bool move_trigger_enter(collider_t *main, collider_t *sub);
    bool receive_enemy_damage(collider_t *main, collider_t *sub);
    bool receive_player_damage(collider_t *main, collider_t *sub);
    bool player_collision(collider_t *player, collider_t *sub);
    bool projectile_collision(collider_t *main, collider_t *sub);
    bool receive_player_damage_boss(collider_t *main, collider_t *sub);

#endif /*COLLISION_H*/
