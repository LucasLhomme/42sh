/*
** EPITECH PROJECT, 2024
** flag_x
** File description:
** display hexadecimal
*/
#include <unistd.h>
#include <stdarg.h>
#include "lib.h"

void flag_x(va_list list)
{
    char *base = "0123456789abcdef";
    int i = (va_arg(list, int));
    int r = 0;
    int p = 0;
    char str[16];

    for (; i != 0; p++) {
        r = i % 16;
        str[p] = base[r + '\0'];
        i = i / 16;
    }
    str[p] = '\0';
    my_revstr(str);
    my_putstr(str);
}
