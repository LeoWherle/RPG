/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** init map collisions
*/

#include <stdlib.h>
#include "errorhandling.h"
#include "room.h"
#include "collision.h"

static collider_t *create_special_col(collider_t *collider, sfFloatRect *rect,
char c, room_type_t type)
{
    if (((c == 'e' || c == 'p') && (type == CAVE_R || type == BOSS_R)) ||
    (type == VILLAGE_R && c == 'w')) {
        collider = collider_create(rect, TELEPORTER_CAVE, true, NULL);
        return (collider);
    }
    if (c == '@' && type == VILLAGE_R) {
        collider = collider_create(rect, TELEPORTER_ROOM, true, NULL);
        return (collider);
    }
    if (c == '@' && type == HOUSE_R) {
        collider = collider_create(rect, TELEPORTER_VILLAGE, true, NULL);
        return (collider);
    }
    if (c == 'c' || c == 'v' || c == 'V') {
        collider = collider_create(rect, INTERACTION, true, NULL);
        return (collider);
    }
    collider = collider_create(rect, SOLID, true, NULL);
    return (collider);
}

static list_t *add_in_colliders(list_t *colliders, room_t *room, int x, int y)
{
    collider_t *collider = NULL;
    sfFloatRect *rect = NULL;

    if (!is_in(room->room[y][x], "? ;,:~$#")) {
        collider = malloc(sizeof(collider_t));
        ASSERT_MALLOC(collider, NULL);
        rect = malloc(sizeof(sfFloatRect));
        ASSERT_MALLOC(rect, NULL);
        rect = translate_collisions(room->room[y][x], rect, room->type);
        rect->top = y + rect->top;
        rect->left = x + rect->left;
        rect->top *= TILE_SIZE;
        rect->left *= TILE_SIZE;
        collider = create_special_col(collider, rect, room->room[y][x],
        room->type);
        ASSERT_MALLOC(collider, NULL);
        colliders->interface->append(colliders, collider);
    }
    return (colliders);
}

static list_t *handle_angle(list_t *colliders, room_t *room, int x, int y)
{
    if (room->room[y][x] == 'l') {
        room->room[y][x] = '[';
        add_in_colliders(colliders, room, x, y);
        ASSERT_MALLOC(colliders, NULL);
        room->room[y][x] = 'l';
    }
    if (room->room[y][x] == 'r') {
        room->room[y][x] = ']';
        add_in_colliders(colliders, room, x, y);
        ASSERT_MALLOC(colliders, NULL);
        room->room[y][x] = 'r';
    }
    return (colliders);
}

list_t *init_colliders(list_t *colliders, room_t *room)
{
    colliders = list_init();
    ASSERT_MALLOC(colliders, NULL);
    for (int y = 0; room->room[y] != NULL; y++) {
        for (int x = 0; room->room[y][x] != '\0'; x++) {
            colliders = add_in_colliders(colliders, room, x, y);
            ASSERT_MALLOC(colliders, NULL);
            colliders = handle_angle(colliders, room, x, y);
            ASSERT_MALLOC(colliders, NULL);
        }
    }
    return (colliders);
}
