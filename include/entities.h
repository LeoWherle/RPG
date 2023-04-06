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
#include <math.h>
#include "item.h"

#ifndef ENTITIES_H
    #define ENTITIES_H

    #define SQRT 0.70710678118
    #define INTERVAL 0.1
    #define PLAYER_SIZE 3
    #define PLAYER_SPEED 5
    #define PLAYER_ATK_SPEED 1
    #define PLAYER_HP 100
    #define PLAYER_ATK 10
    #define PLAYER_DEF 10
    #define PLAYER_LUCK 10

    enum entity_type {
        PLAYER_E = 0,
        ENEMY,
        NPC,
        ITEM,
        OTHER
    };

    enum animation_type_player {
        FRONT_IDLE = 0,
        SIDE_IDLE,
        BACK_IDLE,
        FRONT_WALK,
        SIDE_WALK,
        BACK_WALK,
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
        enum entity_type type;
        enum animation_type_player animation;
        int facing_right;
        stats_t stats;
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f pos;
        sfIntRect anim_rect;
        sfClock *anim_clock;
        sfTime anim_time;
        dependency_t *depend;
    } entity_t;

    entity_t *create_player(window_t *window);
    void destroy_player(void *entity);
    void move_player(entity_t *player, window_t *window);
    void player_print(void *player, window_t *window);
    void player_update(void *player, window_t *window);
    void set_camera(entity_t *player, window_t *window);
    void update_camera(entity_t *player, window_t *window);

#endif /* !ENTITIES_H */
