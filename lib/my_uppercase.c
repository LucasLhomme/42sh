/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-lucas.lhomme
** File description:
** my_uppercase
*/
#include <stdio.h>

char *my_uppercase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
    return str;
}
