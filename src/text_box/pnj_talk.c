/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** pnj speech buble
*/

#include "entities.h"
#include "text_box.h"
#include "errorhandling.h"

void talk_tuto_pnj(UNUSED entity_t *player, UNUSED collider_t *col)
{
    static int step = 0;
    if (step == 0) {
        text_box_modify(NULL, " Miner\0", "\tHello stranger.\n\
\t('LEFT CLICK' to continue)\n\
\tI found you yesterday down the huge hole caused by the meteor.\n\
\tYou might have lost your memory, let me teach you how to move.\n\
\tYou can press 'Z' to go up, 'S' to go down,\n\t'Q' to go left, \
'D' to go right.\n\tYou can open your inventory by pressing 'E', interact \
with people and objects \tusing 'SPACE' and open the option menu with \
'ESCAPE'.\n\tI think the old villager next to the mine entrance \
has something to tell you\n\tYou should go talk to him.\0", 1);
    } if (step >= 1) {
        text_box_modify(NULL, " Miner\0", "\tYou forgot how to move ?\n\
\tLet me explain it.\n\tYou can press 'Z' to go up, 'S' to go down,\n\t \
'Q' to go left, 'D' to go right.\n\tYou can open your inventory by pressing \
'E', interact with people and objects \tusing 'SPACE' and open the option \
menu with 'ESCAPE'.\n\tI think the old villager next to the mine entrance \
has something to tell you.\n\tYou should go talk to him.\0", 1);
    }
    step++;
}

void talk_combat_pnj(UNUSED entity_t *player, UNUSED collider_t *col)
{
    static int step = 0;

    if (step == 0) {
        text_box_modify(NULL, " Martial Teacher\0", "\tHello stranger.\n\
\tI'm the martial teacher and I will teach you how to fight.\n\
\tTo swing your sword press the 'LEFT CLICK' and aim with your 'MOUSE'.\n\
\tYou can also do a dash with 'SHIFT'.\n\
\tThere is a slime down this place, pick your sword and kill it.\0", 1);
    }
    if (step >= 1) {
        text_box_modify(NULL, " Martial Teacher\0", "\tYou forgot how to\
fight ?\
\n\tTo swing your sword press the 'LEFT CLICK' and aim with your 'MOUSE'.\n\
\tYou can also do a dash with 'SHIFT'.\n\
\tThere is a slime down this place, pick your sword and kill it.\0", 1);
    }
    step++;
}

static void reward_quest(entity_t *player)
{
    static bool reward = false;

    if (reward == true)
        text_box_modify(NULL, " Old Villager\0",
        "\tYou killed the Slime King, \
thank you !\n\tCongratulations you finished the game IntoTheAbyss ! :)\0", 1);
    if (player->quest == true && reward == false) {
        add_exp(&player->stats, 5050);
        text_box_modify(NULL, " Old Villager\0",
        "\tYou killed the Slime King, \
thank you !\n\there a little reward for your efforts.\n\
\tCongratulations you finished the game IntoTheAbyss ! :)\0", 1);
        reward = true;
    }
}

void talk_quest_pnj(UNUSED entity_t *player, UNUSED collider_t *col)
{
    static int step = 0;

    if (step == 0) { text_box_modify(NULL, " Old Villager\0",
    "\tHello stranger.\n\
\tMonsters are appearing since the metor crashed on our village.\n\
\tGo down the big hole using this mine to train and then defeat the \
Slime King.\n\
\tI'll give you a reward if you comeback here after defeating it.\n\
\tLet me warn you, there is a lof of monsters in the mines but there is also \
some \ttreasures, it will help you to defeat the Slime King.\0", 1);
    player->quest = false;
    } if (step >= 1) {
        text_box_modify(NULL, " Old Villager\0",
        "\tYou forgot what you have to do ?\n\tGo down the big hole to defeat \
a Slime King.\n\tI'll give you a reward if you comeback here after defeating \
it.\n\tIf you're not strong enough, go in the mines thanks to this door \
and train.\0", 1);
    }
    step++;
    reward_quest(player);
}
