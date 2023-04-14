/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** projectile
*/

#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>
#include "chained_list.h"
#include "collision.h"
#include "item.h"

#ifndef PROJECTILE_H
    #define PROJECTILE_H

    typedef struct projectile {
        list_t *projectile_list;
        collider_t *hitbox;
        sfRectangleShape *rect;
        sfFloatRect box;
        sfVector2f pos;
        sfVector2f move_vect;
        sfTime time;
        void *caster;
        void (*move)(struct projectile *, window_t *);
    } projectile_t;

    /**
     * @brief create a projectile
     *
     * @param rect the rectangle of the projectile (position and size)
     * @param move_vect the movement/speed vector of the projectile
     * @param texture texture of the projectile
     * @param move function pointer to move
     * @return projectile_t*
     */
    projectile_t *projectile_create(sfFloatRect rect, sfVector2f move_vect,
        sfTexture *texture, void (*move)(struct projectile *, window_t *));

    /**
     * @brief delete a node from the projectile list
     *
     * @param node the node to be destroyed
     */
    void projectile_delete(void *node);

    /**
     * @brief delete the projectile list
     *
     * @param item the list to be destroyed
     */
    void projectile_list_destroy(void *item);
    void projectile_move_sinus(projectile_t *proj, window_t *win);
    void projectile_move_line(projectile_t *proj, window_t *win);
    void projectile_print(void *item, window_t *window);
    void projectile_update(void *item, window_t *window);

#endif /*PROJECTILE_H*/
