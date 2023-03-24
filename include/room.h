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
    #define TILE_NB 14
    #define VOID 0
    #define FLOOR 1
    #define WALL 2
    #define WALL2 3
    #define WALL3 4
    #define UPLEFT 5
    #define UPRIGHT 6
    #define DOWNLEFT 7
    #define DOWNRIGHT 8
    #define DOOR 9
    #define OPEN_DOOR 10
    #define CHEST 11
    #define WALL2_W_GROUND 12
    #define WALL3_W_GROUND 13


typedef enum room_type_e {
    EMPTY_R,
    MONSTER_R,
    CHEST_R,
    PNJ_R,
    BOSS_R,
    TRAP_R
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
    void draw_room(sfRenderWindow *window, room_t *room, tile_t **tile_list);
    tile_t **init_tile_list(tile_t **tile_list);
    void free_tile_list(tile_t **tile_list);
    char **get_tiles_img(char **tiles);

#endif /* !ROOM_H_ */
