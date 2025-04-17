/*
** EPITECH PROJECT, 2024
** count_words
** File description:
** lol c'est cool vs code
*/

#include "../../include/my.h"
#include <stdarg.h>
#include <stdio.h>

int handle_e(va_list ap)
{
    int i = 0;
    double nb = va_arg(ap, double);
    int post = 0;
    int after_int = 0;
    float after = 0.0;

    for (; (int)nb > 9; i++)
        nb = nb / 10;
    post = (int)nb;
    after = (nb - post) * 1000000;
    after_int = (int)(after + 0.5);
    my_put_nbr(post);
    my_putchar('.');
    my_put_nbr(after_int);
    my_putstr("e+");
    my_put_nbr(0);
    my_put_nbr(i);
    return 0;
}
