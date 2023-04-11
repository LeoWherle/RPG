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
    sfVector2f speed = {0, 0};

    speed = entity->speed_vector;
    if (speed.x == 0 && speed.y == 0)
        return;
    entity->trig.left = entity->pos.x + speed.x;
    entity->trig.top = entity->pos.y + speed.y;
    collision_check(entity->trigger);
    if (speed.x != entity->speed_vector.x &&
        speed.y != entity->speed_vector.y) {
        entity->speed_vector = speed;
        entity->trig.left = entity->pos.x;
        entity->trig.top = entity->pos.y + speed.y;
        collision_check(entity->trigger);
        entity->trig.left = entity->pos.x + speed.x;
        entity->trig.top = entity->pos.y;
        collision_check(entity->trigger);
    }
}
