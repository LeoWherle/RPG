/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** projectile_collision
*/

#include "projectile.h"
#include "collision.h"
#include "entities.h"

bool projectile_collision(collider_t *main, collider_t *sub)
{
    projectile_t *proj = NULL;
    entity_t *caster = NULL;
    entity_t *target = NULL;

    proj = main->owner;
    caster = proj->caster;
    if (caster->coll.hurt->type == sub->type)
        return false;
    if (sub->type == HURTBOX || sub->type == PLAYER_HURTBOX) {
        target = sub->owner;
        sub->on_collision_entered(sub, caster->coll.weapon->hitbox);
        if (sub->type == HURTBOX)
            target->state.knockback = false;
    }
    if (sub->type == HURTBOX || sub->type == PLAYER_HURTBOX) {
        node_delete(proj->projectile_list, proj, projectile_delete);
        return true;
    }
    return false;
}
