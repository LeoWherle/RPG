/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** function pointer of the option
*/

#include "item.h"
#include "music_player.h"
#include "errorhandling.h"

void volume_0(UNUSED void *self, UNUSED window_t *screen)
{
    music_set_volume(NULL, 0);
}

void volume_25(UNUSED void *self, UNUSED window_t *screen)
{
    music_set_volume(NULL, 25);
}

void volume_50(UNUSED void *self, UNUSED window_t *screen)
{
    music_set_volume(NULL, 50);
}

void volume_75(UNUSED void *self, UNUSED window_t *screen)
{
    music_set_volume(NULL, 75);
}

void volume_100(UNUSED void *self, UNUSED window_t *screen)
{
    music_set_volume(NULL, 100);
}
