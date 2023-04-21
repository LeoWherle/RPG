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
#include "errorhandling.h"

#ifndef WEAPON_H
    #define WEAPON_H

    #define INV_HEIGHT 4
    #define INV_WIDTH 8
    #define INV_SLOT_MAX INV_WIDTH * INV_HEIGHT

    typedef struct weapon {
        sfRectangleShape *weapon;
        sfTexture *texture;
        char *path;
        collider_t *hitbox;
        sfFloatRect rect;
        float angle;
        sfVector2f pos;
        int strenght;
        float cooldown;
        void (*use)(struct weapon *, window_t *, float);
    } weapon_t;

    typedef struct inventory_s {
        weapon_t *weapon;
        list_t *items;
    } inventory_t;

    weapon_t *weapon_create_sword(float cooldown, int strenght, sfVector2f size,
                        char *path);
    weapon_t *body_damage(sfVector2f size, int strength);
    void weapon_destroy(weapon_t *weapon);
    void weapon_use(weapon_t *weapon, window_t *win, float delta);
    void sword_use(weapon_t *lance, window_t *win, float delta);
    void body_use(weapon_t *body, UNUSED window_t *win, UNUSED float delta);

    weapon_t *weapon_create_bow(float cooldown, int strenght, sfVector2f size,
                        char *path);
    void bow_use(weapon_t *bow, window_t *window, UNUSED float delta);
    void use_cast_magic_ball(weapon_t *ball, window_t *win, UNUSED float delta);
    weapon_t *cast_projectile(UNUSED sfVector2f size, int strength);
    weapon_t *drop_weapon(void);


    /////// INVENTORY ///////
    inventory_t *inventory_create(weapon_t *start_weapon);
    void inventory_destroy(inventory_t *inventory);
    void inventory_clear(inventory_t *inv);

#endif /*WEAPON_H*/
