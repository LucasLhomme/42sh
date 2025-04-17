/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** dupliquer une str
*/

#include "../../include/my.h"
#include <stdlib.h>

char *my_strdup(const char *s)
{
    char *dup = malloc(my_strlen(s) + 1);

    if (!dup)
        return NULL;
    my_strcpy(dup, s);
    return dup;
}
