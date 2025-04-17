/*
** EPITECH PROJECT, 2024
** handle_oct
** File description:
** handle les octale
*/

#include <stdarg.h>
#include "../../include/my.h"
#include <stdio.h>

int handle_oct(va_list ap)
{
    int nb = va_arg(ap, int);
    int result = nb;
    int rest = 0;
    char *base = "01234567";
    char oct[32];
    int i = 0;

    do {
        rest = result % 8;
        oct[i] = base[rest];
        result = result / 8;
        i++;
    } while (result != 0);
    oct[i] = '\0';
    my_revstr(oct);
    my_putstr(oct);
    return 0;
}
