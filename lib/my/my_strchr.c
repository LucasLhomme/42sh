/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** my_strchr.c
*/

#include "../../include/my.h"
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
