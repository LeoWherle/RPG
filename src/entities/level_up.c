/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** level up
*/

#include "entities.h"

void level_up(stats_t *stat)
{
    stat->exp.level++;
    stat->exp.mult += 0.1;
    stat->exp.current_exp -= stat->exp.exp_cap;
    stat->exp.exp_cap = PLAYER_EXP_CAP * stat->exp.level;
    stat->max_hp = PLAYER_HP * stat->exp.mult;
    stat->hp = stat->max_hp;
    stat->atk = PLAYER_ATK * stat->exp.mult;
    stat->speed = PLAYER_SPEED + 1.5 * stat->exp.mult;
}

void add_exp(stats_t *stat, int exp_gain)
{
    stat->exp.current_exp += exp_gain / stat->exp.mult;
    while (stat->exp.current_exp >= stat->exp.exp_cap) {
        level_up(stat);
    }
}
