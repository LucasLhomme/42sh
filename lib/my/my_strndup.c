/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** my_strndup.c
*/

#include <stddef.h>
#include "../../include/my.h"

char *my_strndup(char *str, char *src, int n)
{
    int j = 0;
    int len = my_strlen(src) + 1;
    char *result = malloc(sizeof(char) * (n + len));

    for (int i = 0; src[j] != '\0'; i++) {
        if (i <= n)
            result[i] = str[i];
        else {
            result[i] = src[j];
            j++;
        }
    }
    return result;
}
