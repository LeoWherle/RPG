/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** weapon create and destroy function
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include "weapon.h"
#include "errorhandling.h"
#include "collision.h"
#include "quick_create.h"

weapon_t *weapon_create_lance(float cooldown, int strenght, sfVector2f size,
                        sfTexture *texture)
{
    weapon_t *new = NULL;

    new = malloc(sizeof(weapon_t));
    ASSERT_MALLOC(new, NULL);
    new->activated = false;
    new->angle = 0.;
    new->cooldown = cooldown;
    new->strenght = strenght;
    new->texture = texture;
    new->weapon = rectangle_quick_create((sfFloatRect){0, 0, size.x, size.y},
                                        texture, sfWhite);
    ASSERT_MALLOC(new->weapon, NULL;)
    sfRectangleShape_setOrigin(new->weapon, (sfVector2f){size.x / 2, size.y});
    new->rect = sfRectangleShape_getGlobalBounds(new->weapon);
    new->hitbox = collider_create(&new->rect, HITBOX, false, new);
    ASSERT_MALLOC(new->hitbox, NULL);
    new->pos = (sfVector2f){0, 0};
    new->use = lance_use;
    return new;
}

void weapon_destroy(weapon_t *weapon)
{
    sfRectangleShape_destroy(weapon->weapon);
    collider_destroy(weapon->hitbox);
    free(weapon);
}
