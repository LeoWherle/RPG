/*
** EPITECH PROJECT, 2023
** MyRPG
** File description:
** errorhandling
*/

#ifndef ROOM_H_
    #define ROOM_H_

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

    room_t *get_room(room_t *room, room_type_t type);
    void print_room(char **room);
    void free_room(room_t *room);

#endif /* !ROOM_H_ */
