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
#include "weapon.h"
#include "room.h"

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
    #define PLAYER_EXP_CAP 100
    #define PLAYER_DASH_COOLDOWN 3
    #define PLAYER_SPRITE_SIZE 48

    #define CLOSE_RANGE -24

    #define SLIME_SPRITE_SIZE 20

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

    typedef struct exp{
        unsigned int level;
        unsigned int current_exp;
        unsigned int exp_cap;
        float mult;
    } exp_t;

    typedef struct stats {
        float max_hp;
        float hp;
        float atk;
        float def;
        float luck;
        float speed;
        float atk_speed;
        exp_t exp;
    } stats_t;

    typedef struct player_dash {
        int is_dashing;
        int vector_lock;
        float dash_cooldown;
        sfVector2f dash_vector;
        sfTime dash_start;
        sfTime dash_time;
    } player_dash_t;

    typedef struct enemy {
        int range;
        int proj_range;
        int spoted;
    } enemy_t;

    typedef struct entity {
        sfSprite *sprite;
        sfTexture *texture;
        enum animation_type_player animation;
        sfIntRect anim_rect;
        int sprite_size;
        int facing_right;
        stats_t stats;
        sfVector2f pos;
        sfVector2f speed_vector;
        player_dash_t dash;
        int got_hit;
        float hit_angle;
        int knockback;
        weapon_t *weapon;
        collider_t *hurt;
        collider_t *trigger;
        sfFloatRect hitbox;
        dependency_t *depend;
        enemy_t enemy;
    } entity_t;

    //CREATE AND DESTROY
    entity_t *create_player(map_t *map);
    entity_t *create_slime(sfVector2f pos);
    void destroy_player(void *entity);
    void destroy_enemy(void *entity);

    //CREATE ENEMY LIST
    list_t *spawn_enemies(map_t *map);
    void enemy_list_print(void *enemies, window_t *window);
    void enemy_list_animate(void *enemies, window_t *window);
    void enemy_list_update(void *enemies, window_t *window);
    void clear_list(void *list);

    //PLAYER MOVEMENT
    void move_player(entity_t *player, window_t *window);
    void update_camera(entity_t *player, window_t *window);
    void player_update(void *player, window_t *window);

    //PLAYER ANIMATION
    void player_animation(void *player, window_t *window);
    void dash_animation(entity_t *player);
    void animation_controller(entity_t *player);
    void move_player_sprite(entity_t *player, window_t *window);
    void move_enemy_sprite(entity_t *enemy, window_t *window);
    void player_print(void *player, window_t *window);

    //ENEMY MOVEMENT
    void enemy_move(entity_t *enemy, window_t *window);
    void enemy_update(void *enemy_void, window_t *window);

    //ENEMY ANIMATION
    void enemy_print(void *enemy_void, window_t *window);
    void enemy_animation(void *enemy_void, window_t *window);

    //COMBAT
    void invicibility_frames(entity_t *player, window_t *window);
    void enemy_invicibilty(entity_t *enemy, window_t *window);
    void player_knockback(entity_t *player, window_t *window);
    void ennemy_knockback(entity_t *enemy, window_t *window);
    sfFloatRect get_player_bounds(entity_t *player);

    //OTHER
    void check_dir(entity_t *entity);
    void spawn_point(entity_t *entity, char sign);

#endif /* !ENTITIES_H */
