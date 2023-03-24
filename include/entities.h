/*
** EPITECH PROJECT, 2023
** My_RPG
** File description:
** entites header
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/System.h>


#ifndef ENTITIES_H
    #define ENTITIES_H

    enum entity_type {
        PLAYER,
        ENEMY,
        NPC,
        ITEM,
        OTHER
    };

    typedef struct entity {
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f pos;
        enum entity_type type;
        void (*draw)(struct entity *, sfRenderWindow *);
        void (*action)(struct entity *, sfEvent);
    } entity_t;

#endif /* !ENTITIES_H */
