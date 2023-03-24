/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained_list_destructor
*/

#include <stdlib.h>
#include "chained_list.h"

/**
 * @brief free a data only
 *
 * @param data the data to free
 */
void string_free(void *data)
{
    free(data);
}
