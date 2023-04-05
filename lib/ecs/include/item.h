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
        PLAYER,
        WEAPON,
        ENTITY,
        MAP,
    };

    typedef struct window {
        sfClock *frame;
        sfVideoMode mode;
        sfView *view;
        sfEvent *event;
        sfRenderWindow *window;
    } window_t;

    typedef struct item {
        void *item;
        void (* update)(void *, window_t *);
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

    window_t *window_create(sfVideoMode mode, int framerate,
                            char const *title, sfFloatRect view_rect);
    void window_destroy(window_t *window);
    item_t *item_create(item_t *list, void *item,
                        void (* act)(void *, window_t *),
                        void (* print)(void *, window_t *));
    void item_list_destroy(item_t *item);

#endif /*ITEM_H*/
