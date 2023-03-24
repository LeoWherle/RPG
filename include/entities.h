/*
** EPITECH PROJECT, 2023
** My_RPG
** File description:
** entites header
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include "item.h"

#ifndef ENTITIES_H
    #define ENTITIES_H

    enum entity_type {
        PLAYER,
        ENEMY,
        NPC,
        ITEM,
        OTHER
    };

    enum animation_type {
        IDLE,
        WALK,
        ATTACK,
        DEATH
    };

    typedef struct stats {
        int hp;
        int atk;
        int def;
        int luck;
        int speed;
        float atk_speed;
    } stats_t;

    typedef struct entity {
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f pos;
        sfFloatRect anim;
        enum entity_type type;
        enum animation_type animation;
        stats_t stats;
        dependency_t *depend;
        void (*move)(struct entity *, sfEvent);
        void (*anim)(struct entity *, sfEvent);
        void (*action)(struct entity *, sfEvent);
    } entity_t;

#endif /* !ENTITIES_H */
