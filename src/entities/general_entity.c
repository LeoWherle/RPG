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
    sfFloatRect trig = {0, 0, 1, 1};

    entity->trigger->hitbox = &trig;
    speed = entity->speed_vector;
    if (speed.x == 0 && speed.y == 0)
        return;
    trig.left = entity->pos.x + speed.x;
    trig.top = entity->pos.y + speed.y;
    collision_check(entity->trigger);
    if (speed.x != entity->speed_vector.x &&
        speed.y != entity->speed_vector.y) {
        entity->speed_vector = speed;
        trig.left = entity->pos.x;
        trig.top = entity->pos.y + speed.y;
        collision_check(entity->trigger);
        trig.left = entity->pos.x + speed.x;
        trig.top = entity->pos.y;
        collision_check(entity->trigger);
    }
}
