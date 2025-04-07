/*
** EPITECH PROJECT, 2024
** Isneg
** File description:
** positif or not
*/
#include "lib.h"

int my_isneg(int i)
{
    if (i < 0)
        my_putchar('N');
    else
        my_putchar('P');
    return 0;
}
