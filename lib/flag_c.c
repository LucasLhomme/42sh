/*
** EPITECH PROJECT, 2024
** Flag c
** File description:
** flag c
*/
#include <stdio.h>
#include <stdarg.h>
#include "lib.h"

void flag_c(va_list list)
{
    my_putchar(va_arg(list, int));
}
