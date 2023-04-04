/*
** EPITECH PROJECT, 2023
** rpg [WSL: fedora]
** File description:
** gui_evaluate
*/

#include "gui.h"
#include "francais.h"

/**
 * @brief check if a gui_state_t is set
 *
 * @param status the state to check (can be multiple with |)
 * @param state the state from the button to check
 * @return int return 1 if the state is set, 0 otherwise
 */
int gui_state_is(gui_state_t status, gui_state_t state)
{
    return ((status & state) != 0);
}

/**
 * @brief set a gui_state_t
 *
 * @param status the state to add (can be multiple with |)
 * @param state the state from the button to modify
 */
void gui_state_set(gui_state_t status, gui_state_t *state)
{
    *state |= status;
}

/**
 * @brief unset a gui_state_t
 *
 * @param status the state to remove (can be multiple with |)
 * @param state the state from the button to modify
 */
void gui_state_unset(gui_state_t status, gui_state_t *state)
{
    *state &= ~status;
}
