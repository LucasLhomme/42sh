/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_strtok
*/

#include "lib.h"
#include <unistd.h>

char *my_strtok(char *str, const char *delim)
{
    static char *next = NULL;
    char *token_start = NULL;

    if (str)
        next = str;
    if (!next)
        return NULL;
    while (*next && my_strchr(delim, *next))
        next++;
    if (*next == '\0')
        return NULL;
    token_start = next;
    while (*next && !my_strchr(delim, *next))
        next++;
    if (*next) {
        *next = '\0';
        next++;
    } else
        next = NULL;
    return token_start;
}
