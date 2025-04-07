/*
** EPITECH PROJECT, 2024
** strncpy
** File description:
** je sais pas quoi mettre
*/

#include <stdio.h>

char *my_strncpy(char *dest, char const *src, int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
    return dest;
}
