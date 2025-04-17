/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** my_strncat
*/

#include "../../include/my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int a = my_strlen(dest) + nb;
    int b = my_strlen(dest);
    int i = 0;

    while (b != a) {
        dest[b] = src[i];
        b++;
        i++;
    }
    return 0;
}
