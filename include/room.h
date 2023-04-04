/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** errorhandling
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>

#ifndef ROOM_H_
    #define ROOM_H_
    #define TILE_SIZE 60
    #define TILE_NB 18
    #define VOID_ID 0
    #define FLOOR_ID 1
    #define VOID_POS ((sfIntRect){2, 2, 20, 20})
    #define FLOOR_POS ((sfIntRect){142, 0, 20, 20})
    #define WALL_FRONT_POS ((sfIntRect){162, 42, 20, 20})
    #define WALL_BACK_POS ((sfIntRect){42, 2, 20, 20})
    #define WALL_LEFT_POS ((sfIntRect){122, 22, 20, 20})
    #define WALL_RIGHT_POS ((sfIntRect){82, 22, 20, 20})
    #define TOP_LEFT_POS ((sfIntRect){82, 2, 20, 20})
    #define TOP_RIGHT_POS ((sfIntRect){102, 2, 20, 20})
    #define BOT_LEFT_POS ((sfIntRect){142, 22, 20, 20})
    #define BOT_RIGHT_POS ((sfIntRect){162, 22, 20, 20})
    #define DOOR_TOP_OP ((sfIntRect){2, 42, 40, 20})
    #define DOOR_BOT_OP ((sfIntRect){62, 62, 40, 20})
    #define DOOR_TOP_CL ((sfIntRect){42, 42, 40, 20})
    #define DOOR_BOT_CL ((sfIntRect){102, 62, 40, 20})
    #define LITTLE_CRIS_BL ((sfIntRect){62, 82, 20, 20})
    #define LITTLE_CRIS_PI ((sfIntRect){102, 82, 20, 20})
    #define LITTLE_ROCK ((sfIntRect){222, 22, 20, 20})
    #define LITTLE_STICK ((sfIntRect){142, 102, 20, 20})


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
    char **collisions;
    room_type_t type;
    int entity_nb;
    int height;
} room_t;

typedef struct tile_s {
    sfTexture *texture;
    sfSprite *img;
} tile_t;

typedef struct pos_s {
    int x;
    int y;
} pos_t;

    room_t *get_room(room_t *room, room_type_t type);
    void print_room(char **room);
    void free_room(room_t *room);
    void draw_room(sfRenderWindow *window, room_t *room, tile_t **tile_list);
    tile_t **init_tile_list(tile_t **tile_list);
    void free_tile_list(tile_t **tile_list);
    room_t *fill_collisions(room_t *room, char *buff, FILE *fd, size_t len);
    char *fill_room(int c, char *buff, char **room, int y);
    int get_file_nb(char *path);
    char *get_specific_file(char *path, int nb);
    int draw_doors(char **map, int x, int y, int i);

#endif /* !ROOM_H_ */
