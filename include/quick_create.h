/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** quick create
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>

#ifndef QUICK_CREATE_H
    #define QUICK_CREATE_H

    sfRectangleShape *rectangle_quick_create(sfFloatRect rect,
                                sfTexture *texture, sfColor color);

#endif