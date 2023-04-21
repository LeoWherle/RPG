/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** save game
*/

#include <unistd.h>
#include <fcntl.h>
#include "entities.h"
#include "weapon.h"
#include "my_str.h"

void put_nbr(int nbr, int size, int fd, int i)
{
    char c = '\0';

    if (i > size)
        return;
    c = nbr % 10 + '0';
    put_nbr(nbr / 10, size, fd, i + 1);
    write(fd, &c, 1);
}

static void write_number(int nbr, int fd)
{
    int len = 0;
    int tmp = nbr;

    while (tmp > 0) {
        tmp /= 10;
        len++;
    }
    if (nbr == 0) {
        write(fd, "0", 1);
    } else
        put_nbr(nbr, len - 1, fd, 0);
}

static void save_weapon(weapon_t *weapon, int fd)
{
    sfVector2f size = {0};

    if (weapon->use == sword_use)
        write(fd, "s;", 2);
    else
        write(fd, "b;", 2);
    write(fd, weapon->path, my_strlen(weapon->path));
    write(fd, ";", 1);
    write_number(weapon->cooldown * 10, fd);
    write(fd, ";", 1);
    write_number(weapon->strenght, fd);
    write(fd, ";", 1);
    size = sfRectangleShape_getSize(weapon->weapon);
    write_number(size.x, fd);
}

void save(entity_t *player)
{
    int fd = 0;
    weapon_t *weapon = NULL;

    fd = open(".save.csv", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (fd == -1) {
        write(2, "Failed to save", 14);
        return;
    }
    write_number(player->stats.exp.level, fd);
    write(fd, ";", 1);
    write_number(player->stats.exp.current_exp, fd);
    for (node_t *node = player->inventory->items->head; node;
        node = node->next) {
        write(fd, "\n", 1);
        weapon = node->data;
        save_weapon(weapon, fd);
    }
}
