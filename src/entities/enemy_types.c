/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** ADD enemies
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "entities.h"
#include "collision.h"
#include "chained_list.h"
#include "errorhandling.h"
#include "item.h"
#include "room.h"

bool first_enemy_set(list_t *enemies, int i, int j, char sign)
{
    item_t *add = NULL;

    if (sign == 's') {
        add = item_create(NULL, create_skull
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    if (sign == 'a') {
        add = item_create(NULL, create_ice_ghost
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    return true;
}

bool second_enemy_set(list_t *enemies, int i, int j, char sign)
{
    item_t *add = NULL;

    if (sign == 'd') {
        add = item_create(NULL, create_demon
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    if (sign == '#') {
        add = item_create(NULL, create_slime
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    return true;
}

bool third_enemy_set(list_t *enemies, int i, int j, char sign)
{
    item_t *add = NULL;

    if (sign == 'e') {
        add = item_create(NULL, create_little_skeleton
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    if (sign == 'S') {
        add = item_create(NULL, create_big_skeleton
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, enemy_update, enemy_animation, enemy_print);
        enemies->interface->append(enemies, add);
    }
    return true;
}

bool boss_set(list_t *enemies, int i, int j, char sign)
{
    item_t *add = NULL;

    if (sign == 'K') {
        add = item_create(NULL, create_king_slime
        ((sfVector2f){j * TILE_SIZE, i * TILE_SIZE}), destroy_enemy);
        if (!add)
            return false;
        item_set_func(add, king_slime_update, king_slime_animation,
        king_slime_print);
        enemies->interface->append(enemies, add);
    }
    return true;
}

bool enemy_set(list_t *enemies, int i, int j, char sign)
{
    if (!first_enemy_set(enemies, i, j, sign))
        return false;
    if (!second_enemy_set(enemies, i, j, sign))
        return false;
    if (!third_enemy_set(enemies, i, j, sign))
        return false;
    if (!boss_set(enemies, i, j, sign))
        return false;
    return true;
}
