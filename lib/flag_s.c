/*
** EPITECH PROJECT, 2024
** flag_s
** File description:
** display string
*/

#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

void flag_s(va_list list)
{
    char *str = va_arg(list, char *);

    my_putstr(str);
}
