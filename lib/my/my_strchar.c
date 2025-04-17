/*
** EPITECH PROJECT, 2024
** my_strchar
** File description:
** str to char
*/

#include "../../include/my.h"
#include <stdlib.h>

char *my_strchar(const char *str, int c)
{
    while (*str) {
        if (*str == c)
            return (char *)str;
        str++;
    }
    return NULL;
}
