/*
** EPITECH PROJECT, 2025
** B-PSU-100-LIL-1-1-myls-lucas.lhomme
** File description:
** my_strcat
*/
#include "lib.h"

char *my_strcat(char *str, const char *new_str)
{
    int i = 0;
    int str_len = my_strlen(str);
    int new_str_len = my_strlen(new_str);

    for (i = 0; i < new_str_len; i++)
        str[str_len + i] = new_str[i];
    str[str_len + i] = '\0';
    return str;
}
