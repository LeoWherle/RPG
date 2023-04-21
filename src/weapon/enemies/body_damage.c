/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** body damage
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <SFML/Graphics.h>
#include "weapon.h"
#include "collision.h"
#include "quick_create.h"
#include "entities.h"
#include "item.h"

void body_use(weapon_t *body, UNUSED window_t *win, UNUSED float delta)
{
    entity_t *entity = NULL;

    if (!body)
        return;
    entity = body->hitbox->owner;
    sfRectangleShape_setPosition(body->weapon, entity->pos);
    body->rect = sfSprite_getGlobalBounds(entity->visu.sprite);
}

weapon_t *body_damage(sfVector2f size, int strength)
{
    weapon_t *new = NULL;

    new = malloc(sizeof(weapon_t));
    ASSERT_MALLOC(new, NULL);
    new->angle = 0.;
    new->cooldown = 0;
    new->strenght = strength;
    new->weapon = rectangle_quick_create((sfFloatRect){0, 0, size.x, size.y},
                                        NULL, sfWhite);
    ASSERT_MALLOC(new->weapon, NULL;)
    new->rect = sfRectangleShape_getGlobalBounds(new->weapon);
    new->hitbox = collider_create(&new->rect, HITBOX, true, new);
    ASSERT_MALLOC(new->hitbox, NULL);
    new->pos = (sfVector2f){0, 0};
    new->use = body_use;
    new->path = NULL;
    return new;
}
