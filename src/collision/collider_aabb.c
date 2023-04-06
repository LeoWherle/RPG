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
    tag_t hold = 0;

    hold = to_check->type;
    to_check->type = 6;
    while (node) {
        act = node->data;
        if (act->activated && act->type == tag &&
            sfFloatRect_intersects(to_check->hitbox, act->hitbox, NULL)) {
            return act;
        }
        node = node->next;
    }
    to_check->type = hold;
    return NULL;
}
