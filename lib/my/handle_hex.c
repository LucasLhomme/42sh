/*
** EPITECH PROJECT, 2024
** handle_hex
** File description:
** handle le hexadecimale
*/

#include <stdarg.h>
#include "../../include/my.h"
#include <stdio.h>

int handle_hex(va_list ap)
{
    int nb = va_arg(ap, int);
    int result = nb;
    int rest = 0;
    char *base = "0123456789abcdef";
    char hex[32];
    int i = 0;

    do {
        rest = result % 16;
        hex[i] = base[rest];
        result = result / 16;
        i++;
    } while (result != 0);
    hex[i] = '\0';
    my_revstr(hex);
    my_putstr(hex);
    return 0;
}
