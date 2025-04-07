/*
** EPITECH PROJECT, 2024
** Modulo d
** File description:
** Modulo D
*/

#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

void flag_d(va_list list)
{
    my_put_nbr(va_arg(list, int));
}
