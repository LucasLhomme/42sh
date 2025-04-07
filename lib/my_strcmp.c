/*
** EPITECH PROJECT, 2024
** jsp
** File description:
** jsp
*/
#include <stddef.h>
#include <stdio.h>

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
