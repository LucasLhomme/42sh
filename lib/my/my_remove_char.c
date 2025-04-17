/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-robotfactory-gregoire.fageot
** File description:
** my_remove_char.c
*/

#include "../../include/my.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char get_last_char(char *str)
{
    int len = my_strlen(str);

    for (int i = 0; i <= len; i++) {
        if (i == len - 1)
            return str[i];
    }
}

int nb_char(char *str, char c)
{
    int nb_occu = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            nb_occu++;
    }
    return nb_occu;
}

char *remove_char(char *str, char c)
{
    int nb_occu = nb_char(str, c);
    char *result = malloc(sizeof(char) * (my_strlen(str) - nb_occu + 1));
    int y = 0;

    if (!result)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            result[y] = str[i];
            y++;
        }
    }
    result[y] = '\0';
    return result;
}

char *remove_start(char *str, int n)
{
    int len = my_strlen(str);
    char *result = NULL;

    if (n >= len)
        return my_strdup("");
    result = malloc(sizeof(char) * (len - n + 1));
    if (!result)
        return NULL;
    my_strcpy(result, str + n);
    return result;
}

char *remove_end(char *str, int n)
{
    int len = my_strlen(str);
    char *result = NULL;

    if (n >= len)
        return my_strdup("");
    result = malloc(sizeof(char) * (len - n + 1));
    if (!result)
        return NULL;
    for (int i = 0; i < len - n; i++) {
        result[i] = str[i];
    }
    result[len - n] = '\0';
    return result;
}
