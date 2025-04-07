/*
** EPITECH PROJECT, 2024
** strndup
** File description:
** strndup BOOTCAMP²
*/
#include "lib.h"

char *my_strndup(const char *str, size_t n)
{
    char *new_dup = malloc(sizeof(char) * (n + 1));

    if (new_dup == NULL)
        return NULL;
    for (size_t i = 0; i < n; i++)
        new_dup[i] = str[i];
    new_dup[n] = '\0';
    return new_dup;
}
