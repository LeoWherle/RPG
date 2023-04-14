/*
** EPITECH PROJECT, 2023
** my rpg
** File description:
** check if there is a collision between two collision box
*/

#include <stddef.h>
#include <stdbool.h>
#include "collision.h"
#include "chained_list.h"

/**
 * @brief check if there is a collision between a collider and
 * another collider and use the on collision entered
 *
 * @param to_check the collider that collision will be check
 * @return collider_t*
 */
void collision_check(collider_t *to_check)
{
    collider_t *act = NULL;
    node_t *node = to_check->to_collide->head;

    while (node) {
        act = node->data;
        if (act->activated && act->hitbox && to_check->hitbox &&
            act->owner != to_check->owner &&
            sfFloatRect_intersects(to_check->hitbox, act->hitbox, NULL) &&
            to_check->on_collision_entered(to_check, act)) {
                return;
        }
        node = node->next;
    }
}
