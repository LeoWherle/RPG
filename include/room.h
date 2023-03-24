/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** errorhandling
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>

#ifndef ROOM_H_
    #define ROOM_H_
    #define TILE_SIZE 64
    #define TILE_NB 4
    #define VOID 0
    #define FLOOR 1
    #define WALL 2
    #define DOOR 3

typedef enum room_type_e {
    MONSTER,
    CHEST,
    PNJ,
    BOSS,
    TRAP,
    EMPTY
} room_type_t;

typedef struct room_s {
    char **room;
    room_type_t type;
    int entity_nb;
    int height;
} room_t;

typedef struct tile_s {
    sfTexture *texture;
    sfSprite *img;
    bool collision;
} tile_t;

    room_t *get_room(room_t *room, room_type_t type);
    void print_room(char **room);
    void free_room(room_t *room);

#endif /* !ROOM_H_ */
