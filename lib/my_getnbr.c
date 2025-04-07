/*
** EPITECH PROJECT, 2024
** get nbr
** File description:
** nbr
*/

#include "lib.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int result = 0;
    int neg = 1;

    while (str[i] == '\0' || str[i] == '\n') {
        i++;
    }
    if (str[i] == '-') {
        neg = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * neg;
}
