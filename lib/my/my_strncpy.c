/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** copier n charactere
*/
#include <stddef.h>
#include "../../include/my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (n >= my_strlen(src)) {
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
    dest[i] = '\0';
    return dest;
    }
    while (i != n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
