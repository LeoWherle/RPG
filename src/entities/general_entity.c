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
#include "room.h"

void normalize_vect(sfVector2f *vect, float delta)
{
    vect->x = vect->x / (1. / 60.) * delta;
    vect->y = vect->y / (1. / 60.) * delta;
}

void check_dir(entity_t *entity, float delta)
{
    sfVector2f speed = {0, 0};
    sfFloatRect trig = {0, 0, 1, 1};

    normalize_vect(&entity->speed_vector, delta);
    entity->coll.trigger->hitbox = &trig;
    speed = entity->speed_vector;
    if (speed.x == 0 && speed.y == 0) return;
    trig.left = entity->pos.x + speed.x;
    trig.top = entity->pos.y + speed.y;
    collision_check(entity->coll.trigger);
    if (speed.x != entity->speed_vector.x &&
        speed.y != entity->speed_vector.y) {
        entity->speed_vector = speed;
        trig.left = entity->pos.x;
        trig.top = entity->pos.y + speed.y;
        collision_check(entity->coll.trigger);
        trig.left = entity->pos.x + speed.x;
        trig.top = entity->pos.y;
        collision_check(entity->coll.trigger);
    }
}

int check_spawn(entity_t *entity, int i, char sign, char **map)
{
    for (int j = 0; map[i][j] != '\0'; j++) {
        if (map[i][j] == sign) {
            entity->pos.x = j * TILE_SIZE;
            entity->pos.y = i * TILE_SIZE;
            return 1;
        }
    }
    return 0;
}

void spawn_point(entity_t *entity, char sign)
{
    map_t *map = (map_t *)entity->depend->dependency;

    for (int i = 0; map->room->room[i]; i++) {
        if (check_spawn(entity, i, sign, map->room->room))
            return;
    }
}
