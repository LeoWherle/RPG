/*
** EPITECH PROJECT, 2023
** item
** File description:
** item structure
*/

#include <SFML/Graphics.h>
#include <stdbool.h>

#ifndef ITEM_H
    #define ITEM_H

    enum type {
        NONE = 0,
        TEXTURE,
        SPRITE,
        ENTITY,
        MAP,
    };

    typedef struct window {
        float framerate;
        sfClock *frame;
        sfVideoMode mode;
        sfRenderWindow *window;
    } window_t;

    typedef struct item {
        void *item;
        void (* update)(void *, sfEvent *);
        void (* animate)(void *, sfTime *);
        void (* print)(void *, window_t *);
        void (* destroy)(void *);
        struct item *next;
    } item_t;

    typedef struct dependency {
        enum type type;
        void *dependency;
        struct dependency *next;
    } dependency_t;

    void item_loop(item_t *item, window_t *screen, bool (* cond)(sfEvent *));

    window_t *create_window(sfVideoMode mode, int framerate, char const *title);
    item_t *create_item(item_t *list, void *item,
    void (* act)(void *, sfEvent *),
    void (* print)(void *, window_t *));

#endif /*ITEM_H*/
