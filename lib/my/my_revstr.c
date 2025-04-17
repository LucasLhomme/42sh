/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** reverse les char d'un string
*/

#include "../../include/my.h"

char *my_revstr(char *str)
{
    int lenstr = my_strlen(str);
    int i = 0;
    int fin = lenstr - 1;
    char swap;

    while (i < fin) {
        swap = str[i];
        str[i] = str[fin];
        str[fin] = swap;
        i++;
        fin--;
    }
    return str;
}
