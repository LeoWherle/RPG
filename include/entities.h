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
#include "collision.h"

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
        FRONT_DASH,
        SIDE_DASH,
        BACK_DASH,
    };

    typedef struct stats {
        float hp;
        float atk;
        float def;
        float luck;
        float speed;
        float atk_speed;
    } stats_t;

    typedef struct player_dash {
        int is_dashing;
        int vector_lock;
        float dash_cooldown;
        sfVector2f dash_vector;
        sfTime dash_start;
        sfTime dash_time;
    } player_dash_t;

    typedef struct entity {
        enum entity_type type;
        enum animation_type_player animation;
        int facing_right;
        int sprite_size;
        sfVector2f speed_vector;
        stats_t stats;
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f pos;
        player_dash_t *dash;
        sfIntRect anim_rect;
        sfFloatRect trig;
        collider_t *hurt;
        collider_t *trigger;
        dependency_t *depend;
    } entity_t;

    entity_t *create_player(window_t *window);
    entity_t *create_slime(window_t *window);
    void destroy_player(void *entity);
    void destroy_enemy(void *entity);
    void move_player(entity_t *player, window_t *window);
    void player_print(void *player, window_t *window);
    void player_update(void *player, window_t *window);
    void player_animation(void *player, window_t *window);
    void dash_animation(entity_t *player);
    void animation_controller(entity_t *player);
    void move_player_sprite(entity_t *player, window_t *window);
    void move_enemy_sprite(entity_t *enemy, window_t *window);
    void player_hitbox(entity_t *player);
    void enemy_update(void *enemy_void, window_t *window);
    void enemy_print(void *enemy_void, window_t *window);
    void enemy_move(entity_t *enemy, window_t *window);
    void enemy_animation(void *enemy_void, window_t *window);
    void set_camera(entity_t *player, window_t *window);
    void update_camera(entity_t *player, window_t *window);
    void check_dir(entity_t *entity);

#endif /* !ENTITIES_H */
