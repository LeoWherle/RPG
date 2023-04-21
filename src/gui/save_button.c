/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** save button func ptr
*/

#include "gui.h"
#include "item.h"
#include "errorhandling.h"
#include "save.h"
#include "entities.h"
#include "room.h"
#include "music_player.h"

void save_button(UNUSED void *self, window_t *screen)
{
    entity_t *player = NULL;
    map_t *map = NULL;

    player = screen->player;
    map = player->depend->dependency;
    if (map->room->type == HOUSE_R || map->room->type == VILLAGE_R)
        save(player);
}

void load_button(UNUSED void *self, window_t *screen)
{
    entity_t *player = NULL;

    screen->state = GAME;
    player = screen->player;
    reset_scene(screen->player, screen);
    load(player);
    change_music(NULL, VILLAGE_M);
}

void exit_button(UNUSED void *self, window_t *screen)
{
    reset_scene(screen->player, screen);
    screen->state = TITLE_SCREEN;
}
