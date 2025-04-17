/*
** EPITECH PROJECT, 2024
** Les flottants
** File description:
** display un float dans printf
*/

#include "../../include/my.h"
#include <stdarg.h>
#include <stdio.h>

int flottant(va_list ap)
{
    double nb = va_arg(ap, double);
    int post = (int)nb;
    int after_int;
    float after;

    after = (nb - post) * 1000000;
    after_int = (int)(after + 0.5);
    my_put_nbr(post);
    my_putchar('.');
    my_put_nbr(after_int);
    return 0;
}
