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

    enum win_state {
        TITLE_SCREEN,
        GAME,
        GAME_OVER,
        EXIT_ERROR,
    };

    typedef struct window {
        sfClock *frame;
        sfVideoMode mode;
        sfUint32 style;
        sfView *view;
        sfEvent *event;
        sfRenderWindow *window;
        bool exit;
        enum win_state state;
        void *player;
    } window_t;

    typedef struct item {
        void *item;
        void (* update)(void *, window_t *, float);
        void (* animate)(void *, window_t *);
        void (* print)(void *, window_t *);
        void (* destroy)(void *);
        struct item *next;
    } item_t;

    typedef struct dependency {
        enum type type;
        void *dependency;
        struct dependency *next;
    } dependency_t;

    void item_loop(item_t *item, window_t *screen, bool (* cond)(window_t *));

    window_t *window_create(sfVideoMode mode, int framerate,
                            char const *title, sfFloatRect view_rect);
    void window_destroy(window_t *window);
    item_t *item_create(item_t *list, void *item, void (* destroy)(void *));
    void item_list_destroy(item_t *item);
    void item_set_func(item_t *item, void (* update)(void *, window_t *, float),
                    void (* animate)(void *, window_t *),
                    void (* print)(void *, window_t *));

#endif /*ITEM_H*/
