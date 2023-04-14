/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create and delete function for projectile
*/

#include <stddef.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "projectile.h"
#include "chained_list.h"
#include "quick_create.h"

projectile_t *projectile_create(sfFloatRect rect, sfVector2f move_vect,
            sfTexture *texture, void (*move)(struct projectile *, window_t *))
{
    static list_t *projectile_list = NULL;
    projectile_t *new = NULL;

    new = malloc(sizeof(projectile_t));
    ASSERT_MALLOC(new, NULL);
    new->rect = rectangle_quick_create(rect, texture, sfWhite);
    ASSERT_MALLOC(new->rect, NULL);
    new->pos = sfRectangleShape_getPosition(new->rect);
    new->move_vect = move_vect;
    new->box = sfRectangleShape_getGlobalBounds(new->rect);
    new->hitbox = collider_create(&new->box, HITBOX, true, NULL);
    ASSERT_MALLOC(new->hitbox, NULL);
    if (!projectile_list) {
        projectile_list = list_init();
        ASSERT_MALLOC(projectile_list, NULL);
    }
    projectile_list->interface->append(projectile_list, new);
    new->projectile_list = projectile_list;
    new->move = move;
    return new;
}

void projectile_delete(void *node)
{
    projectile_t *proj = node;

    collider_destroy(proj->hitbox);
    sfRectangleShape_destroy(proj->rect);
    free(proj);
}

void projectile_list_destroy(void *item)
{
    list_t *list = item;

    list_destroy(list, projectile_delete);
}
