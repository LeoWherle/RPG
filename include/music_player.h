/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** music_player
*/

#include <SFML/Audio/Music.h>
#include <SFML/Graphics.h>
#include <stdbool.h>
#include "item.h"
#include "errorhandling.h"

#ifndef MUSIC_PLAYER_H
    #define MUSIC_PLAYER_H

    enum music_enum {
        TITLE_SCREEN_M,
        VILLAGE_M,
        NORMAL_FIGHT_M,
        BOSS_FIGHT_M,
        VICTORY_M,
        CREDIT_M,
    };

    typedef struct music_identifier {
        char *path;
        char *text;
    } music_identifier_t;

    typedef struct music {
        sfMusic *music;
        char *text;
    } music_t;

    typedef struct music_player {
        enum music_enum id;
        sfMusic *music;
        sfText *title;
        music_t **musi_list;
        bool new;
        float volume;
    } music_player_t;

void change_music(music_player_t *player, enum music_enum music_id);
void music_set_volume(music_player_t *music, float volume);
void music_player_destroy(void *item);
music_player_t *music_player_create(sfFont *font);
music_t *create_music(char *path, char *text);
void music_print(void *item, window_t *window);
void music_update(void *item, window_t *window, UNUSED float delta);

#endif /*MUSIC_PLAYER_H*/
