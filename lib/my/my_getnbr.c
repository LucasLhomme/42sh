/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** get un nbr
*/

#include "../../include/my.h"

int my_getnbr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return 0;
}
