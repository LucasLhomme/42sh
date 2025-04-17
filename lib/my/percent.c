/*
** EPITECH PROJECT, 2024
** pourcantage
** File description:
** pourcentage
*/

#include <stdarg.h>
#include "../../include/my.h"

int percent(va_list ap)
{
    (void)ap;
    my_putchar('%');
    return 1;
}
