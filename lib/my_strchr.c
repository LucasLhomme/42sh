/*
** EPITECH PROJECT, 2025
** lib
** File description:
** strchr
*/

#include "lib.h"
#include <unistd.h>

char *my_strchr(const char *str, char c)
{
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}
