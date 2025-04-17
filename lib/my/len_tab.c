/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-joseph.birck
** File description:
** len_tab.c
*/

#include "../../include/my.h"

int len_tab(char **tab)
{
    int len_tab = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        len_tab = i;
    }
    return len_tab;
}
