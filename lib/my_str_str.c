/*
** EPITECH PROJECT, 2024
** str str
** File description:
** str str BOOTCAMP
*/
#include "lib.h"

char *my_strstr(char *str, char const *to_find)
{
    int j = 0;

    if (!*to_find)
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        for (; str[i + j] != '\0' && to_find[j]
        != '\0' && str[i + j] == to_find[j]; j++) {
            j++;
        }
        if (to_find[j] == '\0')
            return &str[i];
    }
    return NULL;
}
