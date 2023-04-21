/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** move trigger enter
*/

#include <stdbool.h>
#include "collision.h"
#include "entities.h"

bool move_trigger_enter(collider_t *main, collider_t *sub)
{
    entity_t *ent = NULL;

    if (sub->type == SOLID) {
        ent = main->owner;
        if (main->hitbox->left != ent->pos.x) {
            ent->speed_vector.x = 0;
        }
        if (main->hitbox->top != ent->pos.y) {
            ent->speed_vector.y = 0;
        }
        return true;
    }
    return false;
}
