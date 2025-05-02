/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** is_str_alnum.c
*/

#include "../../include/my.h"

int is_alpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
        return 0;
    return 84;
}

int is_num(char *str)
{
    if (!str)
        return 84;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        else
            return 84;
    }
    return 0;
}

int is_alnum_two(char *str)
{
    if (!str)
        return 84;
    for (int i = 0; str[i] != '\0'; i++) {
        if (((str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z')))
            continue;
        else
            return 84;
    }
    return 0;
}

int my_isalnum_char(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z'))
        return 0;
    else {
        return 84;
    }
}
