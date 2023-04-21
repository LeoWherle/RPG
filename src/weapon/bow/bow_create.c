/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create a bow
*/

#include <stdlib.h>
#include "weapon.h"
#include "quick_create.h"

weapon_t *weapon_create_bow(float cooldown, int strenght, sfVector2f size,
                        char *path)
{
    weapon_t *new = NULL;

    new = malloc(sizeof(weapon_t));
    ASSERT_MALLOC(new, NULL);
    new->angle = 0.;
    new->cooldown = cooldown;
    new->strenght = strenght;
    new->path = string_dup(path);
    new->texture = sfTexture_createFromFile(path, NULL);
    ASSERT_MALLOC(new->texture, NULL);
    new->weapon = rectangle_quick_create((sfFloatRect){0, 0, size.x, size.y},
                                        new->texture, sfWhite);
    ASSERT_MALLOC(new->weapon, NULL;)
    sfRectangleShape_setOrigin(new->weapon, (sfVector2f){0, size.x});
    new->rect = sfRectangleShape_getGlobalBounds(new->weapon);
    new->hitbox = collider_create(&new->rect, PLAYER_HITBOX, false, new);
    ASSERT_MALLOC(new->hitbox, NULL);
    new->pos = (sfVector2f){0, 0};
    new->use = bow_use;
    return new;
}
