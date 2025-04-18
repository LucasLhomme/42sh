/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** concatene_tab.c
*/

#include "../../include/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int get_nb_char(char **tab)
{
    int count = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        count += strlen(tab[i]);
    }
    return count;
}

char *cat_tab(char **tab)
{
    int nb_of_char = 0;
    char *str = NULL;
    int pos = 0;
    int len = 0;

    if (tab == NULL)
        return NULL;
    nb_of_char = get_nb_char(tab);
    str = malloc(sizeof(char) * (nb_of_char + 1));
    if (str == NULL)
        return NULL;
    for (int i = 0; tab[i] != NULL; i++) {
        len = strlen(tab[i]);
        memcpy(str + pos, tab[i], len);
        pos += len;
    }
    str[nb_of_char] = '\0';
    return str;
}
