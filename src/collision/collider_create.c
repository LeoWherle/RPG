/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** collider_create
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include "collision.h"
#include "chained_list.h"

/**
 * @brief create a new collider and add it to the global list
 *
 * @param hitbox the sfFloatrect that will describe the hitbox
 * @param type the type of hitbox
 * @param activate whether to use the collider or not
 * @param owner the owner of the collider
 * @return collider_t*
 */
collider_t *collider_create(sfFloatRect *hitbox, tag_t type,
                            bool activate, void *owner)
{
    static list_t *collider_list = NULL;
    collider_t *new = NULL;

    if (!collider_list) {
        collider_list = list_init();
    }
    new = malloc(sizeof(collider_t));
    new->hitbox = hitbox;
    new->type = type;
    new->activated = activate;
    new->owner = owner;
    new->to_collide = collider_list;
    new->on_collision_entered = NULL;
    collider_list->interface->append(collider_list, new);
    return new;
}

/**
 * @brief Destroy a collider and remove it from the golbal collider list.
 * If this is the last collider, also destroy the global list.
 *
 * @param collider the collider to destroy
 */
void collider_destroy(collider_t *collider)
{
    if (collider->to_collide->size == 1) {
        collider->to_collide->interface->destroy(collider->to_collide, free);
    } else {
        node_delete(collider->to_collide, collider, free);
    }
}
