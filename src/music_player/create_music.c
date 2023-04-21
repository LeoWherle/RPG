/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** create music
*/

#include <stdlib.h>
#include "music_player.h"
#include "errorhandling.h"
#include "my_str.h"

static const music_identifier_t stock[CREDIT_M] = {
    {"assets/music/Octopath-Traveler-Main-Theme.ogg",
    "Music: Octopath Traveler main theme, Yasunori Nishiki"},
    {"assets/music/Seliana-Day-Theme.ogg",
    "Music: Seliana (Day), Akihiko Narita"},
    {"assets/music/Pulsating-Power.ogg",
    "Music: Pulsating Power, Keichi Okabe"},
    {"assets/music/Serpent-Eating-the-Ground.ogg",
    "Music: Serpent Eating the Ground, Revo"},
    {"assets/music/Victory-Fanfare.ogg",
    "Music: Victory Fanfare, Nobuo Uematsu"},
};

music_t *create_music(char *path, char *text)
{
    music_t *new = NULL;
    int len = 0;

    new = malloc(sizeof(music_t));
    ASSERT_MALLOC(new, NULL);
    new->music = sfMusic_createFromFile(path);
    ASSERT_MALLOC(new->music, NULL);
    len = my_strlen(text);
    new->text = malloc((len + 1) * sizeof(char));
    ASSERT_MALLOC(new->text, NULL);
    my_strcpy(new->text, text);
    return new;
}

music_player_t *music_player_create(sfFont *font)
{
    music_player_t *new = NULL;
    new = malloc(sizeof(music_player_t));
    ASSERT_MALLOC(new, NULL);
    new->musi_list = malloc(sizeof(music_t) * CREDIT_M);
    ASSERT_MALLOC(new->musi_list, NULL);
    new->title = sfText_create();
    ASSERT_MALLOC(new->title, NULL);
    sfText_setFont(new->title, font);
    sfText_setCharacterSize(new->title, 32);
    sfText_setOutlineThickness(new->title, 3.2);
    new->music = NULL;
    new->new = false;
    new->id = 6;
    for (int i = 0; i < CREDIT_M; i++) {
        new->musi_list[i] = create_music(stock[i].path, stock[i].text);
        ASSERT_MALLOC(new->musi_list[i], NULL);
    }
    new->volume = 100;
    change_music(new, VILLAGE_M);
    return new;
}

void music_player_destroy(void *item)
{
    music_player_t *player = item;

    for (int i = 0; i < CREDIT_M; i++) {
        sfMusic_destroy(player->musi_list[i]->music);
        free(player->musi_list[i]->text);
        free(player->musi_list[i]);
    }
    free(player->musi_list);
    free(player);
}

void change_music(music_player_t *player, enum music_enum music_id)
{
    static music_player_t *music_player = NULL;

    if (!music_player) {
        music_player = player;
    }
    if (music_player->id == music_id)
        return;
    music_player->id = music_id;
    if (music_player->music)
        sfMusic_stop(music_player->music);
    music_player->music = music_player->musi_list[music_id]->music;
    sfText_setString(music_player->title,
                    music_player->musi_list[music_id]->text);
    sfMusic_setLoop(music_player->music, sfTrue);
    sfMusic_play(music_player->music);
    music_player->new = true;
    music_set_volume(music_player, music_player->volume);
}

void music_set_volume(music_player_t *music, float volume)
{
    static music_player_t *player = NULL;

    if (music)
        player = music;
    player->volume = volume;
    sfMusic_setVolume(player->music, volume);
}
