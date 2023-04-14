/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** projectile_collision
*/

#include "projectile.h"
#include "collision.h"
#include "entities.h"

static void kill_a_knock(entity_t *ent, entity_t *caster, projectile_t *proj)
{
    if (ent->stats.hp <= 0)
        add_exp(&caster->stats, 100);
    ent->got_hit = true ;
    ent->knockback = true;
    ent->hit_angle = atan2(ent->pos.y - proj->pos.y,
    ent->pos.x - proj->pos.x) * 180 / M_PI;
}

bool projectile_collision(collider_t *main, collider_t *sub)
{
    projectile_t *proj = NULL;
    entity_t *ent = NULL;
    entity_t *caster = NULL;

    proj = main->owner;
    caster = proj->caster;
    if (caster->hurt->type == sub->type)
        return false;
    if (sub->type == HURTBOX || sub->type == PLAYER_HURTBOX) {
        ent = sub->owner;
        ent->stats.hp -= caster->stats.atk + caster->weapon->strenght -
                        ent->stats.def;
        kill_a_knock(ent, caster, proj);
    }
    if (sub->type == SOLID || sub->type == INTERACTION ||
        sub->type == HURTBOX || sub->type == PLAYER_HURTBOX) {
        node_delete(proj->projectile_list, proj, projectile_delete);
        return true;
    }
    return false;
}
