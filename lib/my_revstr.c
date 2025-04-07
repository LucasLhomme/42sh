/*
** EPITECH PROJECT, 2024
** revstr
** File description:
** revstr BOOTCAMP
*/
#include "lib.h"

char *my_revstr(char *str)
{
    int i = 0;
    int len = my_strlen(str);
    char temp;

    if (str == NULL)
        return NULL;
    for (; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}
