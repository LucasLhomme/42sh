/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-joseph.birck
** File description:
** error_handling
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "project.h"

char *remove_first_char(const char *str)
{
    int len = my_strlen(str);
    char *src = malloc(sizeof(char) * len);
    int y = 0;

    for (int i = 1; str[i] != '\0'; i++) {
        src[y] = str[i];
        y++;
    }
    src[y] = '\0';
    return src;
}

