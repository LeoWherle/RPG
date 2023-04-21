/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** load game
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "entities.h"
#include "save.h"
#include "weapon.h"
#include "my_str.h"

static void load_stats(char *line, entity_t *player)
{
    char **csv = NULL;
    int level = 0;

    csv = str_to_word_array(line, ";\n");
    level = my_getnbr(csv[0]);
    for (int i = 1; i < level; i++)
        level_up(&player->stats);
    player->stats.exp.current_exp = my_getnbr(csv[1]);
    for (int i = 0; csv[i]; i++)
        free(csv[i]);
    free(csv);
}

static bool check_line(char *line, FILE *fd, int nb)
{
    int comma = 0;

    for (int i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
        if (line[i] == ';')
            comma++;
    }
    if (comma == nb)
        return false;
    free(line);
    fclose(fd);
    write(2, "invalid save file", 18);
    return true;
}

static void load_weapon(char *line, entity_t *player)
{
    char **csv = NULL;
    float cooldown = 0.;
    int strength = 0;
    int size = 0;
    weapon_t *new = NULL;
    csv = str_to_word_array(line, ";\n");
    cooldown = (float){my_getnbr(csv[2])} / 10.;
    strength = my_getnbr(csv[3]);
    size = my_getnbr(csv[4]);
    if (csv[0][0] == 's') {
        new = weapon_create_sword(cooldown, strength,
                                (sfVector2f){size, size}, csv[1]);
    } else {
        new = weapon_create_bow(cooldown, strength,
                            (sfVector2f){size, size}, csv[1]);
    }
    for (int i = 0; csv[i]; i++)
        free(csv[i]);
    new->hitbox->owner = player;
    node_append(player->inventory->items, new);
}

bool load(entity_t *player)
{
    FILE *fd = 0;
    char *line = NULL;
    size_t r = 0;

    fd = fopen(".save.csv", "r");
    if (fd == NULL) return false;
    getline(&line, &r, fd);
    if (check_line(line, fd, 1)) return false;
    load_stats(line, player);
    node_destroy(player->inventory->items, inventory_weapon_destroy);
    while (getline(&line, &r, fd) != EOF) {
        if (check_line(line, fd, 4)) return false;
        load_weapon(line, player);
    }
    free(line);
    fclose(fd);
    player->inventory->weapon = player->inventory->items->head->data;
    player->coll.weapon = player->inventory->items->head->data;
    return true;
}
