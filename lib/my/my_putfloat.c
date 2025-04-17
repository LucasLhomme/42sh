/*
** EPITECH PROJECT, 2024
** my_putfloat
** File description:
** float
*/

#include "../../include/my.h"

int my_putfloat(float nb)
{
    int post;
    int after;

    post = (int)nb;
    after = ((float)nb - (float)post) * (float)100;
    my_put_nbr(post);
    my_putchar('.');
    if (after < 10 && after >= 0)
        my_put_nbr(0);
    my_put_nbr(after);
}
