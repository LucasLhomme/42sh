/*
** EPITECH PROJECT, 2024
** conversion decimal to octal
** File description:
** convertis un chiffre to un octal
*/
#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

void flag_o(va_list list)
{
    int i = va_arg(list, int);
    int result = 0;
    int power = 1;

    while (i != 0) {
        result += (i % 8) * power;
        i = i / 8;
        power *= 10;
    }
    my_put_nbr(result);
}
