/*
** EPITECH PROJECT, 2024
** blanck.c
** File description:
** blanck.c
*/
#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

void blank(va_list list)
{
    char *blanck = va_arg(list, char *);

    if (my_strlen(blanck) == 0 || my_isneg(*blanck) == 1)
        my_putchar(' ');
    my_putstr(blanck);
}
