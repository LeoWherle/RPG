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

    #define PLAYER_SIZE 3
    #define PLAYER_SPEED 5
    #define PLAYER_ATK_SPEED 1
    #define PLAYER_HP 100
    #define PLAYER_ATK 10
    #define PLAYER_EXP_CAP 100
    #define PLAYER_DASH_COOLDOWN 2.5
    #define PLAYER_SPRITE_SIZE 48

    #define CLOSE_RANGE -24
    #define LONG_RANGE 200

    #define SLIME_SPRITE_SIZE 20
    #define KING_SLIME_SPRITE_SIZE 50
    #define ICE_GHOST_SPRITE_SIZE 26

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

    typedef struct exp {
        unsigned int level;
        float current_exp;
        float exp_cap;
        float mult;
    } exp_t;

    typedef struct stats {
        float max_hp;
        float hp;
        float atk;
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

    typedef struct king_slime {
        sfVector2f sprite_pos;
        int is_jumping;
        int jump_start;
        float timer;
        int jump_height;
        float offset;
        float jump_speed;
        sfTime jump_delay;
        sfCircleShape *shadow;
    } king_slime_t;

    typedef struct enemy {
        int range;
        int proj_range;
        int spoted;
        int rand_angle;
        int is_moving;
        int anim_frames;
        int is_dead;
        int is_boss;
        sfVector2f scale;
        float anim_inter;
        king_slime_t king_slime;
        sfTime knock_time;
        sfTime wander_time;
        sfTime anim_time;
        sfTime invi_time;
        sfTime death_time;
        sfTime attack_time;
    } enemy_t;

    typedef struct entity_visuals {
        sfSprite *sprite;
        sfTexture *texture;
        sfIntRect anim_rect;
        sfSprite *death_sprite;
        sfTexture *death_texture;
        sfIntRect death_anim_rect;
        enum animation_type_player animation;
        int sprite_size;
        int facing_right;
    } entity_visuals_t;

    typedef struct entity_state {
        int got_hit;
        float hit_angle;
        int knockback;
        sfRectangleShape *info_bar;
    } entity_state_t;

    typedef struct entity_colliders {
        weapon_t *weapon;
        collider_t *hurt;
        collider_t *trigger;
        sfFloatRect hitbox;
    } entity_colliders_t;

    typedef struct camera_effects {
        sfVector2f player_pos;
        sfVector2f camera_pos;
        sfTime shake_time;
        int cam_lock;
        int got_player;
        int shake;
        int backtrack;
        int pass_update;
    } camera_effects_t;

    typedef struct entity {
        entity_visuals_t visu;
        entity_state_t state;
        entity_colliders_t coll;
        camera_effects_t cam;
        stats_t stats;
        sfVector2f pos;
        sfVector2f speed_vector;
        dependency_t *depend;
        enemy_t enemy;
        player_dash_t dash;
        inventory_t *inventory;
        bool quest;
    } entity_t;

    //CREATE AND DESTROY
    entity_t *create_player(map_t *map, window_t *window);
    entity_t *create_slime(sfVector2f pos);
    entity_t *create_ice_ghost(sfVector2f pos);
    entity_t *create_skull(sfVector2f pos);
    entity_t *create_demon(sfVector2f pos);
    entity_t *create_king_slime(sfVector2f pos);
    entity_t *create_little_skeleton(sfVector2f pos);
    entity_t *create_big_skeleton(sfVector2f pos);
    void destroy_player(void *entity);
    void destroy_enemy(void *entity);
    void set_stats(entity_t *entity, stats_t *stats);
    void set_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                sfVector2f origin);
    void set_info_bar(entity_t *entity, sfColor color,
    sfVector2f size, sfVector2f pos);
    void set_death_sprite(entity_t *entity, char *path, sfIntRect anim_rect,
                    sfVector2f origin);
    void set_enemy(entity_t *entity, float range, float proj_range,
                    int frames);
    void set_enemy_2(entity_t *entity, stats_t *stats,
            weapon_t *(* create_weapon)(sfVector2f size, int strength));

    //CREATE ENEMY LIST
    list_t *spawn_enemies(map_t *map);
    void enemy_list_print(void *enemies, window_t *window);
    void enemy_list_animate(void *enemies, window_t *window);
    void enemy_list_update(void *enemies, window_t *window, float delta);
    void clear_list(void *list);
    void clear_enemies(list_t *enemies);
    void destroy_item_enemy(void *item);
    bool enemy_set(list_t *enemies, int i, int j, char sign);

    //PLAYER MOVEMENT
    void move_player(entity_t *player, window_t *window, float delta);
    void update_camera(entity_t *player, window_t *window);
    void player_update(void *player, window_t *window, float delta);

    //PLAYER ANIMATION
    void player_animation(void *player, window_t *window);
    void dash_animation(entity_t *player);
    void animation_controller(entity_t *player);
    void move_player_sprite(entity_t *player, window_t *window);
    void move_enemy_sprite(entity_t *enemy, window_t *window);
    void player_print(void *player, window_t *window);

    //ENEMY MOVEMENT
    void enemy_move(entity_t *enemy, window_t *window);
    void enemy_update(void *enemy_void, window_t *window, float delta);

    //ENEMY ANIMATION
    void enemy_print(void *enemy_void, window_t *window);
    void enemy_animation(void *enemy_void, window_t *window);

    //BOSS MOVEMENT
    void king_slime_move(entity_t *slime, window_t *window);
    void king_slime_jump(entity_t *slime, window_t *window, float delta);
    void king_slime_update(void *enemy_void, window_t *window, float delta);

    //BOSS ANIMATION
    void king_slime_print(void *enemy_void, window_t *window);
    void king_slime_anim_controller(entity_t *slime, window_t *window);
    void king_slime_animation(void *enemy_void, window_t *window);

    //COMBAT
    void invicibility_frames(entity_t *player, window_t *window);
    void enemy_invicibilty(entity_t *enemy, window_t *window);
    void enemy_health_bar(entity_t *enemy, int bar_size);
    void player_knockback(entity_t *player, window_t *window);
    void player_dash_bar(entity_t *player);
    void ennemy_knockback(entity_t *enemy, window_t *window);
    void enemy_explosion(entity_t *enemy, window_t *window);
    sfFloatRect get_player_bounds(entity_t *player);

    //CAMERA
    void camera_controller(window_t *window, entity_t *boss);
    void death_camera_controller(window_t *window, entity_t *boss);
    int camera_travel(entity_t *boss, sfVector2f target);
    void camera_shake(window_t *window, entity_t *boss, int offset);

    //OTHER
    void check_dir(entity_t *entity, float delta);
    void spawn_point(entity_t *entity, char sign);
    void normalize_vect(sfVector2f *vect, float delta);

    void add_exp(stats_t *stat, int exp_gain);
    void level_up(stats_t *stat);
    void inventory_weapon_destroy(void *weapon);

    void reset_scene(entity_t *player, window_t *window);

#endif /* !ENTITIES_H */
