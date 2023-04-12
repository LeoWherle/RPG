/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** room and map functions
*/

#include <stdbool.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include "item.h"
#include "collision.h"

#ifndef ROOM_H_
    #define ROOM_H_
    #define TILE_SIZE 60
    #define VOID_ID 0
    #define FLOOR_ID 1
    #define RDR_DIST_X 1700
    #define RDR_DIST_Y 1800
    #define RENDER(x) if (x == -1) continue;
    #define RENDER_3D(pos, center) if (pos < center) continue;

typedef enum room_type_e {
    VILLAGE_R,
    CAVE_R,
} room_type_t;

typedef struct room_s {
    char **room;
    room_type_t type;
    int entity_nb;
    int height;
    sfColor bg_color;
} room_t;

typedef struct tile_s {
    sfTexture *texture;
    sfSprite *img;
} tile_t;

typedef struct pos_s {
    int x;
    int y;
} pos_t;

typedef struct map_s {
    room_t *room;
    tile_t **tile_list;
    list_t *colliders;
} map_t;

    room_t *get_room(room_t *room, room_type_t type);
    void print_room(char **room);
    void free_room(room_t *room);
    void draw_room_first(void *map_pt, window_t* window);
    void draw_room_second(void *map_pt, window_t* window);
    void free_tile_list(tile_t **tile_list);
    char *fill_room(int c, char *buff, char **room, int y);
    int get_file_nb(char *path);
    char *get_specific_file(char *path, int nb);
    bool is_in(char c, char *str);
    void free_map(void *map_pt);
    map_t *init_map(room_type_t type);
    tile_t **fill_tile_list(char **tiles, tile_t **tile_list,
    sfIntRect *rec_list[]);
    tile_t **init_village_tile_list(tile_t **tile_list, int map_nb);
    int translate_village(char **map, int y, int x);
    tile_t **init_cave_tile_list(tile_t **tile_list, int map_nb);
    int translate_cave(char **map, int y, int x);
    char *get_random_room(void);
    sfVector2f draw_in_rdr(sfVector2f center, int x, int y);
    int stop_draw_on_close(window_t *window, int y);
    void draw_tile(sfRenderWindow *window, sfSprite *tile, char c,
    room_type_t type);
    int translate_map(char **room, int y, int x, room_type_t type);
    sfFloatRect translate_collisions_village(char c);
    sfFloatRect trans_col_cave(char c);
    list_t *handle_angle(list_t *colliders, room_t *room, int x, int y);
    list_t *add_in_colliders(list_t *colliders, room_t *room, int x, int y);

#endif /* !ROOM_H_ */
