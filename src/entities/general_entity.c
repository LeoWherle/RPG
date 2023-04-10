/*
** EPITECH PROJECT, 2023
** RPG
** File description:
** entity
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "entities.h"
#include "collision.h"

void check_dir(entity_t *entity)
{
    collider_t *colh = NULL;
    collider_t *colv = NULL;
    collider_t *col = NULL;

    entity->trig.left = entity->pos.x + entity->speed_vector.x;
    entity->trig.top = entity->pos.y + entity->speed_vector.y;
    col = collision_check(entity->trigger, SOLID);
    if (col) {
        entity->trig.left = entity->pos.x + entity->speed_vector.x;
        entity->trig.top = entity->pos.y;
        colh = collision_check(entity->trigger, SOLID);
        if (colh)
            entity->speed_vector.x = 0;
        entity->trig.left = entity->pos.x;
        entity->trig.top = entity->pos.y + entity->speed_vector.y;
        colv = collision_check(entity->trigger, SOLID);
        if (colv)
            entity->speed_vector.y = 0;
    }
}