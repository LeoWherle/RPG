/*
** EPITECH PROJECT, 2023
** my rpg
** File description:
** check if there is a collision between two collision box
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "collision.h"
#include "chained_list.h"

static bool check_aabb(sfFloatRect *hitbox, sfFloatRect *hurtbox)
{
    if (hitbox->top < hurtbox->top + hurtbox->height &&
        hitbox->top + hitbox->height > hurtbox->top &&
        hitbox->left < hurtbox->left + hurtbox->width &&
        hitbox->left + hitbox->width > hurtbox->left) {
        return true;
    }
    if (hurtbox->top < hitbox->top + hitbox->height &&
        hurtbox->top + hurtbox->height > hitbox->top &&
        hurtbox->left < hitbox->left + hitbox->width &&
        hurtbox->left + hurtbox->width > hitbox->left) {
        return true;
    }
    return false;
}

/**
 * @brief check if there is a collision between a collider and
 * another collider that have a certain tag
 *
 * @param to_check the collider that collision will be check
 * @param tag the tag to check
 * @return collider_t*
 */
collider_t *collision_check(collider_t *to_check, tag_t tag)
{
    collider_t *act = NULL;
    node_t *node = to_check->to_collide->head;
    tag_t hold = NONE;

    hold = to_check->type;
    to_check->type = NONE;
    while (node) {
        act = node->data;
        if (act->activated && act->type == tag &&
            check_aabb(to_check->hitbox, act->hitbox)) {
            return act;
        }
        node = node->next;
    }
    to_check->type = hold;
    return NULL;
}
