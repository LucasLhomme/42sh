/*
** EPITECH PROJECT, 2024
** str str
** File description:
** str str BOOTCAMP
*/
#include "lib.h"

char *my_strstr(const char *str, const char *to_find)
{
    int j = 0;

    if (!*to_find)
        return (char *)str;
    for (int i = 0; str[i] != '\0'; i++) {
        while (str[i + j] != '\0' && to_find[j] != '\0'
            && str[i + j] == to_find[j]) {
            j++;
        }
        if (to_find[j] == '\0')
            return (char *)&str[i];
    }
    return NULL;
}
